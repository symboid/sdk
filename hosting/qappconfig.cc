
#include "sdk/hosting/setup.h"
#include "sdk/hosting/qappconfig.h"

QAppConfig::QAppConfig(QObject* parent) : QConfigNode(parent)
{
    QSettings settings;
    ui()->loadFromSettings(&settings);
    software()->loadFromSettings(&settings);
}

QAppConfig::~QAppConfig()
{
    QSettings settings;
    ui()->saveToSettings(&settings);
    software()->saveToSettings(&settings);
}
