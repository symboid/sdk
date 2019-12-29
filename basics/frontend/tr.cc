
#include "sdk/basics/frontend/tr.h"

#include <QTranslator>
#include <QCoreApplication>
#include <QLocale>

namespace Sf {

static const QString DEFAULT_LANG("hu");

static QString qmFilePath(const QString& modName, const QString& langId)
{
    // path of compiled qm file:
    return QString(":tr/") + modName + QStringLiteral("_")
            + langId + QStringLiteral(".qm");
}

void loadTranslations(const QString& modName)
{
    QTranslator* translator = new QTranslator;

    QString langId = QLocale::system().name().left(2);
    QString filePath;

    if (translator->load(filePath = qmFilePath(modName, langId)))
    {
//        sy_info("Translation file '%s' loaded.", filePath.toStdString().c_str());
    }
    else if (translator->load(filePath = qmFilePath(modName, DEFAULT_LANG)))
    {
//        sy_warning("Locale '%s' not supported. Translation file '%s' loaded.",
//                langId.toStdString().c_str(), filePath.toStdString().c_str());
    }
    else
    {
        filePath = "";
//        sy_error("Translation file for module '%s' cannot be loaded", modName.toUtf8().data());
    }

    if (filePath.size())
    {
        if (QCoreApplication::instance()->installTranslator(translator))
        {
            QObject::connect(QCoreApplication::instance(), SIGNAL(aboutToQuit()), translator, SLOT(deleteLater()));
//            sy_info("Translation file '%s' installed.", filePath.toStdString().c_str());
        }
        else
        {
            delete translator;
//            sy_error("Translation file '%s' cannot be installed.", filePath.toStdString().c_str());
        }
    }
    else
    {
        delete translator;
    }
}

} // namespace Sf
