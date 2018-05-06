/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.27
   brief:  malloc memory tool interface
*/

#ifndef __OS_MEMORY_H__
#define __OS_MEMORY_H__

/**********************************************include****************************************************/
#include "athena_config.h"

/**********************************************export macro************************************************/
#define AT_MALLOC(size) AT_OS_Memory_Malloc(size)
#define AT_FREE(p) AT_OS_Memory_Free(p)

/**********************************************export type************************************************/

/**********************************************export function************************************************/
AT_VOID *AT_OS_Memory_Malloc(AT_UINT32 size);
AT_VOID AT_OS_Memory_Free(AT_VOID *ptr);


#endif


