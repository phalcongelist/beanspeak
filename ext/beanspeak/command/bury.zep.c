
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/string.h"


/**
 * Beanspeak\Command\Bury
 *
 * Puts a job into the "buried" state.
 *
 * <code>
 * use Beanspeak\Command\Bury;
 *
 * $command = new Bury(89, 10);
 * $command = new Bury($jobObject, 10);
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_Bury) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, Bury, beanspeak, command_bury, beanspeak_command_ce, beanspeak_command_bury_method_entry, 0);

	zend_declare_property_null(beanspeak_command_bury_ce, SL("id"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(beanspeak_command_bury_ce, SL("pri"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(beanspeak_command_bury_ce TSRMLS_CC, 1, beanspeak_response_parser_parserinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Command\Bury constructor
 * @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command_Bury, __construct) {

	zend_bool _0, _1;
	int pri, ZEPHIR_LAST_CALL_STATUS;
	zval *job, *pri_param = NULL, *_2 = NULL, *_8, *_3$$3 = NULL, *_4$$4, *_5$$5, *_6$$5, *_7$$5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &job, &pri_param);

	if (unlikely(Z_TYPE_P(pri_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'pri' must be a int") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	pri = Z_LVAL_P(pri_param);


	_0 = Z_TYPE_P(job) == IS_OBJECT;
	if (_0) {
		_0 = zephir_is_instance_of(job, SL("Beanspeak\\Command\\JobInterface") TSRMLS_CC);
	}
	_1 = Z_TYPE_P(job) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "ctype_digit", NULL, 19, job);
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
		ZEPHIR_CONCAT_SV(_7$$5, "The \"job\" param must be either instanceof JobInterface or integer. Got: ", _6$$5);
		ZEPHIR_CALL_METHOD(NULL, _5$$5, "__construct", NULL, 1, _7$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(_5$$5, "beanspeak/command/bury.zep", 52 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_ZVAL_NREF(_8);
	ZVAL_LONG(_8, pri);
	zephir_update_property_this(this_ptr, SL("pri"), _8 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Bury, getName) {

	

	RETURN_STRING("BURY", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Bury, getCommandLine) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("pri"), PH_NOISY_CC);
	ZEPHIR_CONCAT_SVSV(return_value, "bury ", _0, " ", _1);
	return;

}

/**
 * {@inheritdoc}
 * @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command_Bury, parseResponse) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *_0$$3, *_1$$4, *_2$$4 = NULL, *_3$$4, *_4$$4, *_5;
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


	if (zephir_start_with_str(line, SL("BURIED"))) {
		ZEPHIR_INIT_VAR(_0$$3);
		ZVAL_STRING(_0$$3, "BURIED", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _0$$3);
		zephir_check_temp_parameter(_0$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_start_with_str(line, SL("NOT_FOUND"))) {
		ZEPHIR_INIT_VAR(_1$$4);
		object_init_ex(_1$$4, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_2$$4, this_ptr, "getname", NULL, 0);
		zephir_check_call_status();
		_3$$4 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_4$$4);
		ZEPHIR_CONCAT_VSVS(_4$$4, _2$$4, ": Job ID #", _3$$4, " is not reserved or does not exist");
		ZEPHIR_CALL_METHOD(NULL, _1$$4, "__construct", NULL, 1, _4$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_1$$4, "beanspeak/command/bury.zep", 85 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(_5);
	object_init_ex(_5, beanspeak_command_exception_ce);
	ZEPHIR_INIT_VAR(_6);
	ZEPHIR_CONCAT_SV(_6, "Unhandled response: ", line);
	ZEPHIR_CALL_METHOD(NULL, _5, "__construct", NULL, 1, _6);
	zephir_check_call_status();
	zephir_throw_exception_debug(_5, "beanspeak/command/bury.zep", 88 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

