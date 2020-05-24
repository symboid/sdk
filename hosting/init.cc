
#include "sdk/hosting/setup.h"
#include "sdk/hosting/init.h"
#include <qglobal.h>

mod_sdk_hosting::mod_sdk_hosting()
{
    Q_INIT_RESOURCE(sdk_hosting);
    load_translator();
}

mod_sdk_hosting::~mod_sdk_hosting()
{
    Q_CLEANUP_RESOURCE(sdk_hosting);
}
