
#include "sdk/hosting/setup.h"
#include "sdk/hosting/qsoftwareconfig.h"

QSoftwareConfig::QSoftwareConfig(QConfigNode* parentNode)
    : QConfigNode(tr("Software"), parentNode)
{
}
