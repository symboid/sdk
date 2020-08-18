
#include "sdk/dox/setup.h"
#include "sdk/dox/init.h"
#include <qglobal.h>

mod_sdk_dox::mod_sdk_dox()
{
    _reg_json_sync_node.register_as("DocumentNode");
    Q_INIT_RESOURCE(sdk_dox);
    load_translator();
}

mod_sdk_dox::~mod_sdk_dox()
{
    Q_CLEANUP_RESOURCE(sdk_dox);
}
