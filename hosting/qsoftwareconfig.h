
#ifndef __SYMBOID_SDK_HOSTING_QSOFTWARECONFIG_H__
#define __SYMBOID_SDK_HOSTING_QSOFTWARECONFIG_H__

#include "sdk/hosting/defs.h"
#include "sdk/hosting/qconfig.h"

class QSoftwareConfig : public QConfigNode
{
    Q_OBJECT
    QML_SINGLETON(SoftwareConfig)
public:
    QSoftwareConfig(QObject* parent);

    enum UpdateMethod
    {
        UpdateAutomatic,
        UpdateManual,
        UpdateNone
    };
    Q_ENUM(UpdateMethod)

    Q_CONFIG_PROPERTY(UpdateMethod, updateMethod, UpdateManual)
};

//Q_DECLARE_METATYPE()

#endif // __SYMBOID_SDK_HOSTING_QSOFTWARECONFIG_H__
