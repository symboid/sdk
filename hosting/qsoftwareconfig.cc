
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
    return QSslSocket::supportsSsl();
}

QString QSoftwareConfig::ssl_lib_version_compiletime() const
{
    return QSslSocket::sslLibraryBuildVersionString();
}

QString QSoftwareConfig::ssl_lib_version_runtime() const
{
    return QSslSocket::sslLibraryVersionString();
}
