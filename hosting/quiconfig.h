
#ifndef __SYMBOID_SDK_HOSTING_QUICONFIG_H__
#define __SYMBOID_SDK_HOSTING_QUICONFIG_H__

#include "sdk/hosting/defs.h"
#include "sdk/hosting/qconfig.h"

class SDK_HOSTING_API QUiConfig : public QConfigNode
{
    Q_OBJECT
public:
    QUiConfig(const QString& id, QAbstractConfig* parentNode, const char* parentSignal);

    Q_CONFIG_PROPERTY(QString, style, "Universal")

    Q_PROPERTY(int styleIndex READ styleIndex NOTIFY styleIndexChanged)
    int styleIndex() const;
signals:
    void styleIndexChanged();

public:
    Q_PROPERTY(QStringList styleModel MEMBER mStyleModel CONSTANT)
private:
    QStringList mStyleModel;
};

#endif // __SYMBOID_SDK_HOSTING_QUICONFIG_H__
