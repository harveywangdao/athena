/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.20
   brief:  pipe tool
*/

/**********************************************include****************************************************/
#include "common.h"
#include "os.h"
#include <stdio.h>
#include <unistd.h>

/**********************************************private macro************************************************/

/**********************************************private type************************************************/

/**********************************************static variable************************************************/

/**********************************************function prototype************************************************/

/**********************************************function************************************************/
AT_RESULT AT_OS_Pipe_Create(AT_INT32 arrFd[])
{
    AT_RESULT eResult = AT_SUCCESS;
    int err;

    AT_ASSERT(arrFd != AT_NULL);

    err = pipe(arrFd);
    if (err != 0)
    {
        AT_ERR("Create pipe fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


/*type: r w*/
AT_RESULT AT_OS_Pipe_Open(AT_HANDLE *phFile, const AT_CHAR *cmd, const AT_CHAR *type)
{
    AT_RESULT eResult = AT_SUCCESS;
    FILE *fp;

    AT_ASSERT(phFile != AT_NULL);
    AT_ASSERT(cmd != AT_NULL);
    AT_ASSERT(type != AT_NULL);

    fp = popen(cmd, type);
    if (fp == AT_NULL)
    {
        AT_ERR("Open pipe fail!");
        AT_RETURN(AT_FAILURE);
    }

    *phFile = (AT_HANDLE)fp;
    
    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Pipe_Close(AT_HANDLE hFile)
{
    AT_RESULT eResult = AT_SUCCESS;
    FILE *fp;

    AT_ASSERT((FILE*)hFile != AT_NULL);

    fp = (FILE*)hFile;

    if (pclose(fp) == -1)
    {
        AT_ERR("Close pipe fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}



