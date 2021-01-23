
#include "sdk/arch/setup.h"
#include "sdk/arch/modmain.h"
#include <QOperatingSystemVersion>
#include <QCoreApplication>
#include <QSettings>

arh_ns_begin

mod_main::mod_main(const char* company_name, const char* app_name)
    : basic_mod("main")
    , _M_file_log(nullptr)
{
    g_logs.push_back(&_M_default_log);

    const QOperatingSystemVersion osVersion(QOperatingSystemVersion::current());
    if (osVersion.type() == QOperatingSystemVersion::Windows && osVersion.majorVersion() < 10)
    {
        QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    }
    QSettings settings(QSettings::UserScope, company_name, app_name);
    if (settings.value("ui/high_dpi_scaling", false).toBool())
    {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    }
}

mod_main::~mod_main()
{
    delete _M_file_log;
    g_logs.clear();
}

void mod_main::init_file_log()
{
#ifndef Q_OS_WASM
    _M_file_log = new file_log();
    g_logs.push_back(_M_file_log);
#endif
}

arh_ns_end
