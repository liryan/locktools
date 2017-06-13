/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_locktools.h"
#include "locktools.h"
#include "lock.h"

PHP_METHOD(LockTools,run)
{
    char *name=NULL;
    size_t name_len;
	zval*  retval_ptr=NULL;
    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache;
    int timeout=1000;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"sf*l",&name,&name_len,&fci,&fci_cache,&fci.params,&fci.param_count,&timeout)==FAILURE){
        return;
    }
    int result=-1;
    result=lock(name,timeout);
    if(result==0){
		fci.retval_ptr_ptr=&retval_ptr;
		if(SUCCESS!=zend_call_function(&fci,&fci_cache TSRMLS_CC)){
            return;
		}
        else{
            *return_value = *retval_ptr;
            zval_copy_ctor(return_value);
            zval_ptr_dtor(&retval_ptr);
        }
    }
    else{
		zend_throw_exception_ex(NULL,0 TSRMLS_CC,"can't lock it name is %s ,ERRORNO:%d",name,result);
    }
    unlock();
    return;
}

PHP_METHOD(LockTools,randno)
{
    zval * setting;
    zval * count;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"zz",&setting,&count)==FAILURE){
        printf("parse param error");
        return;
    }
    if(Z_TYPE_P(setting)==IS_ARRAY){
        printf("is array");
    }
    return;
}
