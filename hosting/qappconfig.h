
#ifndef __SYMBOID_SDK_HOSTING_QAPPCONFIG_H__
#define __SYMBOID_SDK_HOSTING_QAPPCONFIG_H__

#include "sdk/hosting/defs.h"
#include "sdk/hosting/qconfig.h"
#include "sdk/arch/mainobject.h"
#include "sdk/hosting/quiconfig.h"
#include "sdk/hosting/qsoftwareconfig.h"

class SDK_HOSTING_API QAppConfig : public QConfigNode
{
    Q_OBJECT
    QML_SINGLETON(AppConfig)

public:
    QAppConfig(QObject* parent = Q_NULLPTR);
    ~QAppConfig();

    Q_CONFIG_NODE(QUiConfig, ui)
    Q_CONFIG_NODE(QSoftwareConfig, software)
};

#endif // __SYMBOID_SDK_HOSTING_QGENERICCONFIG_H__
