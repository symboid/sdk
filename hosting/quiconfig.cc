
#include "sdk/hosting/setup.h"
#include "sdk/hosting/quiconfig.h"

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
