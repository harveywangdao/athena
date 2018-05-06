/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.20
   brief:  fifo tool
*/

/**********************************************include****************************************************/
#include "common.h"
#include "os.h"
#include <sys/stat.h>

/**********************************************private macro************************************************/

/**********************************************private type************************************************/

/**********************************************static variable************************************************/

/**********************************************function prototype************************************************/

/**********************************************function************************************************/
AT_RESULT AT_OS_Fifo_Create(const AT_CHAR *path, mode_t mode)
{
    AT_RESULT eResult = AT_SUCCESS;
    int err = 0;

    AT_ASSERT(path != AT_NULL);

    err = mkfifo(path, mode);

    if (err == -1)
    {
        AT_ERR("Create fifo fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

