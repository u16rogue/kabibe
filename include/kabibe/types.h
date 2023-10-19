#pragma once

typedef char               kabibe_i8;
typedef unsigned char      kabibe_u8;
typedef short              kabibe_i16;
typedef unsigned short     kabibe_u16;
typedef int                kabibe_i32;
typedef unsigned int       kabibe_u32;
typedef long long          kabibe_i64;
typedef unsigned long long kabibe_u64;

#define kabibe_nilptr 0
typedef void * kabibe_vptr;

#define kabibe_true  1
#define kabibe_false 0
typedef kabibe_u8 kabibe_bool;

#if defined(KABIBE_HOST_ARCH)
  #if KABIBE_HOST_ARCH == 8
    typedef kabibe_u64 kabibe_uptr;
    typedef kabibe_u64 kabibe_usz;
  #elif KABIBE_HOST_ARCH == 4 
    typedef kabibe_u32 kabibe_uptr;
    typedef kabibe_u32 kabibe_usz;
  #else
    #error "[kabibe] Unknown host arch"
  #endif
#else
  #error "[kabibe] 'KABIBE_HOST_ARCH' is undefined, please check your generated build."
#endif
