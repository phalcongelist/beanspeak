
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "beanspeak.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *beanspeak_client_ce;
zend_class_entry *beanspeak_exception_ce;
zend_class_entry *beanspeak_job_ce;

ZEND_DECLARE_MODULE_GLOBALS(beanspeak)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(beanspeak)
{
	REGISTER_INI_ENTRIES();
	ZEPHIR_INIT(Beanspeak_Client);
	ZEPHIR_INIT(Beanspeak_Exception);
	ZEPHIR_INIT(Beanspeak_Job);
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(beanspeak)
{
	zephir_deinitialize_memory(TSRMLS_C);
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_beanspeak_globals *beanspeak_globals TSRMLS_DC)
{
	beanspeak_globals->initialized = 0;

	/* Memory options */
	beanspeak_globals->active_memory = NULL;

	/* Virtual Symbol Tables */
	beanspeak_globals->active_symbol_table = NULL;

	/* Cache Enabled */
	beanspeak_globals->cache_enabled = 1;

	/* Recursive Lock */
	beanspeak_globals->recursive_lock = 0;

	/* Static cache */
	memset(beanspeak_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);


}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_beanspeak_globals *beanspeak_globals TSRMLS_DC)
{

}

static PHP_RINIT_FUNCTION(beanspeak)
{

	zend_beanspeak_globals *beanspeak_globals_ptr;
#ifdef ZTS
	tsrm_ls = ts_resource(0);
#endif
	beanspeak_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(beanspeak_globals_ptr TSRMLS_CC);
	zephir_initialize_memory(beanspeak_globals_ptr TSRMLS_CC);


	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(beanspeak)
{
	
	zephir_deinitialize_memory(TSRMLS_C);
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(beanspeak)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_BEANSPEAK_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_BEANSPEAK_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_BEANSPEAK_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_BEANSPEAK_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_BEANSPEAK_ZEPVERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(beanspeak)
{
	php_zephir_init_globals(beanspeak_globals TSRMLS_CC);
	php_zephir_init_module_globals(beanspeak_globals TSRMLS_CC);
}

static PHP_GSHUTDOWN_FUNCTION(beanspeak)
{

}


zend_function_entry php_beanspeak_functions[] = {
ZEND_FE_END

};

zend_module_entry beanspeak_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_BEANSPEAK_EXTNAME,
	php_beanspeak_functions,
	PHP_MINIT(beanspeak),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(beanspeak),
#else
	NULL,
#endif
	PHP_RINIT(beanspeak),
	PHP_RSHUTDOWN(beanspeak),
	PHP_MINFO(beanspeak),
	PHP_BEANSPEAK_VERSION,
	ZEND_MODULE_GLOBALS(beanspeak),
	PHP_GINIT(beanspeak),
	PHP_GSHUTDOWN(beanspeak),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_BEANSPEAK
ZEND_GET_MODULE(beanspeak)
#endif
