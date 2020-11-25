
#include "sdk/hosting/setup.h"
#include "sdk/hosting/qsoftwareconfig.h"

QSoftwareConfig::QSoftwareConfig(QConfigNode* parentNode)
    : QConfigNode("software", tr("Software"), parentNode)
{
}
