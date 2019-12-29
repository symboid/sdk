
#include "sdk/arch/setup.h"
#include "sdk/arch/modmain.h"

arh_ns_begin

mod_main::mod_main()
    : basic_mod("main")
{
    g_logs.push_back(&_M_console_log);
}

mod_main::~mod_main()
{
    g_logs.clear();
}

arh_ns_end
