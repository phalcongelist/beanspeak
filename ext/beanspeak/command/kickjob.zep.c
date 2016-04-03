
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
#include "kernel/string.h"


/**
 * Beanspeak\Command\KickJob
 *
 * A variant of kick that operates with a single job identified by its Job ID.
 * If the given job id exists and is in a buried or delayed state, it will be
 * moved to the ready queue of the the same tube where it currently belongs.
 *
 * <code>
 * use Beanspeak\Command\KickJob;
 *
 * $command = new KickJob(43);
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_KickJob) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, KickJob, beanspeak, command_kickjob, beanspeak_command_ce, beanspeak_command_kickjob_method_entry, 0);

	zend_declare_property_null(beanspeak_command_kickjob_ce, SL("id"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(beanspeak_command_kickjob_ce TSRMLS_CC, 1, beanspeak_response_parser_parserinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Command\KickJob constructor
 * @throws \Beanspeak\Command\Exception;
 */
PHP_METHOD(Beanspeak_Command_KickJob, __construct) {

	zend_bool _0, _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *job, *_2 = NULL, *_3$$3 = NULL, *_4$$4, *_5$$5, *_6$$5, *_7$$5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &job);



	_0 = Z_TYPE_P(job) == IS_OBJECT;
	if (_0) {
		_0 = zephir_is_instance_of(job, SL("Beanspeak\\Command\\JobInterface") TSRMLS_CC);
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
		zephir_throw_exception_debug(_5$$5, "beanspeak/command/kickjob.zep", 52 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_KickJob, getName) {

	

	RETURN_STRING("KICK-JOB", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_KickJob, getCommandLine) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
	ZEPHIR_CONCAT_SV(return_value, "kick-job ", _0);
	return;

}

/**
 * {@inheritdoc}
 * @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command_KickJob, parseResponse) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *_0$$3, *_1$$3 = NULL, *_2$$3, *_3$$3, *_4$$4, *_5;
	zval *line = NULL, *data = NULL, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &line_param, &data_param);

	zephir_get_strval(line, line_param);
	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	} else {
		zephir_get_strval(data, data_param);
	}


	if (zephir_start_with_str(line, SL("NOT_FOUND"))) {
		ZEPHIR_INIT_VAR(_0$$3);
		object_init_ex(_0$$3, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "getname", NULL, 0);
		zephir_check_call_status();
		_2$$3 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_3$$3);
		ZEPHIR_CONCAT_VSVS(_3$$3, _1$$3, ": Job ", _2$$3, " does not exist or is not in a kickable state");
		ZEPHIR_CALL_METHOD(NULL, _0$$3, "__construct", NULL, 1, _3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(_0$$3, "beanspeak/command/kickjob.zep", 79 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_start_with_str(line, SL("KICKED"))) {
		ZEPHIR_INIT_VAR(_4$$4);
		ZVAL_STRING(_4$$4, "KICKED", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _4$$4);
		zephir_check_temp_parameter(_4$$4);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_5);
	object_init_ex(_5, beanspeak_command_exception_ce);
	ZEPHIR_INIT_VAR(_6);
	ZEPHIR_CONCAT_SV(_6, "Unhandled response: ", line);
	ZEPHIR_CALL_METHOD(NULL, _5, "__construct", NULL, 1, _6);
	zephir_check_call_status();
	zephir_throw_exception_debug(_5, "beanspeak/command/kickjob.zep", 86 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

