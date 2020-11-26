
#ifndef __SYMBOID_SDK_HOSTING_QSOFTWARECONFIG_H__
#define __SYMBOID_SDK_HOSTING_QSOFTWARECONFIG_H__

#include "sdk/hosting/defs.h"
#include "sdk/hosting/qconfig.h"

class SDK_HOSTING_API QSoftwareConfig : public QConfigNode
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "SoftwareConfig";

    QSoftwareConfig(const QString& id, QConfigNode* parentNode, const char* parentSignal)
        : QConfigNode(id, parentNode, parentSignal)
    {
    }

    enum UpdateMethod
    {
        UpdateAutomatic = 0,
        UpdateManual    = 1,
        UpdateNone      = 2,
    };
    Q_ENUM(UpdateMethod)

    Q_CONFIG_PROPERTY(int, update_method, 1)
};

#endif // __SYMBOID_SDK_HOSTING_QSOFTWARECONFIG_H__
