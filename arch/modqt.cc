
#include "sdk/arch/modqt.h"
#include "sdk/arch/log.h"
#include <QLocale>
#include <QCoreApplication>

arh_ns_begin

void basic_qt_translation::load(const QString& _mod_name)
{
    const QString mod_file_name = QString(_mod_name).replace('_','-');

    const QString config_lang_id("hu");
    QString qm_file_path = config_lang_id.isEmpty() ? "" :
            QString(":tr/%1_%2.qm").arg(mod_file_name, config_lang_id);

    if (!_M_qm_file.load(QLocale::system(), mod_file_name, "_", ":/tr") &&
        !_M_qm_file.load(qm_file_path))
    {
        log_error << "translation for module '" << _mod_name << "' cannot be loaded!";
    }
    else if (!QCoreApplication::installTranslator(&_M_qm_file))
    {
        log_error << "translation for module '" << _mod_name << "' loaded but cannot be installed!";
    }
    else
    {
        log_info << "translation for module '" << _mod_name << "' loaded and installed.";
    }
}

arh_ns_end
