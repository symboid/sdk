
#include "sdk/arch/log.h"
#include <iostream>

arh_ns_begin

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
    }
}

console_log::console_log()
    : stream_log(&std::cout)
{
}

arh_ns_end
