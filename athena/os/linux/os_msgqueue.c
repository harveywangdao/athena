/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.22
   brief:  message queue tool
*/

/**********************************************include****************************************************/
#include "common.h"
#include "os.h"
#include "os_msgqueue.h"

/**********************************************private macro************************************************/

/**********************************************private type************************************************/

/**********************************************static variable************************************************/

/**********************************************function prototype************************************************/

/**********************************************function************************************************/
#ifdef ATHENA_OS_USE_XSI_IPC
AT_RESULT AT_OS_IPC_GetKey(AT_INT32 *pKey, const AT_CHAR *path, AT_INT32 id)
{
    AT_RESULT eResult = AT_SUCCESS;
    key_t key;

    AT_ASSERT(pKey != AT_NULL);
    AT_ASSERT(path != AT_NULL);

    key = ftok(path, (int)id);

    if (key == (key_t)-1)
    {
        AT_ERR("IPC Get key fail!");
        AT_RETURN(AT_FAILURE);
    }

    *pKey = (AT_INT32)key;

    AT_RETURN(eResult);
}


AT_RESULT AT_OS_MsgQueue_Create(AT_HANDLE *phMsg, AT_INT32 key, AT_INT32 flag)
{
    AT_RESULT eResult = AT_SUCCESS;
    int msgid;

    AT_ASSERT(phMsg != AT_NULL);

    msgid = msgget((key_t)key, (int)flag);

    if (msgid == -1)
    {
        AT_ERR("Create message queue fail!");
        AT_RETURN(AT_FAILURE);
    }

    *phMsg = (AT_HANDLE)msgid;

    AT_RETURN(eResult);
}

/*cmd : IPC_STAT IPC_SET IPC_RMID*/
AT_RESULT AT_OS_MsgQueue_Ctl(AT_HANDLE hMsg, AT_INT32 cmd, struct msqid_ds *buf)
{
    AT_RESULT eResult = AT_SUCCESS;
    int msqid;
    int err;
    
    AT_ASSERT(buf != AT_NULL);

    msqid = (int)hMsg;

    err = msgctl(msqid, (int)cmd, buf);

    if (err == -1)
    {
        AT_ERR("Message queue ctl fail! cmd = %d.", cmd);
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

/*flag : IPC_NOWAIT*/
AT_RESULT AT_OS_MsgQueue_Send(AT_HANDLE hMsg, const AT_VOID *ptr, AT_UINT32 bytes, AT_INT32 flag)
{
    AT_RESULT eResult = AT_SUCCESS;
    int msqid;
    int err;
    
    AT_ASSERT(ptr != AT_NULL);

    msqid = (int)hMsg;

    err = msgsnd(msqid, ptr, (size_t)bytes, (int)flag);

    if (err == -1)
    {
        AT_ERR("Message queue send fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

/*flag : IPC_NOWAIT MSG_NOERROR*/
AT_RESULT AT_OS_MsgQueue_Receive(AT_HANDLE hMsg, AT_VOID *ptr, AT_UINT32 bytes, AT_INT32 type, AT_INT32 flag)
{
    AT_RESULT eResult = AT_SUCCESS;
    int msqid;
    ssize_t datasize;
    
    AT_ASSERT(ptr != AT_NULL);

    msqid = (int)hMsg;

    datasize = msgrcv(msqid, ptr, (size_t)bytes, (long)type, (int)flag);

    if (datasize == -1)
    {
        AT_ERR("Message queue receive fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

#else

AT_RESULT AT_OS_MsgQueue_Create(AT_HANDLE *phMsg, const AT_CHAR *name)
{
    AT_RESULT eResult = AT_SUCCESS;
    mqd_t msgqueue;
    struct mq_attr attr;
    int oflag;
    mode_t mode;

    AT_ASSERT(phMsg != AT_NULL);
    AT_ASSERT(name != AT_NULL);

    oflag = O_RDWR | O_CREAT | O_EXCL;
    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;

    attr.mq_maxmsg = 50;
    attr.mq_msgsize = 1024;

    msgqueue = mq_open(name, oflag, mode, &attr);

    if (msgqueue == -1)
    {
        AT_ERR("Create message queue fail!");
        AT_RETURN(AT_FAILURE);
    }

    *phMsg = (AT_HANDLE)msgqueue;

    AT_RETURN(eResult);
}


AT_RESULT AT_OS_MsgQueue_Close(AT_HANDLE hMsg)
{
    AT_RESULT eResult = AT_SUCCESS;
    mqd_t mq;
    int err;

    mq = (mqd_t)hMsg;

    err = mq_close(mq);

    if (err == -1)
    {
        AT_ERR("Close message queue fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

AT_RESULT AT_OS_MsgQueue_Destroy(const AT_CHAR *name)
{
    AT_RESULT eResult = AT_SUCCESS;
    int err;
    
    AT_ASSERT(name != AT_NULL);

    err = mq_unlink(name);

    if (err == -1)
    {
        AT_ERR("Destroy message queue fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}


AT_RESULT AT_OS_MsgQueue_Send(AT_HANDLE hMsg, const AT_CHAR *ptr, AT_UINT32 size)
{
    AT_RESULT eResult = AT_SUCCESS;
    mqd_t mq;
    int err;
    
    AT_ASSERT(ptr != AT_NULL);

    mq = (mqd_t)hMsg;

    err = mq_send(mq, ptr, (size_t)size, 0);

    if (err == -1)
    {
        AT_ERR("Close message queue fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}


AT_RESULT AT_OS_MsgQueue_Receive(AT_HANDLE hMsg, AT_CHAR *ptr, AT_UINT32 size)
{
    AT_RESULT eResult = AT_SUCCESS;
    mqd_t mq;
    ssize_t err;
    
    AT_ASSERT(ptr != AT_NULL);

    mq = (mqd_t)hMsg;

    err = mq_receive(mq, ptr, (size_t)size, NULL);

    if (err == -1)
    {
        AT_ERR("Close message queue fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

#endif

