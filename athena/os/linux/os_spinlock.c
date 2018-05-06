/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.13
   brief:  spin lock tool
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
#ifdef ATHENA_OS_USE_SPIN_LOCK
AT_RESULT AT_OS_Spin_Create(AT_HANDLE hSpinLock,
                                      const char *sSpinLockName,
                                      AT_INT32 nPriority)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_spinlock_t spin;
    int shared = 0;
    int err;

    AT_ASSERT((pthread_spinlock_t*)hSpinLock != AT_NULL);
    AT_ASSERT(sSpinLockName != AT_NULL);

    err = pthread_spin_init(&spin, shared);
    if (err != 0)
    {
        AT_ERR("Create spin fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    memcpy((pthread_spinlock_t*)hSpinLock, &spin, sizeof(pthread_spinlock_t));
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Spin_Destroy(AT_HANDLE hSpinLock)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_spinlock_t *spin;
    int err;
    
    AT_ASSERT((pthread_spinlock_t*)hSpinLock != AT_NULL);
    spin = (pthread_spinlock_t*)hSpinLock;

    err = pthread_spin_destroy(spin);
    if (err != 0)
    {
        AT_ERR("Destroy spin fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Spin_Lock(AT_HANDLE hSpinLock)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_spinlock_t *spin;
    int err;
    
    AT_ASSERT((pthread_spinlock_t*)hSpinLock != AT_NULL);
    spin = (pthread_spinlock_t*)hSpinLock;

    err = pthread_spin_lock(spin);
    if (err != 0)
    {
        AT_ERR("Lock spin fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Spin_TryLock(AT_HANDLE hSpinLock)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_spinlock_t *spin;
    int err;
    
    AT_ASSERT((pthread_spinlock_t*)hSpinLock != AT_NULL);
    spin = (pthread_spinlock_t*)hSpinLock;

    err = pthread_spin_trylock(spin);
    if (err != 0)
    {
        AT_ERR("Try lock spin fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Spin_Unlock(AT_HANDLE hSpinLock)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_spinlock_t *spin;
    int err;
    
    AT_ASSERT((pthread_spinlock_t*)hSpinLock != AT_NULL);
    spin = (pthread_spinlock_t*)hSpinLock;

    err = pthread_spin_unlock(spin);
    if (err != 0)
    {
        AT_ERR("Unlock spin fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}
#endif

/**********************************************barrier************************************************/
AT_RESULT AT_OS_Barrier_Create(AT_HANDLE hBarrier,
                                      const char *sBarrierName,
                                      AT_INT32 nPriority,
                                      AT_INT32 nCount)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_barrier_t barr;
    pthread_barrierattr_t attr;
    int shared;
    int err;

    AT_ASSERT((pthread_barrier_t*)hBarrier != AT_NULL);
    AT_ASSERT(sBarrierName != AT_NULL);
    
    err = pthread_barrierattr_init(&attr);
    if (err != 0)
    {
        AT_ERR("pthread_barrierattr_init fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    err = pthread_barrierattr_getpshared(&attr, &shared);
    if (err != 0)
    {
        AT_ERR("pthread_barrierattr_getpshared fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_PRINT("barrier attr shared = %d.\n", shared);
    shared = PTHREAD_PROCESS_PRIVATE;/*PTHREAD_PROCESS_SHARED*/

    err = pthread_barrierattr_setpshared(&attr, shared);
    if (err != 0)
    {
        AT_ERR("pthread_barrierattr_setpshared fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    err = pthread_barrier_init(&barr, &attr, nCount);
    if (err != 0)
    {
        AT_ERR("Create barrier fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    memcpy((pthread_barrier_t*)hBarrier, &barr, sizeof(pthread_barrier_t));

    err = pthread_barrierattr_destroy(&attr);
    if (err != 0)
    {
        AT_ERR("pthread_barrierattr_destroy fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Barrier_Destroy(AT_HANDLE hBarrier)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_barrier_t *barr;
    int err;
    
    AT_ASSERT((pthread_barrier_t*)hBarrier != AT_NULL);
    barr = (pthread_barrier_t*)hBarrier;

    err = pthread_barrier_destroy(barr);
    if (err != 0)
    {
        AT_ERR("Destroy barrier fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Barrier_Wait(AT_HANDLE hBarrier)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_barrier_t *barr;
    int err;
    
    AT_ASSERT((pthread_barrier_t*)hBarrier != AT_NULL);
    barr = (pthread_barrier_t*)hBarrier;

    err = pthread_barrier_wait(barr);
    if (err != 0)
    {
        AT_ERR("Wait barrier fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

