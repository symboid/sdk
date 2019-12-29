
#ifndef __SYMBOID_SDK_BASICS_DEFS_H__
#define __SYMBOID_SDK_BASICS_DEFS_H__

#ifdef _MSC_VER
#   define SY_API_EXPORT __declspec(dllexport)
#   define SY_API_IMPORT __declspec(dllimport)
#else // _MSC_VER
#   define SY_API_EXPORT __attribute__((visibility("default")))
#   define SY_API_IMPORT __attribute__((visibility("default")))
#endif // _MSV_VER

/// Platform macros.
#if defined __APPLE__
#   define SY_PLATFORM_IS_OSX 1
#   define SY_PLATFORM_IS_POSIX 1
#   define SY_PLATFORM_IS_WIN 0
#   define SY_PLATFORM_IS_WIN32 0
#   define SY_PLATFORM_IS_WIN64 0
#   define SY_PLATFORM_IS_ANDROID 0
#elif defined _WIN64
#   define SY_PLATFORM_IS_OSX 0
#   define SY_PLATFORM_IS_POSIX 0
#   define SY_PLATFORM_IS_WIN 1
#   define SY_PLATFORM_IS_WIN32 0
#   define SY_PLATFORM_IS_WIN64 1
#   define SY_PLATFORM_IS_ANDROID 0
#elif defined _WIN32
#   define SY_PLATFORM_IS_OSX 0
#   define SY_PLATFORM_IS_POSIX 0
#   define SY_PLATFORM_IS_WIN 1
#   define SY_PLATFORM_IS_WIN32 1
#   define SY_PLATFORM_IS_WIN64 0
#   define SY_PLATFORM_IS_ANDROID 0
#elif defined ANDROID || defined __ANDROID__
#   define SY_PLATFORM_IS_OSX 0
#   define SY_PLATFORM_IS_POSIX 1
#   define SY_PLATFORM_IS_WIN 0
#   define SY_PLATFORM_IS_WIN32 0
#   define SY_PLATFORM_IS_WIN64 0
#   define SY_PLATFORM_IS_ANDROID 1
#elif defined __linux__
#   define SY_PLATFORM_IS_OSX 0
#   define SY_PLATFORM_IS_POSIX 1
#   define SY_PLATFORM_IS_WIN 0
#   define SY_PLATFORM_IS_WIN32 0
#   define SY_PLATFORM_IS_WIN64 0
#   define SY_PLATFORM_IS_ANDROID 0
#else
#   error "Unsupported Platform!"
#endif

/// Compiler macros.
/// Older versions of gcc lacks a number of c++11 features
#if defined __GNUC__ && __GNUC__ < 5
#define SY_COMPILER_FIX11
#endif

#if defined __clang__
#define SY_COMPILER_CLANG
#elif defined __GNUC__
#define SY_COMPILER_GCC
#endif

#define __MK_STRING(param) #param
#define SY_MKSTR(param) __MK_STRING(param)

#define SY_ABS(value) ((value) < 0 ? (-(value)) : (value))

#define SY_UNUSED(x) (void)x

#define SY_MAX(x,y) ((x)>(y)?(x):(y))

#define sy_ns_begin(_ns_name) namespace _ns_name {
#define sy_ns_end }

#define sym_ns_begin sy_ns_begin(sym)
#define sym_ns_end sy_ns_end

#endif // __SYMBOID_SDK_BASICS_DEFS_H__
