
#include "sdk/arch/log.h"
#include <iostream>
#if SY_PLATFORM_IS_ANDROID
#include <android/log.h>
#endif // __ANDROID__
#include <QDebug>
#include <QDir>
#include <QStandardPaths>

arh_ns_begin

static void defaultMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    Q_UNUSED(context)
    Q_UNUSED(msg)
//    const char *file = context.file ? context.file : "";
//    const char *function = context.function ? context.function : "";
    switch (type)
    {
    case QtDebugMsg:
    case QtInfoMsg:
        log_info << localMsg.toStdString();
        break;
    case QtWarningMsg:
        log_warning << localMsg.toStdString();
        break;
    case QtCriticalMsg:
    case QtFatalMsg:
        log_error << localMsg.toStdString();
        break;
    }
}

log::log()
{
    qInstallMessageHandler(defaultMessageOutput);
}

std::string log::level_str(level _level)
{
    switch (_level)
    {
    case info:    return ".i.";
    case warning: return "(w)";
    case error:   return "!e!";
    case fatal:   return "!!!";
    default:      return "   ";
    }
}

log_entry::log_entry(log::level _log_level)
    : _M_log_level(_log_level)
{

}

log_entry::~log_entry()
{
    std::string log_message = str();
    for (log* log : g_logs)
    {
        log->write_entry(_M_log_level, log_message);
    }
}

std::list<log*> g_logs;

stream_log::stream_log(std::ostream* _out_stream)
    : _M_out_stream(_out_stream)
{
}

void stream_log::write_entry(level _level, const std::string& _message)
{
    if (_M_out_stream)
    {
        std::lock_guard<std::mutex> write_guard(_M_write_mutex);
        *_M_out_stream << " " << log::level_str(_level) << " " << _message << std::endl;
        _M_out_stream->flush();
    }
}

console_log::console_log()
    : stream_log(&std::cout)
{
}

void android_log::write_entry(level _level, const std::string& _message)
{
#if SY_PLATFORM_IS_ANDROID
    std::lock_guard<std::mutex> write_guard(_M_log_mutex);
    int android_log_level = ANDROID_LOG_INFO;
    switch (_level)
    {
    case debug:   android_log_level = ANDROID_LOG_DEBUG; break;
    case warning: android_log_level = ANDROID_LOG_WARN; break;
    case error:   android_log_level = ANDROID_LOG_ERROR; break;
    case fatal:   android_log_level = ANDROID_LOG_FATAL; break;
    case info:    android_log_level = ANDROID_LOG_INFO; break;
    }

    __android_log_print(android_log_level, "-----", "%s", _message.c_str());
#else
    Q_UNUSED(_level)
    Q_UNUSED(_message)
#endif
}

QString file_log::logFilePath()
{
    QString path;
    static const QString logDirPath(QStandardPaths::writableLocation(QStandardPaths::DataLocation)
            + "/log");
    if (QDir::root().mkpath(logDirPath))
    {
        path = logDirPath + "/current.log.txt";
    }
    return path;
}

file_log::file_log()
    : _M_log_file(logFilePath())
{
    const QString logDirPath(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/log");
    if (QDir::root().mkpath(logDirPath))
    {
        _M_log_file.open(QFile::WriteOnly);
    }
}

void file_log::write_entry(level _level, const std::string& _message)
{
    QMutexLocker writeLock(&_M_log_mutex);
    _M_log_file.write(" ");
    _M_log_file.write(log::level_str(_level).c_str());
    _M_log_file.write(" ");
    _M_log_file.write(_message.c_str());
    _M_log_file.write("\n");
    _M_log_file.flush();
}

arh_ns_end
