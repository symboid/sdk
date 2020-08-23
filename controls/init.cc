
#include "sdk/controls/setup.h"
#include "sdk/controls/init.h"
#include <qglobal.h>

mod_sdk_controls::mod_sdk_controls()
{
    Q_INIT_RESOURCE(sdk_controls);
    load_translator();
}

mod_sdk_controls::~mod_sdk_controls()
{
    Q_CLEANUP_RESOURCE(sdk_controls);
}
