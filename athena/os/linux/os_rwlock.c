/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.13
   brief:  rwlock tool
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
AT_RESULT AT_OS_RWlock_Create(AT_HANDLE hRwlock,
                                      const char *sRwlockName,
                                      AT_INT32 nPriority)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_rwlock_t rw;
    pthread_rwlockattr_t attr;
    int shared;
    int err;

    AT_ASSERT((pthread_rwlock_t*)hRwlock != AT_NULL);
    AT_ASSERT(sRwlockName != AT_NULL);

    err = pthread_rwlockattr_init(&attr);
    if (err != 0)
    {
        AT_ERR("pthread_rwlockattr_init fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    err = pthread_rwlockattr_getpshared(&attr, &shared);
    if (err != 0)
    {
        AT_ERR("pthread_rwlockattr_getpshared fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    AT_PRINT("rwlock attr shared = %d.\n", shared);
    shared = PTHREAD_PROCESS_PRIVATE;/*PTHREAD_PROCESS_SHARED*/

    err = pthread_rwlockattr_setpshared(&attr, shared);
    if (err != 0)
    {
        AT_ERR("pthread_rwlockattr_setpshared fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    err = pthread_rwlock_init(&rw, &attr);
    if (err != 0)
    {
        AT_ERR("Create rwlock fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    memcpy((pthread_rwlock_t*)hRwlock, &rw, sizeof(pthread_rwlock_t));

    err = pthread_rwlockattr_destroy(&attr);
    if (err != 0)
    {
        AT_ERR("pthread_rwlockattr_destroy fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_RWlock_Destroy(AT_HANDLE hRwlock)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_rwlock_t *rw;
    int err;
    
    AT_ASSERT((pthread_rwlock_t*)hRwlock != AT_NULL);
    rw = (pthread_rwlock_t*)hRwlock;

    err = pthread_rwlock_destroy(rw);
    if (err != 0)
    {
        AT_ERR("Destroy rwlock fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_RWlock_Rdlock(AT_HANDLE hRwlock)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_rwlock_t *rw;
    int err;
    
    AT_ASSERT((pthread_rwlock_t*)hRwlock != AT_NULL);
    rw = (pthread_rwlock_t*)hRwlock;

    err = pthread_rwlock_rdlock(rw);
    if (err != 0)
    {
        AT_ERR("Rdlock rwlock fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_RWlock_Wrlock(AT_HANDLE hRwlock)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_rwlock_t *rw;
    int err;
    
    AT_ASSERT((pthread_rwlock_t*)hRwlock != AT_NULL);
    rw = (pthread_rwlock_t*)hRwlock;

    err = pthread_rwlock_wrlock(rw);
    if (err != 0)
    {
        AT_ERR("Wrlock rwlock fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_RWlock_TryRdlock(AT_HANDLE hRwlock)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_rwlock_t *rw;
    int err;
    
    AT_ASSERT((pthread_rwlock_t*)hRwlock != AT_NULL);
    rw = (pthread_rwlock_t*)hRwlock;

    err = pthread_rwlock_tryrdlock(rw);
    if (err != 0)
    {
        AT_ERR("Try rdlock rwlock fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_RWlock_TryWrlock(AT_HANDLE hRwlock)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_rwlock_t *rw;
    int err;
    
    AT_ASSERT((pthread_rwlock_t*)hRwlock != AT_NULL);
    rw = (pthread_rwlock_t*)hRwlock;

    err = pthread_rwlock_trywrlock(rw);
    if (err != 0)
    {
        AT_ERR("Try wrlock rwlock fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


/* 
   pthread_rwlock_timedrdlock
   pthread_rwlock_timedwrlock
*/


AT_RESULT AT_OS_RWlock_Unlock(AT_HANDLE hRwlock)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_rwlock_t *rw;
    int err;
    
    AT_ASSERT((pthread_rwlock_t*)hRwlock != AT_NULL);
    rw = (pthread_rwlock_t*)hRwlock;

    err = pthread_rwlock_unlock(rw);
    if (err != 0)
    {
        AT_ERR("Wrlock rwlock fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


