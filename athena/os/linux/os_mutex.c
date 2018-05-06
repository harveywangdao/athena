/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.13
   brief:  mutex tool
*/

/**********************************************include****************************************************/
#include "common.h"
#include "os.h"
#include <pthread.h>
#include <string.h>

/**********************************************private macro************************************************/

/**********************************************private type************************************************/

/**********************************************static variable************************************************/

/**********************************************function prototype************************************************/

/**********************************************function************************************************/
AT_RESULT AT_OS_Mutex_Create(AT_HANDLE hMutex,
                                     const char *sMutexName,
                                     AT_INT32 nPriority)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_mutex_t mut;
    pthread_mutexattr_t attr;
    int shared;
    int kind;
    int protocol;
    int robustness;
    int err;

    AT_ASSERT((pthread_mutex_t*)hMutex != AT_NULL);
    AT_ASSERT(sMutexName != AT_NULL);

    err = pthread_mutexattr_init(&attr);
    if (err != 0)
    {
        AT_ERR("pthread_mutexattr_init fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

/*
pthread_mutexattr_getprioceiling
pthread_mutexattr_setprioceiling
*/

    err = pthread_mutexattr_getrobust(&attr, &robustness);
    if (err != 0)
    {
        AT_ERR("pthread_mutexattr_getrobust fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    AT_PRINT("mutex robustness mode = %d.\n", robustness);
  
    robustness = PTHREAD_MUTEX_STALLED;/*PTHREAD_MUTEX_ROBUST*/
    
    err = pthread_mutexattr_setrobust(&attr, robustness);
    if (err != 0)
    {
        AT_ERR("pthread_mutexattr_setrobust fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    err = pthread_mutexattr_getprotocol(&attr, &protocol);
    if (err != 0)
    {
        AT_ERR("pthread_mutexattr_getprotocol fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    AT_PRINT("mutex protocol mode = %d.\n", protocol);
  
    protocol = PTHREAD_PRIO_NONE;/*PTHREAD_PRIO_INHERIT PTHREAD_PRIO_PROTECT*/
    
    err = pthread_mutexattr_setprotocol(&attr, protocol);
    if (err != 0)
    {
        AT_ERR("pthread_mutexattr_setprotocol fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    err = pthread_mutexattr_gettype(&attr, &kind);
    if (err != 0)
    {
        AT_ERR("pthread_mutexattr_gettype fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    AT_PRINT("mutex kind mode = %d.\n", kind);
  
    kind = PTHREAD_MUTEX_NORMAL;/*PTHREAD_MUTEX_RECURSIVE PTHREAD_MUTEX_ERRORCHECK PTHREAD_MUTEX_DEFAULT*/
    
    err = pthread_mutexattr_settype(&attr, kind);
    if (err != 0)
    {
        AT_ERR("pthread_mutexattr_settype fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    err = pthread_mutexattr_getpshared(&attr, &shared);
    if (err != 0)
    {
        AT_ERR("pthread_mutexattr_getpshared fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    AT_PRINT("mutex share mode = %d.\n", shared);
  
    shared = PTHREAD_PROCESS_PRIVATE;/*PTHREAD_PROCESS_SHARED*/

    err = pthread_mutexattr_setpshared(&attr, shared);
    if (err != 0)
    {
        AT_ERR("pthread_mutexattr_setpshared fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    err = pthread_mutex_init(&mut, &attr);
    if (err != 0)
    {
        AT_ERR("Create mutex fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    memcpy((pthread_mutex_t*)hMutex, &mut, sizeof(pthread_mutex_t));

    err = pthread_mutexattr_destroy(&attr);
    if (err != 0)
    {
        AT_ERR("pthread_mutexattr_destroy fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Mutex_Destroy(AT_HANDLE hMutex)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_mutex_t *mut;
    int err;
    
    AT_ASSERT((pthread_mutex_t*)hMutex != AT_NULL);
    
    mut = (pthread_mutex_t*)hMutex;

    err = pthread_mutex_destroy(mut);
    if (err != 0)
    {
        AT_ERR("Destroy mutex fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Mutex_Lock(AT_HANDLE hMutex)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_mutex_t *mut;
    int err;
    
    AT_ASSERT((pthread_mutex_t*)hMutex != AT_NULL);
    mut = (pthread_mutex_t*)hMutex;

    err = pthread_mutex_lock(mut);
    if (err != 0)
    {
        AT_ERR("Lock mutex fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Mutex_Trylock(AT_HANDLE hMutex)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_mutex_t *mut;
    int err;
    
    AT_ASSERT((pthread_mutex_t*)hMutex != AT_NULL);
    mut = (pthread_mutex_t*)hMutex;

    err = pthread_mutex_trylock(mut);
    if (err != 0)
    {
        AT_ERR("Try lock mutex fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

/* absolute time*/
AT_RESULT AT_OS_Mutex_Timedlock(AT_HANDLE hMutex, AT_INT32 nMilliSec)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_mutex_t *mut;
    struct timespec ts;
    int err;
    
    AT_ASSERT((pthread_mutex_t*)hMutex != AT_NULL);
    mut = (pthread_mutex_t*)hMutex;
    ts.tv_sec = nMilliSec / 1000;
    ts.tv_nsec = (nMilliSec % 1000) * 1000000;

    err = pthread_mutex_timedlock(mut, &ts);
    if (err != 0)
    {
        AT_ERR("Timed lock mutex fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Mutex_Unlock(AT_HANDLE hMutex)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_mutex_t *mut;
    int err;
    
    AT_ASSERT((pthread_mutex_t*)hMutex != AT_NULL);
    mut = (pthread_mutex_t*)hMutex;

    err = pthread_mutex_unlock(mut);
    if (err != 0)
    {
        AT_ERR("Unlock mutex fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


