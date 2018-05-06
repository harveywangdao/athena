/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.04
   brief:  unit test os trace
*/

/**********************************************include****************************************************/
#define ATHENA_TRACE_LOCAL_MODULE_ID AT_TRACE_MODULE_UT_OS_TRACE_ID

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "common.h"
#include "os.h"
#include "ut_main.h"


/**********************************************private macro************************************************/

/**********************************************private type************************************************/

/**********************************************static variable************************************************/

/**********************************************function************************************************/
static AT_RESULT ut_OS_TraceReturnSuccess(AT_VOID)
{
    AT_RETURN(AT_SUCCESS);
}

static AT_RESULT ut_OS_TraceReturnFailure(AT_VOID)
{
    AT_RETURN(AT_FAILURE);
}

void ut_os_trace_enter(void)
{
    int num = 1314;
    char cText[16] = "Test String";
    
    AT_PRINT("Enter OS Trace unit test...\n");

    AT_PRINT("This is AT_PRINT, num = %d, cText = %s\n", num, cText);

    AT_ERR("This is AT_ERR, num = %d, cText = %s", num, cText);

    AT_DEBUG("This is AT_DEBUG, num = %d, cText = %s", num, cText);

    AT_ENTER();
    
    AT_EXIT();
    
    ut_OS_TraceReturnFailure();
    ut_OS_TraceReturnSuccess();

    AT_ASSERT(3);
    AT_PRINT("ASSERT(3)\n");
    AT_ASSERT(1);
    AT_PRINT("ASSERT(1)\n");
    AT_ASSERT(0);
    AT_PRINT("ASSERT(0)\n");
    
    AT_PRINT("Exit from OS Trace unit test...\n");
    return;
}


