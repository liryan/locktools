/**
 * author liryan
 * email canbetter@163.com
 */

#include "php.h"
#include <lock.h>
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
    sem_name=name;
    if(sem_ptr==SEM_FAILED)
    {
        php_log_err("open semphore failed" TSRMLS_CC);
        return 0;
    }
    else
    {
        while(count-- >=0){
            if(-1==sem_trywait(sem_ptr)){
                if(errno==EAGAIN){ //has been locked
                    usleep(100); 
                }
                else if(errno==EDEADLK){ 
                    return 2; 
                }
                else if(errno==EINTR){
                    return 3;
                }
                else if(errno==EINVAL){
                    return 4;
                }
                else{
                    return 5;
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
    }

    if(sem_name!=NULL){
        ret=sem_unlink(sem_name);
        printf("unlink sem %d\n",ret);
        sem_name=NULL;
    }

    if(sem_ptr!=NULL){
        ret=sem_close(sem_ptr);
        printf("close sem %d\n",ret);
        sem_ptr=NULL;
    }

}
