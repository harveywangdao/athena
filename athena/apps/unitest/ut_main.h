/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.02
   brief:  file oprate function interface
*/

#ifndef __UT_MAIN_H__
#define __UT_MAIN_H__
/**********************************************include****************************************************/

/**********************************************export macro************************************************/

/**********************************************export type************************************************/
typedef void (*testFunc)(void);

/**********************************************export function************************************************/
void ut_os_file_enter(void);
void ut_os_trace_enter(void);

#endif


