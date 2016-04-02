
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/concat.h"


/**
 * Beanspeak\Command\StatsJob
 *
 * Gives  statistical information about the specified job if it exists.
 *
 * <code>
 * use Beanspeak\Command\StatsJob;
 *
 * $stats = new StatsJob(90);
 * $stats = new StatsJob($jobObject);
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_StatsJob) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, StatsJob, beanspeak, command_statsjob, beanspeak_command_ce, beanspeak_command_statsjob_method_entry, 0);

	zend_declare_property_null(beanspeak_command_statsjob_ce, SL("id"), ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

/**
 * Beanspeak\Command\StatsJob constructor
 * @throws \Beanspeak\Command\Exception;
 */
PHP_METHOD(Beanspeak_Command_StatsJob, __construct) {

	zend_bool _0, _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *job, *_2 = NULL, *_3$$3 = NULL, *_4$$4, *_5$$5, *_6$$5, *_7$$5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &job);



	_0 = Z_TYPE_P(job) == IS_OBJECT;
	if (_0) {
		_0 = zephir_instance_of_ev(job, beanspeak_job_jobinterface_ce TSRMLS_CC);
	}
	_1 = Z_TYPE_P(job) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "ctype_digit", NULL, 15, job);
		zephir_check_call_status();
		_1 = zephir_is_true(_2);
	}
	if (_0) {
		ZEPHIR_CALL_METHOD(&_3$$3, job, "getid", NULL, 0);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("id"), _3$$3 TSRMLS_CC);
	} else if (_1) {
		ZEPHIR_INIT_ZVAL_NREF(_4$$4);
		ZVAL_LONG(_4$$4, zephir_get_intval(job));
		zephir_update_property_this(this_ptr, SL("id"), _4$$4 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_VAR(_5$$5);
		object_init_ex(_5$$5, beanspeak_command_exception_ce);
		ZEPHIR_INIT_VAR(_6$$5);
		zephir_gettype(_6$$5, job TSRMLS_CC);
		ZEPHIR_INIT_VAR(_7$$5);
		ZEPHIR_CONCAT_SV(_7$$5, "The \"job\" param must be either instanceof JobInterface list or integer got: ", _6$$5);
		ZEPHIR_CALL_METHOD(NULL, _5$$5, "__construct", NULL, 1, _7$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(_5$$5, "beanspeak/command/statsjob.zep", 52 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_StatsJob, getName) {

	

	RETURN_STRING("STATS-JOB", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_StatsJob, getCommandLine) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
	ZEPHIR_CONCAT_SV(return_value, "stats-job ", _0);
	return;

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_StatsJob, getResponseParser) {

	zval *_0;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	object_init_ex(return_value, beanspeak_response_parser_yaml_ce);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "dict", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 14, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

