
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_BEANSTALK_H
#define PHP_BEANSTALK_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_BEANSTALK_NAME        "beanstalk"
#define PHP_BEANSTALK_VERSION     "0.0.1"
#define PHP_BEANSTALK_EXTNAME     "beanstalk"
#define PHP_BEANSTALK_AUTHOR      "Serghei Iakovlev"
#define PHP_BEANSTALK_ZEPVERSION  "0.9.2a-dev"
#define PHP_BEANSTALK_DESCRIPTION "PHP extension for beanstalkd queue"



ZEND_BEGIN_MODULE_GLOBALS(beanstalk)

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

	/* Global constants */
	zval *global_true;
	zval *global_false;
	zval *global_null;
	
ZEND_END_MODULE_GLOBALS(beanstalk)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(beanstalk)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) TSRMG(beanstalk_globals_id, zend_beanstalk_globals *, v)
#else
	#define ZEPHIR_GLOBAL(v) (beanstalk_globals.v)
#endif

#ifdef ZTS
	#define ZEPHIR_VGLOBAL ((zend_beanstalk_globals *) (*((void ***) tsrm_ls))[TSRM_UNSHUFFLE_RSRC_ID(beanstalk_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(beanstalk_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def beanstalk_globals
#define zend_zephir_globals_def zend_beanstalk_globals

extern zend_module_entry beanstalk_module_entry;
#define phpext_beanstalk_ptr &beanstalk_module_entry

#endif
