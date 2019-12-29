
#ifndef __SYMBOID_SDK_BASICS_CONFIGS_WIN_PROD_CTX_CONFIG_H__
#define __SYMBOID_SDK_BASICS_CONFIGS_WIN_PROD_CTX_CONFIG_H__

#include "sdk/basics/contexts.h"
#include "sdk/basics/typecontexts/std_string.h"

namespace ctx {

// os default
namespace os { typedef win current; }

// build default
namespace build { typedef release config; }

// running context default
namespace run { typedef prod env; }

// default string type
typedef types::std_string string;

} // namespace ctx

#endif // __SYMBOID_SDK_BASICS_CONFIGS_WIN_PROD_CTX_CONFIG_H__
