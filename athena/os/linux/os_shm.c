/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.24
   brief:  share memory tool
*/

/**********************************************include****************************************************/
#include "common.h"
#include "os.h"
#include "os_shm.h"

/**********************************************private macro************************************************/

/**********************************************private type************************************************/

/**********************************************static variable************************************************/

/**********************************************function prototype************************************************/

/**********************************************function************************************************/
#ifdef ATHENA_OS_USE_XSI_IPC

/*flag : IPC_CREAT IPC_EXCL*/
AT_RESULT AT_OS_Shm_Create(AT_HANDLE *phShm, AT_INT32 key, AT_INT32 size, AT_INT32 flag)
{
    AT_RESULT eResult = AT_SUCCESS;
    int shmid;

    AT_ASSERT(phShm != AT_NULL);

    shmid = shmget((key_t)key, (size_t)size, (int)flag);

    if (shmid == -1)
    {
        AT_ERR("Create share memory fail!");
        AT_RETURN(AT_FAILURE);
    }

    *phShm = (AT_HANDLE)shmid;

    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Shm_Ctl(AT_HANDLE hShm, AT_INT32 cmd, struct shmid_ds *buf)
{
    AT_RESULT eResult = AT_SUCCESS;
    int shmid;
    int err;

    AT_ASSERT(buf != AT_NULL);

    shmid = (int)hShm;

    err = shmctl(shmid, (int)cmd, buf);

    if (err == -1)
    {
        AT_ERR("Control share memory fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

/*flag : SHM_RDONLY*/
AT_RESULT AT_OS_Shm_At(AT_HANDLE hShm, const AT_VOID *addr, AT_INT32 flag, AT_VOID *ptr)
{
    AT_RESULT eResult = AT_SUCCESS;
    int shmid;
    void *buf;

    AT_ASSERT(addr != AT_NULL);

    shmid = (int)hShm;

    buf = shmat(shmid, addr, (int)flag);

    if (buf == (void *)-1)
    {
        AT_ERR("Address share memory fail!");
        AT_RETURN(AT_FAILURE);
    }

    ptr = buf;

    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Shm_Dt(const AT_VOID *addr)
{
    AT_RESULT eResult = AT_SUCCESS;
    int err;

    AT_ASSERT(addr != AT_NULL);

    err = shmdt(addr);

    if (err == -1)
    {
        AT_ERR("Dt share memory fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

#else

AT_RESULT AT_OS_Shm_Create(AT_HANDLE *phShm, const AT_CHAR *name)
{
    AT_RESULT eResult = AT_SUCCESS;
    int shmid;
    int oflag;
    mode_t mode;

    AT_ASSERT(phShm != AT_NULL);
    AT_ASSERT(name != AT_NULL);
    
    oflag = O_RDWR | O_CREAT | O_EXCL;
    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;

    shmid = shm_open(name, oflag, mode);

    if (shmid == -1)
    {
        AT_ERR("Create share memory fail!");
        AT_RETURN(AT_FAILURE);
    }

    *phShm = (AT_HANDLE)shmid;

    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Shm_Destroy(const AT_CHAR *name)
{
    AT_RESULT eResult = AT_SUCCESS;
    int err;

    AT_ASSERT(name != AT_NULL);

    err = shm_unlink(name);

    if (err == -1)
    {
        AT_ERR("Destroy share memory fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

#endif

