/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.07.30
   brief:  debug tool

   remaining: 1.need support multi thread.
*/

/**********************************************include****************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#define ATHENA_USE_ISO_ERROR_PRINT
#ifdef ATHENA_USE_ISO_ERROR_PRINT
#include <errno.h>
#endif
#include "common.h"
#include "os.h"

/**********************************************private macro************************************************/

/**********************************************private type************************************************/

/**********************************************static variable************************************************/
static AT_BOOL s_OSTraceModuleIDEnable[AT_TRACE_MODULE_ID_END];

/**********************************************function prototype************************************************/

/**********************************************function************************************************/
#ifdef ATHENA_USE_ISO_ERROR_PRINT
#define MAXLINE 4096
/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag".
 */
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
   char buf[MAXLINE];
   vsnprintf(buf, MAXLINE, fmt, ap);
   if (errnoflag)
       snprintf(buf+strlen(buf), MAXLINE-strlen(buf), ": %s",
         strerror(error));
   strcat(buf, "\n");
   fflush(stdout); /* in case stdout and stderr are the same */
   fputs(buf, stderr);
   fflush(NULL); /* flushes all stdio output streams */
}

/*
 * Nonfatal error related to a system call.
 * Print a message and return.
 */
void err_ret(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
}


/*
 * Fatal error related to a system call.
 * Print a message and terminate.
 */
void err_sys(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}

/*
 * Nonfatal error unrelated to a system call.
 * Error code passed as explict parameter.
 * Print a message and return.
 */
void err_cont(int error, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
}


/*
 * Fatal error unrelated to a system call.
 * Error code passed as explict parameter.
 * Print a message and terminate.
 */
void err_exit(int error, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
    exit(1);
}


/*
 * Fatal error related to a system call.
 * Print a message, dump core, and terminate.
 */
void err_dump(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    abort(); /* dump core and terminate */
    exit(1); /* shouldn't get here */
}


/*
 * Nonfatal error unrelated to a system call.
 * Print a message and return.
 */
void err_msg(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
}


/*
 * Fatal error unrelated to a system call.
 * Print a message and terminate.
 */
void err_quit(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    exit(1);
}

#endif

AT_INT32 athena_print(const char *format, ...)
{
    va_list arg;
    AT_INT32 done;
    
    va_start (arg, format);
    done = (AT_INT32)vprintf (format, arg);
    va_end (arg);
    
    return done;
}

AT_BOOL athena_check_debug(AT_TRACE_MODULE_ID eModuleID)
{
    if (eModuleID >= AT_TRACE_MODULE_ID_END)
    {
        return AT_FALSE;
    }

    if (s_OSTraceModuleIDEnable[eModuleID] == AT_TRUE)
    {
        return AT_TRUE;
    }
    
    return AT_FALSE;
}


AT_VOID athena_assert(AT_INT32 expr)
{
    if (!expr)
    {
        abort();
    }
}

AT_CHAR* athena_get_result_info(AT_RESULT eResult)
{
    switch (eResult)
    {
        case AT_SUCCESS:
        {
            return "Success!";
        }
        break;

        case AT_FAILURE:
        {
            return "Failure!";
        }
        break;

        case AT_NO_MEMORY:
        {
            return "No memory!";
        }
        break;

        case AT_ALREADY_INITIALIZED:
        {
            return "Already initialized!";
        }
        break;

        case AT_NOT_INITIALIZED:
        {
            return "Not initialized yet!";
        }
        break;

        default:
        {
            return "Unknown result!";
        }
        break;
    }
}

AT_RESULT AT_OS_TRACE_SetDebugModuleID(AT_TRACE_MODULE_ID eModuleID)
{
    AT_RESULT eResult = AT_SUCCESS;
    
    if (eModuleID >= AT_TRACE_MODULE_ID_END)
    {
        AT_RETURN(AT_FAILURE);
    }

    s_OSTraceModuleIDEnable[eModuleID] = AT_TRUE;
    
    AT_RETURN(eResult);
}

AT_RESULT AT_OS_TRACE_SetDebugMutilModuleID(AT_TRACE_MODULE_ID eFromModuleID, AT_TRACE_MODULE_ID eToModuleID)
{
    AT_RESULT eResult = AT_SUCCESS;
    AT_INT32 nIndex = 0;
    
    if (eFromModuleID >= AT_TRACE_MODULE_ID_END || eToModuleID >= AT_TRACE_MODULE_ID_END || eFromModuleID > eToModuleID)
    {
        AT_RETURN(AT_FAILURE);
    }

    for (nIndex = eFromModuleID; nIndex <= eToModuleID; nIndex++)
    {
        s_OSTraceModuleIDEnable[nIndex] = AT_TRUE;
    }
    
    AT_RETURN(eResult);
}


AT_RESULT AT_OS_TRACE_Init(AT_VOID)
{
    AT_RESULT eResult = AT_SUCCESS;

    memset(s_OSTraceModuleIDEnable, 0, sizeof(s_OSTraceModuleIDEnable));

    AT_RETURN(eResult);
}

