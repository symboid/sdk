
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/init.h"
#include <qglobal.h>

mod_sdk_dox_qt::mod_sdk_dox_qt()
{
    Q_INIT_RESOURCE(sdk_dox_qt);
}

mod_sdk_dox_qt::~mod_sdk_dox_qt()
{
    Q_CLEANUP_RESOURCE(sdk_dox_qt);
}
