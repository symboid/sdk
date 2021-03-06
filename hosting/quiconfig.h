
#ifndef __SYMBOID_SDK_HOSTING_QUICONFIG_H__
#define __SYMBOID_SDK_HOSTING_QUICONFIG_H__

#include "sdk/hosting/defs.h"
#include "sdk/hosting/qconfig.h"

class SDK_HOSTING_API QUiConfig : public QConfigNode
{
    Q_OBJECT
public:
    QUiConfig(const QString& id, QAbstractConfig* parentNode, const char* parentSignal);

    static const char* DEFAULT_STYLE;
    Q_CONFIG_PROPERTY(QString, style, DEFAULT_STYLE)

    Q_PROPERTY(int styleIndex READ styleIndex NOTIFY styleIndexChanged)
    int styleIndex() const;
signals:
    void styleIndexChanged();

public:
    Q_PROPERTY(QStringList styleModel MEMBER mStyleModel CONSTANT)
private:
    QStringList mStyleModel;

public:
    Q_CONFIG_PROPERTY(bool, high_dpi_scaling, false)
};

#endif // __SYMBOID_SDK_HOSTING_QUICONFIG_H__
