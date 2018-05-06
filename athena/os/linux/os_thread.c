/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.13
   brief:  thread tool
*/

/**********************************************include****************************************************/
#include "common.h"
#include "os.h"
#include <pthread.h>
#include <unistd.h>
#include <limits.h>

/**********************************************private macro************************************************/

/**********************************************private type************************************************/

/**********************************************static variable************************************************/

/**********************************************function prototype************************************************/

/**********************************************function************************************************/
AT_BOOL AT_OS_Thread_Equal(pthread_t tid1, pthread_t tid2)
{
    if (pthread_equal(tid1, tid2) != 0)
    {
        return AT_TRUE;
    }
    
    return AT_FALSE;
}

AT_RESULT AT_OS_Thread_Self(pthread_t *pTid)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_t tid;

    AT_ASSERT(pTid != AT_NULL);

    tid = pthread_self();
    
    *pTid = tid;
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Thread_Create(AT_HANDLE *phThread,
                                      const char *sThreadName,
                                      AT_INT32 nStackSize,
                                      AT_INT32 nPriority,
                                      void *(*fn)(void *),
                                      void *pArg)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_t tid;
    pthread_attr_t attr;
    int detachstate;
    size_t stacksize;
    struct sched_param sched;
    int err;

    AT_ASSERT(phThread != AT_NULL);
    AT_ASSERT(sThreadName != AT_NULL);
    AT_ASSERT(nStackSize >= PTHREAD_STACK_MIN);
    AT_ASSERT(fn != AT_NULL);
    AT_ASSERT(pArg != AT_NULL);

    err = pthread_attr_init(&attr);
    if (err != 0)
    {
        AT_ERR("pthread_attr_init fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    err = pthread_attr_getdetachstate(&attr, &detachstate);
    if (err != 0)
    {
        AT_ERR("pthread_attr_getdetachstate fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_PRINT("detach state = %d.\n", detachstate);

    detachstate = PTHREAD_CREATE_DETACHED;

    err = pthread_attr_setdetachstate(&attr, detachstate);
    if (err != 0)
    {
        AT_ERR("pthread_attr_setdetachstate fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    err = pthread_attr_getstacksize(&attr, &stacksize);
    if (err != 0)
    {
        AT_ERR("pthread_attr_getstacksize fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_PRINT("init stack size = %d.\n", stacksize);
    
    stacksize = (size_t)nStackSize;
    
    err = pthread_attr_setstacksize(&attr, stacksize);
    if (err != 0)
    {
        AT_ERR("pthread_attr_setstacksize fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    err = pthread_attr_getschedparam(&attr, &sched);
    if (err != 0)
    {
        AT_ERR("pthread_attr_getschedparam fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_PRINT("init priority = %d.\n", sched.sched_priority);
    
    sched.sched_priority = (int)nPriority;
    
    err = pthread_attr_setschedparam(&attr, &sched);
    if (err != 0)
    {
        AT_ERR("pthread_attr_setschedparam fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

/*
pthread_attr_getinheritsched
pthread_attr_setinheritsched

pthread_attr_getschedpolicy
pthread_attr_setschedpolicy

pthread_attr_getscope
pthread_attr_setscope
*/
    err = pthread_create(&tid, &attr, fn, pArg);
    if (err != 0)
    {
        AT_ERR("Create thread fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }

    *phThread = (AT_HANDLE)tid;

    err = pthread_attr_destroy(&attr);
    if (err != 0)
    {
        AT_ERR("pthread_attr_destroy fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Thread_Exit(AT_VOID *p)
{
    AT_RESULT eResult = AT_SUCCESS;

    AT_ASSERT(p != AT_NULL);

    pthread_exit(p);
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Thread_Join(AT_HANDLE hThread, AT_VOID **pp)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_t pid;
    int err;
    
    pid = (pthread_t)hThread;

    err = pthread_join(pid, pp);
    if (err != 0)
    {
        AT_ERR("Join thread fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Thread_Sleep(AT_INT32 nSleepTime)
{
    AT_RESULT eResult = AT_SUCCESS;

    sleep(nSleepTime);
    
    AT_RETURN(eResult);
}

/* void pthread_cleanup_push(void (*rtn)(void *), void *arg)
   void pthread_cleanup_pop(int execute)*/
AT_RESULT AT_OS_Thread_Cancel(AT_HANDLE hThread)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_t pid;
    int err;
    
    pid = (pthread_t)hThread;

    err = pthread_cancel(pid);
    if (err != 0)
    {
        AT_ERR("Cancel thread fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Thread_Detach(AT_HANDLE hThread)
{
    AT_RESULT eResult = AT_SUCCESS;
    pthread_t pid;
    int err;
    
    pid = (pthread_t)hThread;

    err = pthread_detach(pid);
    if (err != 0)
    {
        AT_ERR("Detach thread fail! err = %d.", err);
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


