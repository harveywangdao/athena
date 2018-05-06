/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.07.30
   brief:  base type
*/

#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__
/**********************************************include****************************************************/
#include "athena_config.h"

/**********************************************export macro************************************************/
#define AT_TRUE 1
#define AT_FALSE 0

#define AT_NULL ((void *)0)

#define AT_ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define AT_MIN(a, b) ((a) < (b) ? (a) : (b))
#define AT_MAX(a, b) ((a) > (b) ? (a) : (b))

/**********************************************export type************************************************/
#if (CURRENT_OS == OS_UBUNTU)
typedef signed char AT_INT8;
typedef unsigned char AT_UINT8;
typedef signed short int AT_INT16;
typedef unsigned short int AT_UINT16;
typedef signed int AT_INT32;
typedef unsigned int AT_UINT32;

typedef signed int AT_BOOL;
typedef void AT_VOID;
typedef char AT_CHAR;

typedef float AT_FLOAT;
typedef double AT_DOUBLE;

typedef void * AT_POINTER;

#if (OS_WORD_SIZE == 64)
typedef signed long int AT_INT64;
typedef unsigned long int AT_UINT64;

typedef AT_INT64 AT_HANDLE;

#elif (OS_WORD_SIZE == 32)
typedef signed long long int AT_INT64;
typedef unsigned long long int AT_UINT64;

typedef AT_INT32 AT_HANDLE;
#endif





#elif (CURRENT_OS == OS_WINDOWS)

#endif

/**********************************************export function************************************************/

#endif

