
#ifndef __SYMBOID_SDK_ARCH_DEFS_H__
#define __SYMBOID_SDK_ARCH_DEFS_H__

// API macros
#ifdef _MSC_VER
#   define SY_API_EXPORT __declspec(dllexport)
#   define SY_API_IMPORT __declspec(dllimport)
#else // _MSC_VER
#   define SY_API_EXPORT __attribute__((visibility("default")))
#   define SY_API_IMPORT __attribute__((visibility("default")))
#endif // _MSV_VER

#ifdef BUILD_SDK_ARCH
    #define SDK_ARCH_API SY_API_EXPORT
#else
    #define SDK_ARCH_API SY_API_IMPORT
#endif

// API namespaces
#define sy_ns_begin(_ns_name) namespace _ns_name {
#define sy_ns_end }

#define sym_ns_begin sy_ns_begin(sym)
#define sym_ns_end sy_ns_end

#define arh_ns_begin sy_ns_begin(arh)
#define arh_ns_end sy_ns_end

// Platform macros.
#if defined __EMSCRIPTEN__
#   define SY_PLATFORM_IS_OSX 0
#   define SY_PLATFORM_IS_POSIX 1
#   define SY_PLATFORM_IS_WIN 0
#   define SY_PLATFORM_IS_WIN32 0
#   define SY_PLATFORM_IS_WIN64 0
#   define SY_PLATFORM_IS_ANDROID 0
#   define SY_PLATFORM_IS_WASM 1
#elif defined __APPLE__
#   define SY_PLATFORM_IS_OSX 1
#   define SY_PLATFORM_IS_POSIX 1
#   define SY_PLATFORM_IS_WIN 0
#   define SY_PLATFORM_IS_WIN32 0
#   define SY_PLATFORM_IS_WIN64 0
#   define SY_PLATFORM_IS_ANDROID 0
#   define SY_PLATFORM_IS_WASM 0
#elif defined _WIN64
#   define SY_PLATFORM_IS_OSX 0
#   define SY_PLATFORM_IS_POSIX 0
#   define SY_PLATFORM_IS_WIN 1
#   define SY_PLATFORM_IS_WIN32 0
#   define SY_PLATFORM_IS_WIN64 1
#   define SY_PLATFORM_IS_ANDROID 0
#   define SY_PLATFORM_IS_WASM 0
#elif defined _WIN32
#   define SY_PLATFORM_IS_OSX 0
#   define SY_PLATFORM_IS_POSIX 0
#   define SY_PLATFORM_IS_WIN 1
#   define SY_PLATFORM_IS_WIN32 1
#   define SY_PLATFORM_IS_WIN64 0
#   define SY_PLATFORM_IS_ANDROID 0
#   define SY_PLATFORM_IS_WASM 0
#elif defined ANDROID || defined __ANDROID__
#   define SY_PLATFORM_IS_OSX 0
#   define SY_PLATFORM_IS_POSIX 1
#   define SY_PLATFORM_IS_WIN 0
#   define SY_PLATFORM_IS_WIN32 0
#   define SY_PLATFORM_IS_WIN64 0
#   define SY_PLATFORM_IS_ANDROID 1
#   define SY_PLATFORM_IS_WASM 0
#elif defined __linux__
#   define SY_PLATFORM_IS_OSX 0
#   define SY_PLATFORM_IS_POSIX 1
#   define SY_PLATFORM_IS_WIN 0
#   define SY_PLATFORM_IS_WIN32 0
#   define SY_PLATFORM_IS_WIN64 0
#   define SY_PLATFORM_IS_ANDROID 0
#   define SY_PLATFORM_IS_WASM 0
#else
#   error "Unsupported Platform!"
#endif

#endif // __SYMBOID_SDK_ARCH_DEFS_H__
