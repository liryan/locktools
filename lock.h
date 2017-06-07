/*
 * global function for lock
 * author:liryan
 * email:canbetter@qq.com
 */

#ifndef __LOCK_H_
#define __LOCK_H_


int lock(const char* name,int second_wait);
void unlock();
#endif
