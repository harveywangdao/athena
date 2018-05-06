/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.07.30
   brief:  test
*/

/**********************************************include****************************************************/
#define ATHENA_TRACE_LOCAL_MODULE_ID AT_TRACE_MODULE_UT_MAIN_ID

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "os.h"
#include "ut_main.h"

/**********************************************private macro************************************************/
#define UT_MAIN_INPUT_STRING_LENGTH (16)

/**********************************************private type************************************************/
typedef enum
{
    UT_ITEM_OS_FILE,
    UT_ITEM_OS_TRACE,
    UT_ITEM_EXIT,
    UT_ITEM_NUM
}UT_TestItem_e;

typedef struct UT_TextItemContext_s
{
    UT_TestItem_e eTestItem;
    char sCommand[UT_MAIN_INPUT_STRING_LENGTH];
    testFunc testFunction;
}UT_TextItemContext_t;

/**********************************************static variable************************************************/
static UT_TextItemContext_t stTestItemContext[UT_ITEM_NUM] = 
{
    {UT_ITEM_OS_FILE, "os_file", ut_os_file_enter},
    {UT_ITEM_OS_TRACE, "os_trace", ut_os_trace_enter},
    {UT_ITEM_EXIT, "exit", NULL},
};

/**********************************************function************************************************/
static AT_RESULT ut_init(AT_VOID)
{
    AT_RESULT eResult = AT_SUCCESS;
    AT_INT64 nSec = 0;

    eResult = AT_OS_TRACE_Init();
    if (eResult != AT_SUCCESS)
    {
        AT_RETURN(eResult);
    }

    AT_OS_TRACE_SetDebugModuleID(AT_TRACE_MODULE_UT_OS_TRACE_ID);
    //AT_OS_TRACE_SetDebugModuleID(AT_TRACE_MODULE_UT_MAIN_ID);

    AT_DEBUG("sizeof(AT_INT8) = %d.\n", sizeof(AT_INT8));
    AT_DEBUG("sizeof(AT_UINT8) = %d.\n", sizeof(AT_UINT8));
    AT_DEBUG("sizeof(AT_INT16) = %d.\n", sizeof(AT_INT16));
    AT_DEBUG("sizeof(AT_UINT16) = %d.\n", sizeof(AT_UINT16));
    AT_DEBUG("sizeof(AT_INT32) = %d.\n", sizeof(AT_INT32));
    AT_DEBUG("sizeof(AT_UINT32) = %d.\n", sizeof(AT_UINT32));
    AT_DEBUG("sizeof(AT_INT64) = %d.\n", sizeof(AT_INT64));
    AT_DEBUG("sizeof(AT_UINT64) = %d.\n", sizeof(AT_UINT64));
    AT_DEBUG("sizeof(AT_VOID) = %d.\n", sizeof(AT_VOID));
    AT_DEBUG("sizeof(AT_POINTER) = %d.\n", sizeof(AT_POINTER));
    AT_DEBUG("sizeof(AT_FLOAT) = %d.\n", sizeof(AT_FLOAT));
    AT_DEBUG("sizeof(AT_DOUBLE) = %d.\n", sizeof(AT_DOUBLE));

    
    AT_PRINT("OS milli second is %d.\n", Athena_OS_GetTickCount());
    
    Athena_OS_GetCurrentTime(&nSec);
    AT_PRINT("Current time is %d.\n", nSec);

    //Athena_OS_SetCurrentTime(nSec - 60);

    Athena_OS_GetCurrentTime(&nSec);
    AT_PRINT("Current time is %d.\n", nSec);
    
    AT_PRINT("OS milli second is %d.\n", Athena_OS_GetTickCount());

    AT_RETURN(eResult);
}

int main(int argc, char *argv[])
{
    char inputString[UT_MAIN_INPUT_STRING_LENGTH];
    
    ut_init();

    while (1)
    {
        UT_TestItem_e eTestItem = 0;
        int c = 0;

        AT_PRINT("please enter test command:");
        
        memset(inputString, 0, sizeof(inputString));
        if (fgets(inputString, sizeof(inputString), stdin) == NULL)
        {
            AT_ERR("fgets fail!");
            return 0;
        }

        if (inputString[strlen(inputString) - 1] == '\n')
        {
            inputString[strlen(inputString) - 1] = '\0';
        }
        else
        {
            while ((c = getchar()) != EOF && c != '\n');
        }
        
        AT_DEBUG("inputString = %s\n", inputString);

        for (eTestItem = 0; eTestItem < UT_ITEM_NUM; eTestItem++)
        {
            if (strcmp(inputString, stTestItemContext[eTestItem].sCommand) == 0)
            {
                break;
            }
        }

        if (eTestItem >= UT_ITEM_NUM)
        {
            AT_ERR("error command!");
            continue;
        }
        else if (UT_ITEM_EXIT == eTestItem)
        {
            AT_DEBUG("Exit from unit test.\n");
            return 0;
        }

        (stTestItemContext[eTestItem].testFunction)();
    }
    
    return 0;
}

