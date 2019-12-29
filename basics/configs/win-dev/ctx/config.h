
#ifndef __SYMBOID_SDK_BASICS_CONFIGS_WIN_DEV_CTX_CONFIG_H__
#define __SYMBOID_SDK_BASICS_CONFIGS_WIN_DEV_CTX_CONFIG_H__

#include "sdk/basics/contexts.h"
#include "sdk/basics/typecontexts/std_string.h"

namespace ctx {

// os default
namespace os { typedef win current; }

// build default
namespace build { typedef debug config; }

// running context default
namespace run { typedef qmake env; }

// default string type
typedef types::std_string string;

} // namespace ctx

#endif // __SYMBOID_SDK_BASICS_CONFIGS_WIN_DEV_CTX_CONFIG_H__
