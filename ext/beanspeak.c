
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#if PHP_VERSION_ID < 50500
#include <locale.h>
#endif

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



zend_class_entry *beanspeak_command_commandinterface_ce;
zend_class_entry *beanspeak_response_parser_parserinterface_ce;
zend_class_entry *beanspeak_connection_connectionawareinterface_ce;
zend_class_entry *beanspeak_connection_connectioninterface_ce;
zend_class_entry *beanspeak_dispatcher_dispatcherawareinterface_ce;
zend_class_entry *beanspeak_dispatcher_dispatcherinterface_ce;
zend_class_entry *beanspeak_job_jobinterface_ce;
zend_class_entry *beanspeak_response_responseinterface_ce;
zend_class_entry *beanspeak_command_ce;
zend_class_entry *beanspeak_beanspeak_ce;
zend_class_entry *beanspeak_command_choose_ce;
zend_class_entry *beanspeak_command_exception_ce;
zend_class_entry *beanspeak_command_pausetube_ce;
zend_class_entry *beanspeak_command_put_ce;
zend_class_entry *beanspeak_command_reserve_ce;
zend_class_entry *beanspeak_command_stats_ce;
zend_class_entry *beanspeak_connection_ce;
zend_class_entry *beanspeak_connection_exception_ce;
zend_class_entry *beanspeak_dispatcher_ce;
zend_class_entry *beanspeak_dispatcher_exception_ce;
zend_class_entry *beanspeak_exception_ce;
zend_class_entry *beanspeak_job_ce;
zend_class_entry *beanspeak_job_exception_ce;
zend_class_entry *beanspeak_response_arrayresponse_ce;
zend_class_entry *beanspeak_response_exception_ce;
zend_class_entry *beanspeak_response_parser_exception_ce;
zend_class_entry *beanspeak_response_parser_yaml_ce;

ZEND_DECLARE_MODULE_GLOBALS(beanspeak)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(beanspeak)
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
	ZEPHIR_INIT(Beanspeak_Command_CommandInterface);
	ZEPHIR_INIT(Beanspeak_Response_Parser_ParserInterface);
	ZEPHIR_INIT(Beanspeak_Connection_ConnectionAwareInterface);
	ZEPHIR_INIT(Beanspeak_Connection_ConnectionInterface);
	ZEPHIR_INIT(Beanspeak_Dispatcher_DispatcherAwareInterface);
	ZEPHIR_INIT(Beanspeak_Dispatcher_DispatcherInterface);
	ZEPHIR_INIT(Beanspeak_Job_JobInterface);
	ZEPHIR_INIT(Beanspeak_Response_ResponseInterface);
	ZEPHIR_INIT(Beanspeak_Command);
	ZEPHIR_INIT(Beanspeak_Beanspeak);
	ZEPHIR_INIT(Beanspeak_Command_Choose);
	ZEPHIR_INIT(Beanspeak_Command_Exception);
	ZEPHIR_INIT(Beanspeak_Command_PauseTube);
	ZEPHIR_INIT(Beanspeak_Command_Put);
	ZEPHIR_INIT(Beanspeak_Command_Reserve);
	ZEPHIR_INIT(Beanspeak_Command_Stats);
	ZEPHIR_INIT(Beanspeak_Connection);
	ZEPHIR_INIT(Beanspeak_Connection_Exception);
	ZEPHIR_INIT(Beanspeak_Dispatcher);
	ZEPHIR_INIT(Beanspeak_Dispatcher_Exception);
	ZEPHIR_INIT(Beanspeak_Exception);
	ZEPHIR_INIT(Beanspeak_Job);
	ZEPHIR_INIT(Beanspeak_Job_Exception);
	ZEPHIR_INIT(Beanspeak_Response_ArrayResponse);
	ZEPHIR_INIT(Beanspeak_Response_Exception);
	ZEPHIR_INIT(Beanspeak_Response_Parser_Exception);
	ZEPHIR_INIT(Beanspeak_Response_Parser_Yaml);

#if PHP_VERSION_ID < 50500
	setlocale(LC_ALL, old_lc_all);
	free(old_lc_all);
#endif
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

static PHP_RINIT_FUNCTION(beanspeak)
{

	zend_beanspeak_globals *beanspeak_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(beanspeak_globals_ptr TSRMLS_CC);
	//zephir_init_interned_strings(TSRMLS_C);

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
