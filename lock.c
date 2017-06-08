/**
 * author liryan
 * email canbetter@163.com
 */

#include<lock.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
sem_t* sem_ptr=NULL;
char* sem_name=NULL;
int islocking=0;

int lock(const char* name,int second_wait)
{
    islocking=0;
    int count=second_wait*10;
    umask(S_IWGRP | S_IWOTH);
    sem_ptr=sem_open(name,O_CREAT,0644,1);
    if(sem_ptr==SEM_FAILED)
    {
        printf("create sem failed %s\n",(const char*)strerror(errno));
        return 0;
    }
    else
    {
        while(count-- >=0){
            if(-1==sem_trywait(sem_ptr)){
                if(errno==EAGAIN){ //has been locked
                    printf("can't lock error has locked\n");
                    usleep(100); 
                }
                else if(errno==EDEADLK){ 
                    printf("can't lock error EDEADLK\n");
                    return 2; 
                }
                else if(errno==EINTR){
                    printf("can't lock error EINTR\n");
                    return 3;
                }
                else if(errno==EINVAL){
                    printf("can't lock error EINVAL\n");
                    return 4;
                }
                else{
                    printf("can't lock error UNKOWN\n");
                }
            }
            else{
                islocking=1;
                return 0;
            }
        }
        return 1;
    }
}

/**
 * release a lock
 */
void unlock()
{
    int ret=-1;
    if(sem_ptr!=NULL){
        if(islocking==1){
            ret=sem_post(sem_ptr);
            printf("post sem %d\n",ret);
        }
        ret=sem_close(sem_ptr);
        printf("close sem %d\n",ret);
        sem_ptr=NULL;
    }

    if(sem_name!=NULL){
        ret=sem_unlink(sem_name);
        printf("unlink sem %d\n",ret);
        sem_name=NULL;
    }
}
