/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.23
   brief:  semaphore tool
*/

/**********************************************include****************************************************/
#include "common.h"
#include "os.h"
#include "os_semaphore.h"

/**********************************************private macro************************************************/

/**********************************************private type************************************************/

/**********************************************static variable************************************************/

/**********************************************function prototype************************************************/

/**********************************************function************************************************/
#ifdef ATHENA_OS_USE_XSI_IPC

/*flag : IPC_CREAT IPC_EXCL*/
AT_RESULT AT_OS_Semaphore_Create(AT_HANDLE *phSemaphore, AT_INT32 key, AT_INT32 nsem, AT_INT32 flag)
{
    AT_RESULT eResult = AT_SUCCESS;
    int semid;

    AT_ASSERT(phSemaphore != AT_NULL);

    semid = semget((key_t)key, (int)nsem, (int)flag);

    if (semid == -1)
    {
        AT_ERR("Create semaphore fail!");
        AT_RETURN(AT_FAILURE);
    }

    *phSemaphore = (AT_HANDLE)semid;

    AT_RETURN(eResult);
}

/*cmd : IPC_STAT IPC_SET IPC_RMID GETVAL SETVAL GETPID GETNCNT GETZCNT GETALL SETALL*/
AT_RESULT AT_OS_Semaphore_Ctl(AT_HANDLE hSemaphore, AT_INT32 semnum, AT_INT32 cmd, union semun arg, AT_INT32 *pRet)
{
    AT_RESULT eResult = AT_SUCCESS;
    int semid;
    int ret;
    
    AT_ASSERT(pRet != AT_NULL);

    semid = (int)hSemaphore;

    ret = semctl(semid, (int)semnum, (int)cmd, arg);

    switch (cmd)
    {
        case GETVAL:
        case GETPID:
        case GETNCNT:
        case GETZCNT:
        {
            *pRet = (AT_INT32)ret;
        }
        break;        

        case IPC_STAT:
        case IPC_SET:
        case IPC_RMID:
        case SETVAL:
        case GETALL:
        case SETALL:
        {
            if (ret == -1)
            {
                AT_ERR("Semaphore control fail!");
                AT_RETURN(AT_FAILURE);
            }
        }
        break;

        default:
            AT_ERR("Cmd not support!");
            break;
    }

    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Semaphore_Option(AT_HANDLE hSemaphore, struct sembuf semoparray[], AT_INT32 nops)
{
    AT_RESULT eResult = AT_SUCCESS;
    int semid;
    int ret;
    
    semid = (int)hSemaphore;

    ret = semop(semid, semoparray, (size_t)nops);

    if (ret == -1)
    {
        AT_ERR("Semaphore op fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}
#else

#define ATHENA_OS_USE_NAME_SEMAPHORE
#ifdef ATHENA_OS_USE_NAME_SEMAPHORE
/*oflag 0,O_CREAT,O_EXCL*/
AT_RESULT AT_OS_Semaphore_Create(AT_HANDLE *phSemaphore, const AT_CHAR *name, AT_UINT32 value)
{
    AT_RESULT eResult = AT_SUCCESS;
    sem_t *sem;
    int oflag;
    mode_t mode;

    AT_ASSERT(phSemaphore != AT_NULL);
    AT_ASSERT(name != AT_NULL);
    
    oflag = O_RDWR | O_CREAT | O_EXCL;
    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;

    sem = sem_open(name, oflag, mode, (unsigned int)value);

    if (sem == SEM_FAILED)
    {
        AT_ERR("Create semaphore fail!");
        AT_RETURN(AT_FAILURE);
    }

    *phSemaphore = (AT_HANDLE)sem;

    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Semaphore_Close(AT_HANDLE hSemaphore)
{
    AT_RESULT eResult = AT_SUCCESS;
    sem_t *sem;
    int err;

    AT_ASSERT((sem_t *)hSemaphore != AT_NULL);

    sem = (sem_t *)hSemaphore;

    err = sem_close(sem);

    if (err == -1)
    {
        AT_ERR("Close semaphore fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Semaphore_Destory(const AT_CHAR *name)
{
    AT_RESULT eResult = AT_SUCCESS;
    int err;

    AT_ASSERT(name != AT_NULL);

    err = sem_unlink(name);

    if (err == -1)
    {
        AT_ERR("Destory semaphore fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

#else

AT_RESULT AT_OS_Semaphore_Create(AT_HANDLE hSemaphore, AT_INT32 pshared, AT_UINT32 value)
{
    AT_RESULT eResult = AT_SUCCESS;
    sem_t *sem;
    int err;

    AT_ASSERT((sem_t *)hSemaphore != AT_NULL);

    sem = (sem_t *)hSemaphore;

    err = sem_init(sem, (int)pshared, (unsigned int)value);

    if (err == -1)
    {
        AT_ERR("Create semaphore fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Semaphore_Destory(AT_HANDLE hSemaphore)
{
    AT_RESULT eResult = AT_SUCCESS;
    sem_t *sem;
    int err;

    AT_ASSERT((sem_t *)hSemaphore != AT_NULL);

    sem = (sem_t *)hSemaphore;

    err = sem_destroy(sem);

    if (err == -1)
    {
        AT_ERR("Detory semaphore fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

#endif


AT_RESULT AT_OS_Semaphore_DestoryByName(const AT_CHAR *name)
{
    AT_RESULT eResult = AT_SUCCESS;
    int err;

    AT_ASSERT(name != AT_NULL);

    err = sem_unlink(name);

    if (err == -1)
    {
        AT_ERR("Destory semaphore fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Semaphore_Wait(AT_HANDLE hSemaphore)
{
    AT_RESULT eResult = AT_SUCCESS;
    sem_t *sem;
    int err;

    AT_ASSERT((sem_t *)hSemaphore != AT_NULL);

    sem = (sem_t *)hSemaphore;

    err = sem_wait(sem);

    if (err == -1)
    {
        AT_ERR("Wait semaphore fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Semaphore_TryWait(AT_HANDLE hSemaphore)
{
    AT_RESULT eResult = AT_SUCCESS;
    sem_t *sem;
    int err;

    AT_ASSERT((sem_t *)hSemaphore != AT_NULL);

    sem = (sem_t *)hSemaphore;

    err = sem_trywait(sem);

    if (err == -1)
    {
        AT_ERR("Try wait semaphore fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Semaphore_Release(AT_HANDLE hSemaphore)
{
    AT_RESULT eResult = AT_SUCCESS;
    sem_t *sem;
    int err;

    AT_ASSERT((sem_t *)hSemaphore != AT_NULL);

    sem = (sem_t *)hSemaphore;

    err = sem_post(sem);

    if (err == -1)
    {
        AT_ERR("Post semaphore fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

#endif


