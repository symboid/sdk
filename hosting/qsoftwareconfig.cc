
#include "sdk/hosting/setup.h"
#include "sdk/hosting/qsoftwareconfig.h"
#include <QSslSocket>

QSoftwareConfig::QSoftwareConfig(const QString& id, QAbstractConfig* parentNode, const char* parentSignal)
    : QConfigNode(id, parentNode, parentSignal)
{
}

QString QSoftwareConfig::qt_version_string() const
{
    return QT_VERSION_STR;
}

bool QSoftwareConfig::ssl_supported() const
{
#ifdef QT_NO_SSL
    return true;
#else
    return QSslSocket::supportsSsl();
#endif
}

QString QSoftwareConfig::ssl_lib_version_compiletime() const
{
#ifdef QT_NO_SSL
    return "-";
#else
    return QSslSocket::sslLibraryBuildVersionString();
#endif
}

QString QSoftwareConfig::ssl_lib_version_runtime() const
{
#ifdef QT_NO_SSL
    return "-";
#else
    return QSslSocket::sslLibraryVersionString();
#endif
}
