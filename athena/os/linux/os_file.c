/* Copyright (C) 2017 Athena.
   Author: Wang Thomas
   Date:   2017.07.30
   brief:  file oprate function implement
*/

/**********************************************include****************************************************/
#define ATHENA_TRACE_LOCAL_MODULE_ID AT_TRACE_MODULE_OS_FILE_ID

#include "common.h"
#include "os.h"

/**********************************************private macro************************************************/

/**********************************************private type************************************************/

/**********************************************static variable************************************************/
static AT_BOOL s_bOSFile_init = AT_FALSE;

/**********************************************function************************************************/
#ifdef ATHENA_OS_FILE_USE_ISO_C
/*
int ferror(FILE *stream);
void clearerr(FILE *stream);
int feof(FILE *stream);

void perror(const char *str);
char *strerror(int errnum);

int fileno(FILE *fp);
*/

/* type: rb wb ab rb+ wb+ ab+...
   Can use this func for creating a new file.*/
AT_RESULT Athena_OS_File_Open(AT_HANDLE *phFile, const AT_CHAR *path, const AT_CHAR *type)
{
    AT_RESULT eResult = AT_SUCCESS;
    FILE *fp = NULL;

    AT_ASSERT(phFile != AT_NULL);
    AT_ASSERT(path != AT_NULL);
    AT_ASSERT(type != AT_NULL);

    fp = fopen(path, type);

    if (fp == NULL)
    {
        AT_ERR("Open file fail!");
        AT_RETURN(AT_FAILURE);
    }

    *phFile = (AT_HANDLE)fp;
    
    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_File_Close(AT_HANDLE hFile)
{
    AT_RESULT eResult = AT_SUCCESS;
    FILE *fp = NULL;
    
    AT_ASSERT((AT_VOID *)hFile != AT_NULL);
    
    fp = (FILE *)hFile;

    if (fclose(fp) == EOF)
    {
        AT_ERR("Close file fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


AT_RESULT Athena_OS_File_Read(AT_HANDLE hFile, AT_VOID *buf, size_t size, size_t nobj, size_t *pnReadSize)
{
    AT_RESULT eResult = AT_SUCCESS;
    FILE *fp = NULL;
    
    AT_ASSERT((AT_VOID *)hFile != AT_NULL);
    AT_ASSERT(buf != AT_NULL);
    AT_ASSERT(pnReadSize != AT_NULL);
    
    fp = (FILE *)hFile;

    *pnReadSize = fread(buf, size, nobj, fp);
    
    AT_RETURN(eResult);
}


AT_RESULT Athena_OS_File_Write(AT_HANDLE hFile, const AT_VOID *buf, size_t size, size_t nobj, size_t *pnWriteSize)
{
    AT_RESULT eResult = AT_SUCCESS;
    FILE *fp = NULL;
    
    AT_ASSERT((AT_VOID *)hFile != AT_NULL);
    AT_ASSERT(buf != AT_NULL);
    AT_ASSERT(pnWriteSize != AT_NULL);
    
    fp = (FILE *)hFile;

    *pnWriteSize = fwrite(buf, size, nobj, fp);
    
    AT_RETURN(eResult);
}


AT_RESULT Athena_OS_File_Ftell(AT_HANDLE hFile, AT_INT64 *pnPos)
{
    AT_RESULT eResult = AT_SUCCESS;
    FILE *fp = NULL;
    long pos = 0;
    
    AT_ASSERT((AT_VOID *)hFile != AT_NULL);
    AT_ASSERT(pnPos != AT_NULL);
    
    fp = (FILE *)hFile;

    pos = ftell(fp);

    if (pos == -1L)
    {
        AT_ERR("ftell fail!");
        AT_RETURN(AT_FAILURE);
    }

    *pnPos = (AT_INT64)pos;
    
    AT_RETURN(eResult);
}


/* whence: SEEK_SET SEEK_CUR SEEK_END*/
AT_RESULT Athena_OS_File_Seek(AT_HANDLE hFile, AT_INT64 offset, AT_INT32 whence)
{
    AT_RESULT eResult = AT_SUCCESS;
    FILE *fp = NULL;
    
    AT_ASSERT((AT_VOID *)hFile != AT_NULL);
    
    fp = (FILE *)hFile;

    if (fseek(fp, (long)offset, (int)whence) == -1)
    {
        AT_ERR("fseek fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_File_Rewind(AT_HANDLE hFile)
{
    AT_RESULT eResult = AT_SUCCESS;
    FILE *fp = NULL;
    
    AT_ASSERT((AT_VOID *)hFile != AT_NULL);
    
    fp = (FILE *)hFile;

    rewind(fp);
    
    AT_RETURN(eResult);
}

/*
AT_RESULT Athena_OS_File_Fgetpos(AT_HANDLE hFile, AT_INT64 *pnPos)
{
    AT_RESULT eResult = AT_SUCCESS;
    FILE *fp = NULL;
    fpos_t pos;
    
    AT_ASSERT((AT_VOID *)hFile != AT_NULL);
    AT_ASSERT(pnPos != AT_NULL);
    
    fp = (FILE *)hFile;

    if (fgetpos(fp, &pos) != 0)
    {
        AT_ERR("fseek fail!");
        AT_RETURN(AT_FAILURE);
    }

    *pnPos = (AT_INT64)pos;
    
    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_File_Fsetpos(AT_HANDLE hFile, AT_INT64 offset)
{
    AT_RESULT eResult = AT_SUCCESS;
    FILE *fp = NULL;
    fpos_t pos;
    
    AT_ASSERT((AT_VOID *)hFile != AT_NULL);
    
    fp = (FILE *)hFile;
    pos = (fpos_t)offset;

    if (fsetpos(fp, &pos) != 0)
    {
        AT_ERR("fseek fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}
*/

AT_RESULT Athena_OS_File_Flush(AT_HANDLE hFile)
{
    AT_RESULT eResult = AT_SUCCESS;
    FILE *fp = AT_NULL;
    
    AT_ASSERT((AT_VOID *)hFile != AT_NULL);
    
    fp = (FILE*) hFile;

    if (fflush(fp) == EOF)
    {
        AT_ERR("fflush file fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

#else

/* After you create a new file, you can only write.
   mode : */
AT_RESULT Athena_OS_File_Create(AT_HANDLE *phFile, const AT_CHAR *path, mode_t mode)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd = 0;

    AT_ASSERT(phFile != AT_NULL);
    AT_ASSERT(path != AT_NULL);

    fd = create(path, mode);

    if (fd == -1)
    {
        AT_ERR("Create file fail!");
        AT_RETURN(AT_FAILURE);
    }

    *phFile = (AT_HANDLE)fd;
    
    AT_RETURN(eResult);
}

/* oflag: O_RDONLY O_WRONLY O_RDWR ...
   Do not use this func for creating a new file.*/
AT_RESULT Athena_OS_File_Open(AT_HANDLE *phFile, const AT_CHAR *path, AT_INT32 oflag)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd = 0;

    AT_ASSERT(phFile != AT_NULL);
    AT_ASSERT(path != AT_NULL);

    fd = open(path, oflag);

    if (fd == -1)
    {
        AT_ERR("Open file fail!");
        AT_RETURN(AT_FAILURE);
    }

    *phFile = (AT_HANDLE)fd;
    
    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_File_Close(AT_HANDLE hFile)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd = 0;
    
    fd = (int)hFile;

    if (close(fd) == -1)
    {
        AT_ERR("Close file fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

/* whence: SEEK_SET SEEK_CUR SEEK_END*/
AT_RESULT Athena_OS_File_Seek(AT_HANDLE hFile, AT_INT64 offset, AT_INT32 whence)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd = 0;
    
    fd = (int)hFile;

    if (lseek(fd, (off_t)offset, (int)whence) == -1)
    {
        AT_ERR("Seek file fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_File_Read(AT_HANDLE hFile, AT_VOID *buf, size_t nbytes)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd = 0;

    AT_ASSERT(buf != AT_NULL);
    
    fd = (int)hFile;

    if (read(fd, buf, nbytes) == -1)
    {
        AT_ERR("Read file fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_File_Write(AT_HANDLE hFile, const AT_VOID *buf, size_t nbytes)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd = 0;

    AT_ASSERT(buf != AT_NULL);
    
    fd = (int)hFile;

    if (write(fd, buf, nbytes) == -1)
    {
        AT_ERR("Write file fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


AT_RESULT Athena_OS_File_Dup(AT_HANDLE *phNewFile, AT_HANDLE hOldFile)
{
    AT_RESULT eResult = AT_SUCCESS;
    int newfd = 0;
    int oldfd = 0;

    AT_ASSERT(phNewFile != AT_NULL);
    
    oldfd = (int)hOldFile;
    newfd = dup(oldfd);

    if (newfd == -1)
    {
        AT_ERR("Dup file fail!");
        AT_RETURN(AT_FAILURE);
    }

    *phNewFile = (AT_HANDLE)newfd;
    
    AT_RETURN(eResult);
}


AT_RESULT Athena_OS_File_Dup2(AT_HANDLE hNewFile, AT_HANDLE hOldFile)
{
    AT_RESULT eResult = AT_SUCCESS;
    int newfd = 0;
    int oldfd = 0;

    newfd = (int)hNewFile;
    oldfd = (int)hOldFile;

    if (dup2(oldfd, newfd) == -1)
    {
        AT_ERR("Dup2 file fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}


AT_RESULT Athena_OS_File_Sync(AT_HANDLE hFile)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd = 0;
    
    fd = (int)hFile;

    if (fsync(fd) == -1)
    {
        AT_ERR("fsync file fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}


AT_RESULT Athena_OS_File_Truncate(AT_HANDLE hFile, AT_UINT32 length)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd = 0;
    
    fd = (int)hFile;

    if (ftruncate(fd, (off_t)length) == -1)
    {
        AT_ERR("ftruncate file fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_File_Mmap(AT_HANDLE hFile, AT_UINT32 len, AT_VOID **ppAddr)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd = 0;
    void *addr;

    AT_ASSERT(ppAddr != AT_NULL);
    
    fd = (int)hFile;

    addr = mmap(NULL, (size_t)len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (addr == MAP_FAILED)
    {
        AT_ERR("mmap file fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}


AT_RESULT Athena_OS_File_Munmap(AT_VOID *pAddr, AT_UINT32 len)
{
    AT_RESULT eResult = AT_SUCCESS;
    int err;

    AT_ASSERT(pAddr != AT_NULL);
    
    err = munmap(pAddr, (size_t)len);

    if (err == -1)
    {
        AT_ERR("munmap file fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}


AT_RESULT Athena_OS_File_Msync(AT_VOID *pAddr, AT_UINT32 len)
{
    AT_RESULT eResult = AT_SUCCESS;
    int err;
    int flags;

    AT_ASSERT(pAddr != AT_NULL);

    flags = MS_SYNC;
    
    err = msync(pAddr, (size_t)len, flags);

    if (err == -1)
    {
        AT_ERR("msync file fail!");
        AT_RETURN(AT_FAILURE);
    }

    AT_RETURN(eResult);
}


/*regular file; directory fle; block special file; character special file; FIFO; socket; symbolic link
  S_ISREG() 
  S_ISDIR() 
  S_ISCHR() 
  S_ISBLK() 
  S_ISFIFO() 
  S_ISLINK() 
  S_ISSOCK() 
  S_TYPEISMQ() 
  S_TYPEISSEM() 
  S_TYPEISSHM()*/
AT_RESULT Athena_OS_File_Stat(const AT_CHAR *pathname, struct stat *pStatBuf)
{
    AT_RESULT eResult = AT_SUCCESS;

    AT_ASSERT(pathname != AT_NULL);
    AT_ASSERT(pStatBuf != AT_NULL);

#if 0
    if (stat(pathname, pStatBuf) == -1)
    {
        AT_ERR("Stat file fail!");
        AT_RETURN(AT_FAILURE);
    }
#else
    if (lstat(pathname, pStatBuf) == -1)
    {
        AT_ERR("lstat file fail!");
        AT_RETURN(AT_FAILURE);
    }
#endif
    
    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_File_Fstat(AT_HANDLE hFile, struct stat *pStatBuf)
{
    AT_RESULT eResult = AT_SUCCESS;
    int fd = 0;

    AT_ASSERT(pStatBuf != AT_NULL);
    
    fd = (int)hFile;
    
    if (fstat(fd, pStatBuf) == -1)
    {
        AT_ERR("Fstat file fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

/*file and dir*/
AT_RESULT Athena_OS_File_Remove(const AT_CHAR *pathname)
{
    AT_RESULT eResult = AT_SUCCESS;

    AT_ASSERT(pathname != AT_NULL);

    if (remove(pathname) == -1)
    {
        AT_ERR("remove file fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

/*file and dir*/
AT_RESULT Athena_OS_File_Rename(const AT_CHAR *oldname, const AT_CHAR *newname)
{
    AT_RESULT eResult = AT_SUCCESS;

    AT_ASSERT(oldname != AT_NULL);
    AT_ASSERT(newname != AT_NULL);

    if (rename(oldname, newname) == -1)
    {
        AT_ERR("rename file fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_File_Mkdir(const AT_CHAR *pathname, mode_t mode)
{
    AT_RESULT eResult = AT_SUCCESS;

    AT_ASSERT(pathname != AT_NULL);

    if (mkdir(pathname, mode) == -1)
    {
        AT_ERR("mkdir fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_File_Rmdir(const AT_CHAR *pathname)
{
    AT_RESULT eResult = AT_SUCCESS;

    AT_ASSERT(pathname != AT_NULL);

    if (rmdir(pathname) == -1)
    {
        AT_ERR("rmdir fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_File_Opendir(const AT_CHAR *pathname, DIR **pDir)
{
    AT_RESULT eResult = AT_SUCCESS;

    AT_ASSERT(pathname != AT_NULL);
    AT_ASSERT(pDir != AT_NULL);

    *pDir = opendir(pathname);
    if (*pDir == AT_NULL)
    {
        AT_ERR("opendir fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_File_Readdir(DIR *pDir, struct dirent **pDirent)
{
    AT_RESULT eResult = AT_SUCCESS;
    
    AT_ASSERT(pDir != AT_NULL);
    AT_ASSERT(pDirent != AT_NULL);

    *pDirent = readdir(pDir);
    if (*pDirent == AT_NULL)
    {
        AT_ERR("readdir fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

AT_RESULT Athena_OS_File_Closedir(DIR *pDir)
{
    AT_RESULT eResult = AT_SUCCESS;
    
    AT_ASSERT(pDir != AT_NULL);

    if (closedir(pDir) == AT_NULL)
    {
        AT_ERR("closedir fail!");
        AT_RETURN(AT_FAILURE);
    }
    
    AT_RETURN(eResult);
}

#endif

AT_RESULT Athena_OS_File_Init(AT_VOID)
{
    AT_RESULT eResult = AT_SUCCESS;
    
    AT_ENTER();
    AT_CHECK_UNINIT(s_bOSFile_init);

    s_bOSFile_init = AT_TRUE;
    
    AT_EXIT();
    AT_RETURN(eResult);
}


