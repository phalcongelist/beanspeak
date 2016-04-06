
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/concat.h"
#include "kernel/string.h"


/**
 * Beanspeak\Command\Release
 *
 * Puts a "reserved" job back into the ready queue (and marks its state as "ready")
 * to be run by any client.
 *
 * <code>
 * use Beanspeak\Command\Release;
 *
 * $command = new Release(89, 10, 60 * 60);
 * $command = new Release($jobObject, 10, 60 * 60);
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_Release) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, Release, beanspeak, command_release, beanspeak_command_ce, beanspeak_command_release_method_entry, 0);

	zend_declare_property_null(beanspeak_command_release_ce, SL("id"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(beanspeak_command_release_ce, SL("priority"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(beanspeak_command_release_ce, SL("delay"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(beanspeak_command_release_ce TSRMLS_CC, 1, beanspeak_response_parser_parserinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Command\Release constructor
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Beanspeak_Command_Release, __construct) {

	zend_bool _0, _1;
	int priority, delay, ZEPHIR_LAST_CALL_STATUS;
	zval *job, *priority_param = NULL, *delay_param = NULL, *_2 = NULL, *_8, *_3$$3 = NULL, *_4$$4, *_5$$5, *_6$$5, *_7$$5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &job, &priority_param, &delay_param);

	if (!priority_param) {
		priority = 1024;
	} else {
		priority = zephir_get_intval(priority_param);
	}
	if (!delay_param) {
		delay = 0;
	} else {
		delay = zephir_get_intval(delay_param);
	}


	_0 = Z_TYPE_P(job) == IS_OBJECT;
	if (_0) {
		_0 = zephir_instance_of_ev(job, beanspeak_job_jobinterface_ce TSRMLS_CC);
	}
	_1 = Z_TYPE_P(job) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "ctype_digit", NULL, 21, job);
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
		object_init_ex(_5$$5, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(_6$$5);
		zephir_gettype(_6$$5, job TSRMLS_CC);
		ZEPHIR_INIT_VAR(_7$$5);
		ZEPHIR_CONCAT_SV(_7$$5, "The \"job\" param must be either instanceof JobInterface or integer. Got: ", _6$$5);
		ZEPHIR_CALL_METHOD(NULL, _5$$5, "__construct", NULL, 22, _7$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(_5$$5, "beanspeak/command/release.zep", 56 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_ZVAL_NREF(_8);
	ZVAL_LONG(_8, priority);
	zephir_update_property_this(this_ptr, SL("priority"), _8 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_8);
	ZVAL_LONG(_8, delay);
	zephir_update_property_this(this_ptr, SL("delay"), _8 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Release, getName) {

	

	RETURN_STRING("RELEASE", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Release, getCommandLine) {

	zval *_0, *_1, *_2;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("priority"), PH_NOISY_CC);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("delay"), PH_NOISY_CC);
	ZEPHIR_CONCAT_SVSVSV(return_value, "release ", _0, " ", _1, " ", _2);
	return;

}

/**
 * {@inheritdoc}
 * @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command_Release, parseResponse) {

	zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *_0$$3, *_1$$4, *_2$$4 = NULL, *_4$$4, *_5$$4, *_6$$5, *_7$$5 = NULL, *_8$$5, *_9$$5, *_10;
	zval *line = NULL, *data = NULL, *_11;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &line_param, &data_param);

	zephir_get_strval(line, line_param);
	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	} else {
		zephir_get_strval(data, data_param);
	}


	if (zephir_start_with_str(line, SL("RELEASED"))) {
		ZEPHIR_INIT_VAR(_0$$3);
		ZVAL_STRING(_0$$3, "RELEASED", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _0$$3);
		zephir_check_temp_parameter(_0$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_start_with_str(line, SL("BURIED"))) {
		ZEPHIR_INIT_VAR(_1$$4);
		object_init_ex(_1$$4, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_2$$4, this_ptr, "getname", &_3, 0);
		zephir_check_call_status();
		_4$$4 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_5$$4);
		ZEPHIR_CONCAT_VSV(_5$$4, _2$$4, ": out of memory trying to grow data structure by release Job ID #", _4$$4);
		ZEPHIR_CALL_METHOD(NULL, _1$$4, "__construct", NULL, 1, _5$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_1$$4, "beanspeak/command/release.zep", 90 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_start_with_str(line, SL("NOT_FOUND"))) {
		ZEPHIR_INIT_VAR(_6$$5);
		object_init_ex(_6$$5, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_7$$5, this_ptr, "getname", &_3, 0);
		zephir_check_call_status();
		_8$$5 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_9$$5);
		ZEPHIR_CONCAT_VSVS(_9$$5, _7$$5, ": Job ID #", _8$$5, " doesn't exist or is not reserved by client");
		ZEPHIR_CALL_METHOD(NULL, _6$$5, "__construct", NULL, 1, _9$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(_6$$5, "beanspeak/command/release.zep", 94 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(_10);
	object_init_ex(_10, beanspeak_command_exception_ce);
	ZEPHIR_INIT_VAR(_11);
	ZEPHIR_CONCAT_SV(_11, "Unhandled response: ", line);
	ZEPHIR_CALL_METHOD(NULL, _10, "__construct", NULL, 1, _11);
	zephir_check_call_status();
	zephir_throw_exception_debug(_10, "beanspeak/command/release.zep", 97 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

