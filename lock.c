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

int lock(const char* name,int second_wait)
{
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
                usleep(100); 
            }
            else{
                return 1;
            }
        }
        return 0;
    }
}

void unlock()
{
    if(sem_ptr!=NULL){
        sem_post(sem_ptr);
        sem_close(sem_ptr);
        sem_ptr=NULL;
    }

    if(sem_name!=NULL){
        sem_unlink(sem_name);
        sem_name=NULL;
    }
}
