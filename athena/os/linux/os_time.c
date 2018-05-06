/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.09
   brief:  time function implement
*/

/**********************************************include****************************************************/
#define ATHENA_TRACE_LOCAL_MODULE_ID AT_TRACE_MODULE_OS_TIME_ID

#include "common.h"
#include "os.h"

/**********************************************private macro************************************************/

/**********************************************private type************************************************/

/**********************************************static variable************************************************/
static AT_BOOL s_bOSTime_init = AT_FALSE;

/**********************************************function************************************************/
/*Time from 1970.01.01 00:00:00
  return seconds
  int gettimeofday(struct timeval*tv, struct timezone *tz);
  int settimeofday(const struct timeval *tv,const struct timezone *tz);*/
AT_RESULT Athena_OS_GetCurrentTime(AT_INT64 *pnSec)
{
    AT_RESULT eResult = AT_SUCCESS;
    time_t t;
    
    AT_ASSERT(pnSec != AT_NULL);

    t = time((time_t*)NULL);

    if (t == (time_t)-1)
    {
        AT_ERR("Get time error!");
        AT_RETURN(AT_FAILURE);
    }

    *pnSec = (AT_INT64)t;
    
    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_SetCurrentTime(AT_INT64 nSec)
{
    AT_RESULT eResult = AT_SUCCESS;
    struct timespec ts;

    AT_ASSERT(nSec >= 0);
    
    ts.tv_sec = nSec;
    ts.tv_nsec = 0;

    if (clock_settime(CLOCK_REALTIME, &ts) == -1)
    {
        AT_ERR("Set time error!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


/*CLOCK_REALTIME : from 1970.01.01 00:00:00
  CLOCK_MONOTONIC : from os start
  CLOCK_PROCESS_CPUTIME_ID : from current process start
  CLOCK_THREAD_CPUTIME_ID : from current thread start*/
AT_INT64 Athena_OS_GetTickCount(AT_VOID)
{
    AT_INT64 nMilliSec;
    struct timespec ts;
    
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1)
    {
        AT_ERR("Get time error!");
        return 0;
    }

    nMilliSec = (AT_INT64)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
    
    return nMilliSec;
}


AT_RESULT Athena_OS_Time_Init(AT_VOID)
{
    AT_RESULT eResult = AT_SUCCESS;
    
    AT_ENTER();
    AT_CHECK_UNINIT(s_bOSTime_init);

    s_bOSTime_init = AT_TRUE;
    
    AT_EXIT();
    AT_RETURN(eResult);
}

