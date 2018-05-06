/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.24
   brief:  share memory tool interface
*/

#ifndef __OS_SHM_H__
#define __OS_SHM_H__

/**********************************************include****************************************************/
#include "athena_config.h"
#ifdef ATHENA_OS_USE_XSI_IPC
#include <sys/shm.h>
#else
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

/**********************************************export macro************************************************/

/**********************************************export type************************************************/

/**********************************************export function************************************************/

#endif

