
#include "sdk/arch/setup.h"
#include "sdk/arch/modmain.h"

arh_ns_begin

mod_main::mod_main()
    : basic_mod("main")
    , _M_file_log(nullptr)
{
    g_logs.push_back(&_M_default_log);
}

mod_main::~mod_main()
{
    delete _M_file_log;
    g_logs.clear();
}

void mod_main::init_file_log()
{
    _M_file_log = new file_log();
    g_logs.push_back(_M_file_log);
}

arh_ns_end
