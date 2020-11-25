
#ifndef __SYMBOID_SDK_HOSTING_QUICONFIG_H__
#define __SYMBOID_SDK_HOSTING_QUICONFIG_H__

#include "sdk/hosting/defs.h"
#include "sdk/hosting/qconfig.h"

class QUiConfig : public QConfigNode
{
    Q_OBJECT
public:
    QUiConfig(QConfigNode* parentNode, const char* parentSignal);
    ~QUiConfig();

    Q_CONFIG_PROPERTY(QString, style, "Default", tr("Style"))
};

#endif // __SYMBOID_SDK_HOSTING_QUICONFIG_H__
