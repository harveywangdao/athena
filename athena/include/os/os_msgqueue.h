/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.22
   brief:  message queue tool interface
*/

#ifndef __OS_MSG_QUEUE_H__
#define __OS_MSG_QUEUE_H__

/**********************************************include****************************************************/
#include "athena_config.h"
#ifdef ATHENA_OS_USE_XSI_IPC
#include <sys/ipc.h>
#include <sys/msg.h>
#else
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

/**********************************************export macro************************************************/

/**********************************************export type************************************************/

/**********************************************export function************************************************/

#endif

