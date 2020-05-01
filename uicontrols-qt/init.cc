
#include "sdk/uicontrols-qt/setup.h"
#include "sdk/uicontrols-qt/init.h"
#include <qglobal.h>

mod_sdk_uicontrols_qt::mod_sdk_uicontrols_qt()
{
    Q_INIT_RESOURCE(sdk_uicontrols_qt);
    load_translator();
}

mod_sdk_uicontrols_qt::~mod_sdk_uicontrols_qt()
{
    Q_CLEANUP_RESOURCE(sdk_uicontrols_qt);
}
