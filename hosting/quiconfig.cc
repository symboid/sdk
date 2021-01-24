
#include "sdk/hosting/setup.h"
#include "sdk/hosting/quiconfig.h"

QUiConfig::QUiConfig(const QString& id, QAbstractConfig* parentNode, const char* parentSignal)
    : QConfigNode(id, parentNode, parentSignal)
    , mStyleModel({"Default", "Material", "Universal", "Fusion"})
{
}

#if defined(Q_OS_WASM) || defined(Q_OS_ANDROID)
const char* QUiConfig::DEFAULT_STYLE = "Material";
#else
const char* QUiConfig::DEFAULT_STYLE = "Universal";
#endif

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
