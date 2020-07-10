
#ifndef __SYMBOID_SDK_ARCH_LOG_H__
#define __SYMBOID_SDK_ARCH_LOG_H__

#include "sdk/arch/defs.h"
#include <sstream>
#include <list>
#include <mutex>
#include <fstream>

arh_ns_begin

class SDK_ARCH_API log
{
public:
    enum level
    {
        debug,
        info,
        warning,
        error,
        fatal,
    };
public:
    static std::string level_str(level _level);

public:
    virtual ~log() = default;

public:
    virtual void write_entry(level _level, const std::string& _message) = 0;
};

extern std::list<log*> g_logs;

class SDK_ARCH_API log_entry : public std::ostringstream
{
public:
    log_entry(log::level _log_level);
    ~log_entry();

private:
    log::level _M_log_level;
};

class SDK_ARCH_API stream_log : public log
{
public:
    stream_log(std::ostream* _out_stream = nullptr);
public:
    void write_entry(level _level, const std::string& _message) override;

private:
    std::mutex _M_write_mutex;
protected:
    std::ostream* _M_out_stream;
};

class SDK_ARCH_API console_log : public stream_log
{
public:
    console_log();
};

class SDK_ARCH_API file_log : public stream_log
{
public:
//    file_log();
};

arh_ns_end

#define log_info arh::log_entry(arh::log::info)
#define log_warning arh::log_entry(arh::log::warning)
#define log_error arh::log_entry(arh::log::error)

#endif // __SYMBOID_SDK_ARCH_LOG_H__
