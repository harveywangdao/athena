/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.07.30
   brief:  file oprate function interface
*/

#ifndef __OS_FILE_H__
#define __OS_FILE_H__
/**********************************************include****************************************************/
#define ATHENA_OS_FILE_USE_ISO_C 1

#ifdef ATHENA_OS_FILE_USE_ISO_C
#include <stdio.h>
#else
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/mman.h>
#endif

/**********************************************export macro************************************************/

/**********************************************export type************************************************/

/**********************************************export function************************************************/
AT_RESULT Athena_OS_File_Init(AT_VOID);

#endif

