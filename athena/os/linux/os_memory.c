/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.27
   brief:  malloc memory tool
*/

/**********************************************include****************************************************/
#include "common.h"
#include "os.h"
#include <stdlib.h>

/**********************************************private macro************************************************/

/**********************************************private type************************************************/

/**********************************************static variable************************************************/

/**********************************************function prototype************************************************/

/**********************************************function************************************************/
AT_VOID *AT_OS_Memory_Malloc(AT_UINT32 size)
{
    void *ptr;

    ptr = malloc((size_t)size);

    if (ptr)
        return ptr;

    AT_ERR("Malloc memory fail!");
    return AT_NULL;
}

AT_VOID AT_OS_Memory_Free(AT_VOID *ptr)
{
    AT_ASSERT(ptr != AT_NULL);
    free(ptr);
    return;
}

