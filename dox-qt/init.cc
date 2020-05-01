
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/init.h"
#include <qglobal.h>

mod_sdk_dox_qt::mod_sdk_dox_qt()
{
    _reg_json_sync_node.register_as("DocumentNode");
    Q_INIT_RESOURCE(sdk_dox_qt);
    load_translator();
}

mod_sdk_dox_qt::~mod_sdk_dox_qt()
{
    Q_CLEANUP_RESOURCE(sdk_dox_qt);
}
