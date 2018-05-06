/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.07.30
   brief:  debug tool interface
*/

#ifndef __OS_TRACE_H__
#define __OS_TRACE_H__
/**********************************************include****************************************************/
#include "athena_config.h"

/**********************************************export macro************************************************/
#if (AT_DEBUG_STATUE == 1)

#if !defined(ATHENA_TRACE_LOCAL_MODULE_ID)
#define ATHENA_TRACE_LOCAL_MODULE_ID AT_TRACE_MODULE_ID_END
#endif

/*Any time, any where*/
#define AT_PRINT(...) athena_print(__VA_ARGS__)

/*Print when function occurs error*/
#define AT_ERR(...) \
    do\
    {\
        athena_print("[ERROR] %s() %d : ", __FUNCTION__, __LINE__);\
        athena_print(__VA_ARGS__);\
        athena_print("\n");\
    }while(0)

/*For debugging for whole module*/
#define AT_DEBUG(...)\
    do\
    {\
        if (athena_check_debug(ATHENA_TRACE_LOCAL_MODULE_ID))\
        {\
            athena_print("[DEBUG] %s() %d : ", __FUNCTION__, __LINE__);\
            athena_print(__VA_ARGS__);\
            athena_print("\n");\
        }\
    }while(0)

/*For enter function*/
#define AT_ENTER()\
    do\
    {\
        if (athena_check_debug(ATHENA_TRACE_LOCAL_MODULE_ID))\
        {\
            athena_print("[ENTER] %s() %d\n", __FUNCTION__, __LINE__);\
        }\
    }while(0)

/*For exit from function*/
#define AT_EXIT()\
    do\
    {\
        if (athena_check_debug(ATHENA_TRACE_LOCAL_MODULE_ID))\
        {\
            athena_print("[EXIT] %s() %d\n", __FUNCTION__, __LINE__);\
        }\
    }while(0)

/*For return*/
#define AT_RETURN(eResult)\
    do\
    {\
        AT_RESULT tmpResult = (eResult);\
        if (tmpResult != AT_SUCCESS)\
        {\
            AT_ERR("%s", athena_get_result_info(tmpResult));\
        }\
        return tmpResult;\
    }while(0)

/*For assert*/
#define AT_ASSERT(expr)\
    do\
    {\
        if (!(expr))\
        {\
            AT_ERR("ASSERT!");\
            athena_assert(expr);\
        }\
    }while(0)

#define AT_CHECK_UNINIT(bInited)\
    do\
    {\
        if (bInited)\
        {\
            AT_RETURN(AT_ALREADY_INITIALIZED);\
        }\
    }while(0)
    
#define AT_CHECK_INIT(bInited)\
    do\
    {\
        if (!(bInited))\
        {\
            AT_RETURN(AT_NOT_INITIALIZED);\
        }\
    }while(0)

#else
#define AT_PRINT() ((void)0)
#define AT_ERR() ((void)0)
#define AT_DEBUG() ((void)0)

#define AT_ENTER() ((void)0)
#define AT_EXIT() ((void)0)

#define AT_RETURN(eResult) (return (eResult);)

#define AT_ASSERT(expr) ((void)0)

#define AT_CHECK_UNINIT(bInited) ((void)0)
#define AT_CHECK_INIT(bInited) ((void)0)

#endif

/**********************************************export type************************************************/
typedef enum
{
    AT_SUCCESS,
    AT_FAILURE,
    AT_NO_MEMORY,
    AT_ALREADY_INITIALIZED,
    AT_NOT_INITIALIZED,
    AT_RESULT_END
}AT_RESULT;

typedef enum
{
    AT_TRACE_MODULE_OS_TRACE_ID,
    AT_TRACE_MODULE_OS_FILE_ID,
    AT_TRACE_MODULE_OS_TIME_ID,
    
    AT_TRACE_MODULE_UT_MAIN_ID,
    AT_TRACE_MODULE_UT_OS_TRACE_ID,
    AT_TRACE_MODULE_UT_OS_FILE_ID,
    
    AT_TRACE_MODULE_ID_END
}AT_TRACE_MODULE_ID;

/**********************************************export function************************************************/
AT_INT32 athena_print(const char *format, ...);
AT_VOID athena_assert(AT_INT32 expr);
AT_CHAR* athena_get_result_info(AT_RESULT eResult);
AT_BOOL athena_check_debug(AT_TRACE_MODULE_ID eModuleID);



AT_RESULT AT_OS_TRACE_SetDebugModuleID(AT_TRACE_MODULE_ID eModuleID);
AT_RESULT AT_OS_TRACE_SetDebugMutilModuleID(AT_TRACE_MODULE_ID eFromModuleID, AT_TRACE_MODULE_ID eToModuleID);
AT_RESULT AT_OS_TRACE_Init(AT_VOID);

#endif


