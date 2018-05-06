/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.08.27
   brief:  net memory tool
*/

/**********************************************include****************************************************/
#include "common.h"
#include "os.h"
#include <sys/socket.h>

/**********************************************private macro************************************************/

/**********************************************private type************************************************/

/**********************************************static variable************************************************/

/**********************************************function prototype************************************************/

/**********************************************function************************************************/
AT_RESULT AT_OS_Net_Create(AT_HANDLE *phSocket, AT_INT32 domain, AT_INT32 type)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd;

    AT_ASSERT(phSocket != AT_NULL);

    fd = socket(domain, type, 0);

    if (fd == -1)
    {
        AT_ERR("Create socket fail!");
        AT_RETURN(AT_FAILURE);
    }

    *phSocket = (AT_HANDLE)fd;

    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Net_Destory()
{
    AT_RESULT eResult = AT_SUCCESS;

    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Net_Shutdown(AT_HANDLE hSocket, AT_INT32 how)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd;
    int err;

    fd = (int)hSocket;

    err = shutdown(fd, how);

    if (err == -1)
    {
        AT_ERR("Shutdown socket fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Net_Bind(AT_HANDLE hSocket, const struct sockaddr *addr, socklen_t len)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd;
    int err;
    
    AT_ASSERT(addr != AT_NULL);

    fd = (int)hSocket;

    err = bind(fd, addr, len);

    if (err == -1)
    {
        AT_ERR("Bind socket fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Net_Connect(AT_HANDLE hSocket, const struct sockaddr *addr, socklen_t len)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd;
    int err;
    
    AT_ASSERT(addr != AT_NULL);

    fd = (int)hSocket;

    err = connect(fd, addr, len);

    if (err == -1)
    {
        AT_ERR("Bind socket fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Net_Listen(AT_HANDLE hSocket, AT_INT32 backlog)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd;
    int err;
    
    fd = (int)hSocket;

    err = listen(fd, backlog);

    if (err == -1)
    {
        AT_ERR("Listen socket fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Net_Accept(AT_HANDLE hSocket, struct sockaddr *addr, socklen_t *pLen)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd;
    int err;
    
    AT_ASSERT(addr != AT_NULL);
    AT_ASSERT(pLen != AT_NULL);
    
    fd = (int)hSocket;

    err = accept(fd, addr, pLen);

    if (err == -1)
    {
        AT_ERR("accept socket fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

AT_RESULT AT_OS_Net_Send(AT_HANDLE hSocket, const AT_VOID *buf, AT_UINT32 nbytes, AT_INT32 flags)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd;
    ssize_t size;;

    AT_ASSERT(buf != AT_NULL);
    
    fd = (int)hSocket;

    size = send(fd, buf, (size_t)nbytes, (int)flags);

    if (size == -1)
    {
        AT_ERR("Send socket fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_DEBUG("Send data size is %d.", size);

    AT_RETURN(eResult);
}


AT_RESULT AT_OS_Net_Receive(AT_HANDLE hSocket, AT_VOID *buf, AT_UINT32 nbytes, AT_INT32 flags)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd;
    ssize_t size;

    AT_ASSERT(buf != AT_NULL);
    
    fd = (int)hSocket;

    size = recv(fd, buf, (size_t)nbytes, (int)flags);

    if (size == -1)
    {
        AT_ERR("Receive socket fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_DEBUG("Receive data size is %d.", size);

    AT_RETURN(eResult);
}


