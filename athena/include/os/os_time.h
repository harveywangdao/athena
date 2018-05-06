/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.09
   brief:  time function interface
*/

#ifndef __OS_TIME_H__
#define __OS_TIME_H__
/**********************************************include****************************************************/
#include <time.h>
#include <sys/time.h>

/**********************************************export macro************************************************/

/**********************************************export type************************************************/

/**********************************************export function************************************************/
AT_RESULT Athena_OS_GetCurrentTime(AT_INT64 *pnSec);
AT_INT64 Athena_OS_GetTickCount(AT_VOID);
AT_RESULT Athena_OS_Time_Init(AT_VOID);

#endif


