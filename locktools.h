#ifndef __LOCKTOOLS_H__
#define __LOCKTOOLS_H__
#include <zend_exceptions.h>
#define error_log(size,...) {\
    char errorbuf[size+1];\
    bzero(errorbuf,size+1); \
    snprintf(errorbuf,size,__VA_ARGS__);\
    php_log_err(errorbuf TSRMLS_CC);\
}

#endif
