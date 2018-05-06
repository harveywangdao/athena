/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.13
   brief:  cond tool
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
AT_RESULT AT_OS_Cond_Create(AT_HANDLE hCond,
                                   const char *sCondName,
                                   AT_INT32 nPriority)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_cond_t cond;
    pthread_condattr_t attr;
    int shared;
    int err;

    AT_ASSERT((pthread_cond_t*)hCond != AT_NULL);
    AT_ASSERT(sCondName != AT_NULL);

    err = pthread_condattr_init(&attr);
    if (err != 0)
    {
        AT_ERR("pthread_condattr_init fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    err = pthread_condattr_getpshared(&attr, &shared);
    if (err != 0)
    {
        AT_ERR("pthread_condattr_getpshared fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    AT_PRINT("cond attr shared = %d.\n", shared);
    shared = PTHREAD_PROCESS_PRIVATE;/*PTHREAD_PROCESS_SHARED*/

    err = pthread_condattr_setpshared(&attr, shared);
    if (err != 0)
    {
        AT_ERR("pthread_condattr_setpshared fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    err = pthread_cond_init(&cond, &attr);
    if (err != 0)
    {
        AT_ERR("Create cond fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    memcpy((pthread_cond_t*)hCond, &cond, sizeof(pthread_cond_t));

    err = pthread_condattr_destroy(&attr);
    if (err != 0)
    {
        AT_ERR("pthread_condattr_destroy fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Cond_Destroy(AT_HANDLE hCond)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_cond_t *cond;
    int err;
    
    AT_ASSERT((pthread_cond_t*)hCond != AT_NULL);
    
    cond = (pthread_cond_t*)hCond;

    err = pthread_cond_destroy(cond);
    if (err != 0)
    {
        AT_ERR("Destroy cond fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Cond_Wait(AT_HANDLE hCond, AT_HANDLE hMutex)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_cond_t *cond;
    pthread_mutex_t *mut;
    int err;
    
    AT_ASSERT((pthread_cond_t*)hCond != AT_NULL);
    AT_ASSERT((pthread_mutex_t*)hMutex != AT_NULL);
    
    cond = (pthread_cond_t*)hCond;
    mut = (pthread_mutex_t*)hMutex;

    err = pthread_cond_wait(cond, mut);
    if (err != 0)
    {
        AT_ERR("Wait cond fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


/*pthread_cond_timedwait*/


AT_RESULT AT_OS_Cond_Singal(AT_HANDLE hCond)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_cond_t *cond;
    int err;
    
    AT_ASSERT((pthread_cond_t*)hCond != AT_NULL);
    cond = (pthread_cond_t*)hCond;

    err = pthread_cond_signal(cond);
    if (err != 0)
    {
        AT_ERR("Signal cond fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Cond_Broadcast(AT_HANDLE hCond)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_cond_t *cond;
    int err;
    
    AT_ASSERT((pthread_cond_t*)hCond != AT_NULL);
    cond = (pthread_cond_t*)hCond;

    err = pthread_cond_broadcast(cond);
    if (err != 0)
    {
        AT_ERR("Broadcast cond fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


