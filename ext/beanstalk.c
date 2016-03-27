
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#if PHP_VERSION_ID < 50500
#include <locale.h>
#endif

#include "php_ext.h"
#include "beanstalk.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *beanstalk_beanstalkinterface_ce;
zend_class_entry *beanstalk_connectioninterface_ce;
zend_class_entry *beanstalk_beanstalk_ce;
zend_class_entry *beanstalk_connection_ce;
zend_class_entry *beanstalk_connection_exception_ce;
zend_class_entry *beanstalk_exception_ce;

ZEND_DECLARE_MODULE_GLOBALS(beanstalk)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(beanstalk)
{
#if PHP_VERSION_ID < 50500
	char* old_lc_all = setlocale(LC_ALL, NULL);
	if (old_lc_all) {
		size_t len = strlen(old_lc_all);
		char *tmp  = calloc(len+1, 1);
		if (UNEXPECTED(!tmp)) {
			return FAILURE;
		}

		memcpy(tmp, old_lc_all, len);
		old_lc_all = tmp;
	}

	setlocale(LC_ALL, "C");
#endif
	REGISTER_INI_ENTRIES();
	ZEPHIR_INIT(Beanstalk_BeanstalkInterface);
	ZEPHIR_INIT(Beanstalk_ConnectionInterface);
	ZEPHIR_INIT(Beanstalk_Beanstalk);
	ZEPHIR_INIT(Beanstalk_Connection);
	ZEPHIR_INIT(Beanstalk_Connection_Exception);
	ZEPHIR_INIT(Beanstalk_Exception);

#if PHP_VERSION_ID < 50500
	setlocale(LC_ALL, old_lc_all);
	free(old_lc_all);
#endif
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(beanstalk)
{

	zephir_deinitialize_memory(TSRMLS_C);
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_beanstalk_globals *beanstalk_globals TSRMLS_DC)
{
	beanstalk_globals->initialized = 0;

	/* Memory options */
	beanstalk_globals->active_memory = NULL;

	/* Virtual Symbol Tables */
	beanstalk_globals->active_symbol_table = NULL;

	/* Cache Enabled */
	beanstalk_globals->cache_enabled = 1;

	/* Recursive Lock */
	beanstalk_globals->recursive_lock = 0;

	/* Static cache */
	memset(beanstalk_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);


}

static PHP_RINIT_FUNCTION(beanstalk)
{

	zend_beanstalk_globals *beanstalk_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(beanstalk_globals_ptr TSRMLS_CC);
	//zephir_init_interned_strings(TSRMLS_C);

	zephir_initialize_memory(beanstalk_globals_ptr TSRMLS_CC);


	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(beanstalk)
{

	

	zephir_deinitialize_memory(TSRMLS_C);
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(beanstalk)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_BEANSTALK_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_BEANSTALK_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_BEANSTALK_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_BEANSTALK_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_BEANSTALK_ZEPVERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(beanstalk)
{
	php_zephir_init_globals(beanstalk_globals TSRMLS_CC);
}

static PHP_GSHUTDOWN_FUNCTION(beanstalk)
{

}


zend_function_entry php_beanstalk_functions[] = {
ZEND_FE_END

};

zend_module_entry beanstalk_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_BEANSTALK_EXTNAME,
	php_beanstalk_functions,
	PHP_MINIT(beanstalk),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(beanstalk),
#else
	NULL,
#endif
	PHP_RINIT(beanstalk),
	PHP_RSHUTDOWN(beanstalk),
	PHP_MINFO(beanstalk),
	PHP_BEANSTALK_VERSION,
	ZEND_MODULE_GLOBALS(beanstalk),
	PHP_GINIT(beanstalk),
	PHP_GSHUTDOWN(beanstalk),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_BEANSTALK
ZEND_GET_MODULE(beanstalk)
#endif
