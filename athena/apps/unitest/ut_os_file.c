/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.02
   brief:  unit test os file
*/

/**********************************************include****************************************************/
#define ATHENA_TRACE_LOCAL_MODULE_ID AT_TRACE_MODULE_UT_OS_FILE_ID
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "common.h"
#include "os.h"
#include "ut_main.h"


/**********************************************private macro************************************************/
#define UT_MAIN_OS_FILE_COMMAND_STRING_LENGTH (32)

/**********************************************private type************************************************/
typedef AT_RESULT (*testFunc1)(AT_VOID);

typedef enum
{
    UT_ITEM_OS_FILE_INIT,
    UT_ITEM_OS_FILE_BACK,
    UT_ITEM_OS_FILE_NUM
}UT_OS_FILE_TestItem_e;

typedef struct UT_TextOSFileItemContext_s
{
    UT_OS_FILE_TestItem_e eTestItem;
    char sCommand[UT_MAIN_OS_FILE_COMMAND_STRING_LENGTH];
    testFunc1 testFunction;
}UT_TextOSFileItemContext_t;

/**********************************************static variable************************************************/

static UT_TextOSFileItemContext_t stTestOSFileItemContext[UT_ITEM_OS_FILE_NUM]=
{
    {UT_ITEM_OS_FILE_INIT, "init", Athena_OS_File_Init},
    {UT_ITEM_OS_FILE_BACK, "back", NULL},
};

/**********************************************function************************************************/

void ut_os_file_enter(void)
{    
    char sInputCommand[UT_MAIN_OS_FILE_COMMAND_STRING_LENGTH];

    AT_DEBUG("Enter OS File unit test...\n");

    while (1)
    {
        int nIndex = 0;
        int c = 0;

        AT_PRINT("please enter os file test command:");
                
        memset(sInputCommand, 0, sizeof(sInputCommand));
        if (fgets(sInputCommand, sizeof(sInputCommand), stdin) == NULL)
        {
            AT_ERR("fgets fail!");
            return;
        }

        if (sInputCommand[strlen(sInputCommand) - 1] == '\n')
        {
            sInputCommand[strlen(sInputCommand) - 1] = '\0';
        }
        else
        {
            while ((c = getchar()) != EOF && c != '\n');
        }
        
        AT_DEBUG("sInputCommand = %s\n", sInputCommand);

        for (nIndex = 0; nIndex < UT_ITEM_OS_FILE_NUM; nIndex++)
        {
            if (strcmp(sInputCommand, stTestOSFileItemContext[nIndex].sCommand) == 0)
            {
                break;
            }
        }

        if (nIndex >= UT_ITEM_OS_FILE_NUM)
        {
            AT_ERR("error command!");
            continue;
        }

        if (nIndex == UT_ITEM_OS_FILE_BACK)
        {
            return;
        }

        (stTestOSFileItemContext[nIndex].testFunction)();
    }
    
    return;
}

