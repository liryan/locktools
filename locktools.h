#ifndef __LOCKTOOLS_H__
#define __LOCKTOOLS_H__
#include "TSRM.h"
#include <zend_exceptions.h>
#define error_log(size,...) {\
    char errorbuf[size+1];\
    bzero(errorbuf,size+1); \
    snprintf(errorbuf,size,__VA_ARGS__);\
    php_log_err(errorbuf TSRMLS_CC);\
}


extern zend_module_entry locktools_module_entry;


PHP_METHOD(LockTools,run);
PHP_METHOD(LockTools,randno);

ZEND_BEGIN_ARG_INFO_EX(arginfo_run,0,0,3)
    ZEND_ARG_INFO(0,name)
    ZEND_ARG_INFO(0,callback)
    ZEND_ARG_INFO(0,timeout)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_randno,1,0,3)
    ZEND_ARG_INFO(0,setting)
    ZEND_ARG_INFO(1,count)
ZEND_END_ARG_INFO()

#endif
