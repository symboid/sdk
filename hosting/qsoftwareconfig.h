
#ifndef __SYMBOID_SDK_HOSTING_QSOFTWARECONFIG_H__
#define __SYMBOID_SDK_HOSTING_QSOFTWARECONFIG_H__

#include "sdk/hosting/defs.h"
#include "sdk/hosting/qconfig.h"

class SDK_HOSTING_API QSoftwareConfig : public QConfigNode
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "SoftwareConfig";

    QSoftwareConfig(const QString& id, QAbstractConfig* parentNode, const char* parentSignal);

    enum UpdateMethod
    {
        UpdateAutomatic = 0,
        UpdateManual    = 1,
        UpdateNone      = 2,
    };
    Q_ENUM(UpdateMethod)

    Q_CONFIG_PROPERTY(int, update_method, 1)

    Q_CONFIG_CONSTANT(QString, qt_version_string)
    Q_CONFIG_CONSTANT(bool, ssl_supported)
    Q_CONFIG_CONSTANT(QString, ssl_lib_version_compiletime)
    Q_CONFIG_CONSTANT(QString, ssl_lib_version_runtime)
};

#endif // __SYMBOID_SDK_HOSTING_QSOFTWARECONFIG_H__
