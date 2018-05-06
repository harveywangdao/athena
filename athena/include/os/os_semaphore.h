/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.23
   brief:  semaphore tool interface
*/

#ifndef __OS_SEMAPHORE_H__
#define __OS_SEMAPHORE_H__

/**********************************************include****************************************************/
#include "athena_config.h"
#ifdef ATHENA_OS_USE_XSI_IPC
#include <sys/sem.h>
#else
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

/**********************************************export macro************************************************/

/**********************************************export type************************************************/
#ifdef ATHENA_OS_USE_XSI_IPC

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
};
#endif

/**********************************************export function************************************************/

#endif


