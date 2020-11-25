
#include "sdk/hosting/setup.h"
#include "sdk/hosting/quiconfig.h"

QUiConfig::QUiConfig(QConfigNode* parentNode, const char* parentSignal)
    : QConfigNode(tr("Ui"), parentNode, parentSignal)
    , mStyleModel({"Default", "Material", "Universal", "Fusion"})
{
    QSettings settings;
    loadFromSettings(&settings);
}

QUiConfig::~QUiConfig()
{
    QSettings settings;
    saveToSettings(&settings);
}

int QUiConfig::styleIndex() const
{
    const QString currentStyle = style();
    int styleIndex = -1;
    for (int i = 0; styleIndex == -1 && i < mStyleModel.count(); ++i)
    {
        if (mStyleModel[i] == currentStyle)
        {
            styleIndex = i;
        }
    }
    return styleIndex;
}