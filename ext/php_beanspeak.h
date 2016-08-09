
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_BEANSPEAK_H
#define PHP_BEANSPEAK_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_BEANSPEAK_NAME        "beanspeak"
#define PHP_BEANSPEAK_VERSION     "1.0.0-beta1"
#define PHP_BEANSPEAK_EXTNAME     "beanspeak"
#define PHP_BEANSPEAK_AUTHOR      "Phalcon Team and contributors"
#define PHP_BEANSPEAK_ZEPVERSION  "0.9.4a-dev"
#define PHP_BEANSPEAK_DESCRIPTION "Client for Beanstalk delivered as a C-extension for PHP"



ZEND_BEGIN_MODULE_GLOBALS(beanspeak)

	int initialized;

	/* Memory */
	zephir_memory_entry *start_memory; /**< The first preallocated frame */
	zephir_memory_entry *end_memory; /**< The last preallocate frame */
	zephir_memory_entry *active_memory; /**< The current memory frame */

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/** Function cache */
	HashTable *fcache;

	zephir_fcall_cache_entry *scache[ZEPHIR_MAX_CACHE_SLOTS];

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	
ZEND_END_MODULE_GLOBALS(beanspeak)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(beanspeak)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(beanspeak, v)
#else
	#define ZEPHIR_GLOBAL(v) (beanspeak_globals.v)
#endif

#ifdef ZTS
	void ***tsrm_ls;
	#define ZEPHIR_VGLOBAL ((zend_beanspeak_globals *) (*((void ***) tsrm_get_ls_cache()))[TSRM_UNSHUFFLE_RSRC_ID(beanspeak_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(beanspeak_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def beanspeak_globals
#define zend_zephir_globals_def zend_beanspeak_globals

extern zend_module_entry beanspeak_module_entry;
#define phpext_beanspeak_ptr &beanspeak_module_entry

#endif
