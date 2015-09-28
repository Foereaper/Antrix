/****************************************************************************
*
* General Object Type File
* Copyright (c) 2007 Antrix Team
*
* This file may be distributed under the terms of the Q Public License
* as defined by Trolltech ASA of Norway and appearing in the file
* COPYING included in the packaging of this file.
*
* This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
* WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
*/

#ifndef WOWSERVER_COMMON_H
#define WOWSERVER_COMMON_H

#ifdef WIN32
#pragma warning(disable:4996)
#endif

enum TimeVariables
{
    TIME_SECOND = 1,
    TIME_MINUTE = TIME_SECOND * 60,
    TIME_HOUR = TIME_MINUTE * 60,
    TIME_DAY = TIME_HOUR * 24,
};

enum MsTimeVariables
{
    MSTIME_SECOND = 1000,
    MSTIME_MINUTE = MSTIME_SECOND * 60,
    MSTIME_HOUR = MSTIME_MINUTE * 60,
    MSTIME_DAY = MSTIME_HOUR * 24,
};

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <signal.h>
#include <assert.h>

// current platform and compiler
#define PLATFORM_WIN32 0
#define PLATFORM_UNIX  1
#define PLATFORM_APPLE 2

#define UNIX_FLAVOUR_LINUX 1
#define UNIX_FLAVOUR_BSD 2
#define UNIX_FLAVOUR_OTHER 3

#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
#  define PLATFORM PLATFORM_WIN32
#elif defined( __APPLE_CC__ )
#  define PLATFORM PLATFORM_APPLE
#else
#  define PLATFORM PLATFORM_UNIX
#endif

#define COMPILER_MICROSOFT 0
#define COMPILER_GNU	   1
#define COMPILER_BORLAND   2

#ifdef _MSC_VER
#  define COMPILER COMPILER_MICROSOFT
#elif defined( __BORLANDC__ )
#  define COMPILER COMPILER_BORLAND
#elif defined( __GNUC__ )
#  define COMPILER COMPILER_GNU
#else
#  pragma error "FATAL ERROR: Unknown compiler."
#endif

#if PLATFORM == PLATFORM_UNIX || PLATFORM == PLATFORM_APPLE
#ifdef USE_KQUEUE
#define UNIX_FLAVOUR UNIX_FLAVOUR_BSD
#else
#define UNIX_FLAVOUR UNIX_FLAVOUR_LINUX
#endif
#endif

#if COMPILER == COMPILER_MICROSOFT
#  pragma warning( disable : 4267 ) // conversion from 'size_t' to 'int', possible loss of data
#  pragma warning( disable : 4311 ) // 'type cast': pointer truncation from HMODULE to uint32
#  pragma warning( disable : 4786 ) // identifier was truncated to '255' characters in the debug information
#  pragma warning( disable : 4146 )
#  pragma warning( disable : 4800 )
#endif

#if PLATFORM == PLATFORM_WIN32
#define STRCASECMP stricmp
#define _WIN32_WINNT 0x0500
#else
#define STRCASECMP strcasecmp
#endif

#if PLATFORM == PLATFORM_WIN32
#define ASYNC_NET
#endif

#ifdef USE_EPOLL
#define CONFIG_USE_EPOLL
#endif
#ifdef USE_KQUEUE
#define CONFIG_USE_KQUEUE
#endif
#ifdef USE_SELECT
#define CONFIG_USE_SELECT
#endif
#ifdef USE_POLL
#define CONFIG_USE_POLL
#endif

#include <set>
#include <list>
#include <string>
#include <map>
#include <queue>
#include <sstream>
#include <algorithm>
//#include <iostream>

#if defined (__GNUC__)
#  define GCC_VERSION (__GNUC__ * 10000 \
					   + __GNUC_MINOR__ * 100 \
					   + __GNUC_PATCHLEVEL__)
#endif

#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
#  define WIN32_LEAN_AND_MEAN
//#  define _WIN32_WINNT 0x0500
#  define NOMINMAX
#  include <windows.h>
#  undef NOMINMAX
#else
#  include <string.h>
#  define MAX_PATH 1024
#  if defined (__GNUC__)
#	if GCC_VERSION >= 30400
#         ifdef HAVE_DARWIN
#	      define __fastcall
#         else
#    	      define __fastcall __attribute__((__fastcall__))
#         endif
#	else
#	  define __fastcall __attribute__((__regparm__(3)))
#	endif
#  else
#	define __fastcall __attribute__((__fastcall__))
#  endif
#endif

#if COMPILER == COMPILER_GNU && __GNUC__ >= 3
#include <ext/hash_map>
#include <ext/hash_set>
#elif COMPILER == COMPILER_MICROSOFT && (_MSC_VER > 1500 || _MSC_VER == 1500 && _HAS_TR1)   // VC9.0 SP1 and later
#  include <unordered_map>
#  include <unordered_set>
#endif

#ifdef CONFIG_USE_SELECT
#undef FD_SETSIZE
#define FD_SETSIZE 2048 
#endif

#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>
#endif

#ifdef _STLPORT_VERSION
#define HM_NAMESPACE std
using std::hash_map;
using std::hash_set;
#elif COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1600
#  define UNORDERED_MAP std::unordered_map
#  define UNORDERED_SET std::unordered_set
#  define HASH_NAMESPACE_START namespace std {
#  define HASH_NAMESPACE_END }
#elif COMPILER == COMPILER_INTEL
#define HM_NAMESPACE std
using std::hash_map;
using std::hash_set;
#elif COMPILER == COMPILER_GNU && __GNUC__ >= 3
#define HM_NAMESPACE __gnu_cxx
using __gnu_cxx::hash_map;
using __gnu_cxx::hash_set;

namespace __gnu_cxx
{
    template<> struct hash<unsigned long long>
    {
        size_t operator()(const unsigned long long &__x) const { return (size_t)__x; }
    };
    template<typename T> struct hash<T *>
    {
        size_t operator()(T * const &__x) const { return (size_t)__x; }
    };

};

#else
#define HM_NAMESPACE std
using std::hash_map;
#endif

/* Use correct types for x64 platforms, too */
#if COMPILER != COMPILER_GNU
typedef signed __int64 int64;
typedef signed __int32 int32;
typedef signed __int16 int16;
typedef signed __int8 int8;

typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef unsigned __int16 uint16;
typedef unsigned __int8 uint8;
#else

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;
typedef uint32_t DWORD;

#endif

/* Define this if you're using a big-endian machine (todo: replace with autoconf */
/*#define USING_BIG_ENDIAN 1*/

/* these can be optimized into assembly */
inline static void swap16(uint16* p) { *p = (*p >> 8) | (*p << 8); }
inline static void swap32(uint32* p) { *p = (*p >> 24) | ((*p >> 8) & 0xff00) | ((*p << 8) & 0xff0000) | (*p << 24); }
inline static void swap64(uint64* p) {
    *p = ((*p >> 56)) | ((*p >> 40) & 0x000000000000ff00ULL) | ((*p >> 24) & 0x0000000000ff0000ULL) | ((*p >> 8) & 0x00000000ff000000ULL) |
        ((*p << 8) & 0x000000ff00000000ULL) | ((*p << 24) & 0x0000ff0000000000ULL) | ((*p << 40) & 0x00ff000000000000ULL) | ((*p << 56));
}
inline static float swapfloat(float p)
{
    union { float asfloat; uint8 asbytes[4]; } u1, u2;
    u1.asfloat = p;
    /* swap! */
    u2.asbytes[0] = u1.asbytes[3];
    u2.asbytes[1] = u1.asbytes[2];
    u2.asbytes[2] = u1.asbytes[1];
    u2.asbytes[3] = u1.asbytes[0];

    return u2.asfloat;
}

inline static double swapdouble(double p)
{
    union { double asfloat; uint8 asbytes[8]; } u1, u2;
    u1.asfloat = p;
    /* swap! */
    u2.asbytes[0] = u1.asbytes[7];
    u2.asbytes[1] = u1.asbytes[6];
    u2.asbytes[2] = u1.asbytes[5];
    u2.asbytes[3] = u1.asbytes[4];
    u2.asbytes[4] = u1.asbytes[3];
    u2.asbytes[5] = u1.asbytes[2];
    u2.asbytes[6] = u1.asbytes[1];
    u2.asbytes[7] = u1.asbytes[0];

    return u2.asfloat;
}

inline static void swapfloat(float * p)
{
    union { float asfloat; uint8 asbytes[4]; } u1, u2;
    u1.asfloat = *p;
    /* swap! */
    u2.asbytes[0] = u1.asbytes[3];
    u2.asbytes[1] = u1.asbytes[2];
    u2.asbytes[2] = u1.asbytes[1];
    u2.asbytes[3] = u1.asbytes[0];
    *p = u2.asfloat;
}

inline static void swapdouble(double * p)
{
    union { double asfloat; uint8 asbytes[8]; } u1, u2;
    u1.asfloat = *p;
    /* swap! */
    u2.asbytes[0] = u1.asbytes[7];
    u2.asbytes[1] = u1.asbytes[6];
    u2.asbytes[2] = u1.asbytes[5];
    u2.asbytes[3] = u1.asbytes[4];
    u2.asbytes[4] = u1.asbytes[3];
    u2.asbytes[5] = u1.asbytes[2];
    u2.asbytes[6] = u1.asbytes[1];
    u2.asbytes[7] = u1.asbytes[0];
    *p = u2.asfloat;
}

inline static uint16 swap16(uint16 p) { return (p >> 8) | (p << 8); }
inline static uint32 swap32(uint32 p) { return (p >> 24) | ((p >> 8) & 0xff00) | ((p << 8) & 0xff0000) | (p << 24); }
inline static uint64 swap64(uint64 p) {
    p = ((p >> 56)) | ((p >> 40) & 0x000000000000ff00ULL) | ((p >> 24) & 0x0000000000ff0000ULL) | ((p >> 8) & 0x00000000ff000000ULL) |
        ((p << 8) & 0x000000ff00000000ULL) | ((p << 24) & 0x0000ff0000000000ULL) | ((p << 40) & 0x00ff000000000000ULL) | ((p << 56));
}

inline static void swap16(int16* p) { *p = (*p >> 8) | (*p << 8); }
inline static void swap32(int32* p) { *p = (*p >> 24) | ((*p >> 8) & 0xff00) | ((*p << 8) & 0xff0000) | (*p << 24); }
inline static void swap64(int64* p) {
    *p = ((*p >> 56)) | ((*p >> 40) & 0x000000000000ff00ULL) | ((*p >> 24) & 0x0000000000ff0000ULL) | ((*p >> 8) & 0x00000000ff000000ULL) |
        ((*p << 8) & 0x000000ff00000000ULL) | ((*p << 24) & 0x0000ff0000000000ULL) | ((*p << 40) & 0x00ff000000000000ULL) | ((*p << 56));
}

inline static int16 swap16(int16 p) { return (p >> 8) | (p << 8); }
inline static int32 swap32(int32 p) { return (p >> 24) | ((p >> 8) & 0xff00) | ((p << 8) & 0xff0000) | (p << 24); }
inline static int64 swap64(int64 p) {
    p = ((p >> 56)) | ((p >> 40) & 0x000000000000ff00ULL) | ((p >> 24) & 0x0000000000ff0000ULL) | ((p >> 8) & 0x00000000ff000000ULL) |
        ((p << 8) & 0x000000ff00000000ULL) | ((p << 24) & 0x0000ff0000000000ULL) | ((p << 40) & 0x00ff000000000000ULL) | ((p << 56));
}

/*
Scripting system exports/imports
*/

#ifdef WIN32
#ifndef SCRIPTLIB
#define SERVER_DECL __declspec(dllexport)
#define SCRIPT_DECL __declspec(dllimport)
#else
#define SERVER_DECL __declspec(dllimport)
#define SCRIPT_DECL __declspec(dllexport)
#endif
#else
#define SERVER_DECL 
#define SCRIPT_DECL 
#endif

// Include all threading files
#include <assert.h>
#include "Threading/Threading.h"

#include "MersenneTwister.h"

#if COMPILER == COMPILER_MICROSOFT

#define I64FMT "%016I64X"
#define I64FMTD "%I64u"
#define SI64FMTD "%I64d"
#define snprintf _snprintf
#define atoll __atoi64

#else

#define stricmp strcasecmp
#define strnicmp strncasecmp
#define I64FMT "%016llX"
#define I64FMTD "%llu"
#define SI64FMTD "%lld"

#endif

#define GUID_HIPART(x) (*(((uint32*)&(x))+1))
#define GUID_LOPART(x) (*((uint32*)&(x)))
#define UINT32_HIPART(x) (*(((uint16*)&(x))+1))
#define UINT32_LOPART(x) (*((uint16*)&(x)))

#define atol(a) strtoul( a, NULL, 10)

#define STRINGIZE(a) #a

// fix buggy MSVC's for variable scoping to be reliable =S
#define for if(true) for

#ifdef GNL_BIG_ENDIAN
#  define GNL_LOWER_WORD_BYTE	4
#else
#  define GNL_LOWER_WORD_BYTE	0
#endif

#define GNL_LONG_AT_BYTE(x,b)	*(long *)(((char *)&x) + b)
#define FIST_MAGIC_QROUND (((65536.0 * 65536.0 * 16.0) + (65536.0 * 0.5)) * 65536.0)

/// Fastest Method of float2int32
static inline int float2int32(const float value)
{
    union { int asInt[2]; double asDouble; } n;
    n.asDouble = value + 6755399441055744.0;

#if GNL_BIG_ENDIAN
    return n.asInt[1];
#else
    return n.asInt[0];
#endif
}

/// Fastest Method of long2int32
static inline int long2int32(const double value)
{
    union { int asInt[2]; double asDouble; } n;
    n.asDouble = value + 6755399441055744.0;

#if GNL_BIG_ENDIAN
    return n.asInt[1];
#else
    return n.asInt[0];
#endif
}

/// Round a floating-point value and convert to integer
static inline long QRound(double inval)
{
    double dtemp = FIST_MAGIC_QROUND + inval;
    return GNL_LONG_AT_BYTE(dtemp, GNL_LOWER_WORD_BYTE) - 0x80000000;
}

/// Convert a float to a cross-platform 32-bit format (no endianess adjustments!)
static inline long float2long(float f)
{
    int exp;
    long mant = QRound(frexp(f, &exp) * 0x1000000);
    long sign = mant & 0x80000000;
    if (mant < 0) mant = -mant;
    if (exp > 63) exp = 63; else if (exp < -64) exp = -64;
    return sign | ((exp & 0x7f) << 24) | (mant & 0xffffff);
}

/// Convert a 32-bit cross-platform float to native format (no endianess adjustments!)
static inline float long2float(long l)
{
    int exp = (l >> 24) & 0x7f;
    if (exp & 0x40) exp = exp | ~0x7f;
    float mant = float(l & 0x00ffffff) / 0x1000000;
    if (l & 0x80000000) mant = -mant;
    return (float)ldexp(mant, exp);
}

#ifndef max
#define max(a,b) ((a)>(b))?(a):(b)
#define min(a,b) ((a)<(b))?(a):(b)
#endif

#ifndef WIN32
#include <sys/timeb.h>
#endif

inline uint32 now()
{
#ifdef WIN32
    return GetTickCount();
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#endif
}

#ifndef WIN32
#define FALSE   0
#define TRUE	1
#endif

#ifndef WIN32
#define Sleep(ms) usleep(1000*ms)
#endif

#ifdef WIN32
#ifndef __SHOW_STUPID_WARNINGS__
#pragma warning(disable:4018)
#pragma warning(disable:4244)
#pragma warning(disable:4305) 
#pragma warning(disable:4748)
#pragma warning(disable:4800) 
#pragma warning(disable:4996)
#pragma warning(disable:4251)
#endif	  
#endif

#undef INTEL_COMPILER
#ifdef INTEL_COMPILER
#pragma warning(disable:279)
#pragma warning(disable:1744)
#pragma warning(disable:1740)
#endif

#include "Util.h"
struct WayPoint
{
    WayPoint()
    {
        o = 0.0f;
    }
    uint32 id;
    float x;
    float y;
    float z;
    float o;
    uint32 waittime; //ms
    uint32 flags;
    bool forwardemoteoneshot;
    uint32 forwardemoteid;
    bool backwardemoteoneshot;
    uint32 backwardemoteid;
    uint32 forwardskinid;
    uint32 backwardskinid;

};

typedef UNORDERED_MAP<uint32, WayPoint*> WayPointMap;

#endif
