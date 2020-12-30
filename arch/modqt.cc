
#include "sdk/arch/modqt.h"
#include "sdk/arch/log.h"
#include <QLocale>
#include <QCoreApplication>

arh_ns_begin

void basic_qt_translation::load(const QString& _mod_name)
{
    const QString mod_file_name = QString(_mod_name).replace('_','-');

    static const QLocale system_locale = QLocale::system();
    static const QString lang_code = system_locale.name().left(2);
    QString qm_file_path = lang_code.isEmpty() ? "" :
            QString(":tr/%1_%2.qm").arg(mod_file_name, lang_code);

    if (lang_code == "en")
    {
        log_info << "english translation used for module '" << _mod_name << "'";
    }
    else if (!_M_qm_file.load(system_locale, mod_file_name, "_", ":/tr") &&
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
