
#include "sdk/hosting/setup.h"
#include "sdk/hosting/quiconfig.h"

QUiConfig::QUiConfig(QConfigNode* parentNode, const char* parentSignal)
    : QConfigNode(tr("Ui"), parentNode, parentSignal)
{
    QSettings settings;
    loadFromSettings(&settings);
}

QUiConfig::~QUiConfig()
{
    QSettings settings;
    saveToSettings(&settings);
}
