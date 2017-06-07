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
#include "lock.h"

/* If you declare any globals in php_locktools.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(locktools)
*/

/* True global resources - no need for thread safety here */
static int le_locktools;

const zend_function_entry locktools_methods[] = {
    PHP_ME(LockTools,run,arginfo_run,ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END	/* Must be the last line in locktools_functions[] */
};

/* }}} */

PHP_METHOD(LockTools,run)
{
    char *name=NULL;
    size_t name_len;
    zval *retval_ptr=NULL;
    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache;
    int timeout=1000;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"sf*l",&name,&name_len,&fci,&fci_cache,&fci.params,&fci.param_count,&timeout)==FAILURE){
        return;
    }
    if(1==lock(name,timeout)){
        fci.retval_ptr_ptr=&retval_ptr;
        zend_call_function(&fci,&fci_cache TSRMLS_CC);
        unlock();
    }
    else{
        php_log_err("unlock" TSRMLS_CC);   
    }
}

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("locktools.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_locktools_globals, locktools_globals)
    STD_PHP_INI_ENTRY("locktools.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_locktools_globals, locktools_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_locktools_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_locktools_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "locktools", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_locktools_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_locktools_init_globals(zend_locktools_globals *locktools_globals)
{
	locktools_globals->global_value = 0;
	locktools_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(locktools)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce,"LockTools",locktools_methods);
    lock_tools_ce=zend_register_internal_class(&ce);
    zend_declare_property_null(lock_tools_ce,"version",sizeof("version")-1,ZEND_ACC_PUBLIC);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(locktools)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
    unlock();
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(locktools)
{
    unlock();
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(locktools)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(locktools)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "locktools support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ locktools_functions[]
 *
 * Every user visible function must have an entry in locktools_functions[].
 */

/* {{{ locktools_module_entry
 */
zend_module_entry locktools_module_entry = {
	STANDARD_MODULE_HEADER,
	"locktools",
    NULL,
	PHP_MINIT(locktools),
	PHP_MSHUTDOWN(locktools),
	PHP_RINIT(locktools),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(locktools),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(locktools),
	PHP_LOCKTOOLS_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_LOCKTOOLS
ZEND_GET_MODULE(locktools)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
