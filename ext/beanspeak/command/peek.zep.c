
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
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/exception.h"
#include "kernel/string.h"
#include "kernel/array.h"


/**
 * Beanspeak\Command\Peek
 *
 * Lets the client inspect a job in the system.
 *
 * <code>
 * use Beanspeak\Command\Peek;
 *
 * $peekJob     = new Peek(75);
 * $peekReady   = new Peek('ready');
 * $peekDelayed = new Peek('delayed');
 * $peekBuried  = new Peek('buried');
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_Peek) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, Peek, beanspeak, command_peek, beanspeak_command_ce, beanspeak_command_peek_method_entry, 0);

	zend_declare_property_null(beanspeak_command_peek_ce, SL("jobId"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_string(beanspeak_command_peek_ce, SL("commandSuffix"), "", ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(beanspeak_command_peek_ce TSRMLS_CC, 1, beanspeak_response_parser_parserinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Command\Peek constructor
 * @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command_Peek, __construct) {

	zend_bool _0, _2$$4, _3$$4;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *subject, *_1 = NULL, *_4$$5, *_5$$6, *_6$$6, *_7$$7, *_8$$7, *_9$$7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &subject);



	_0 = Z_TYPE_P(subject) == IS_LONG;
	if (!(_0)) {
		ZEPHIR_CALL_FUNCTION(&_1, "ctype_digit", NULL, 14, subject);
		zephir_check_call_status();
		_0 = zephir_is_true(_1);
	}
	if (_0) {
		zephir_update_property_this(this_ptr, SL("jobId"), subject TSRMLS_CC);
	} else if (Z_TYPE_P(subject) == IS_STRING) {
		_2$$4 = ZEPHIR_IS_STRING(subject, "ready");
		if (!(_2$$4)) {
			_2$$4 = ZEPHIR_IS_STRING(subject, "delayed");
		}
		_3$$4 = _2$$4;
		if (!(_3$$4)) {
			_3$$4 = ZEPHIR_IS_STRING(subject, "buried");
		}
		if (_3$$4) {
			ZEPHIR_INIT_VAR(_4$$5);
			ZEPHIR_CONCAT_SV(_4$$5, "-", subject);
			zephir_update_property_this(this_ptr, SL("commandSuffix"), _4$$5 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_VAR(_5$$6);
			object_init_ex(_5$$6, beanspeak_command_exception_ce);
			ZEPHIR_INIT_VAR(_6$$6);
			ZEPHIR_CONCAT_SV(_6$$6, "Invalid peek subject: ", subject);
			ZEPHIR_CALL_METHOD(NULL, _5$$6, "__construct", NULL, 1, _6$$6);
			zephir_check_call_status();
			zephir_throw_exception_debug(_5$$6, "beanspeak/command/peek.zep", 55 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_INIT_VAR(_7$$7);
		object_init_ex(_7$$7, beanspeak_command_exception_ce);
		ZEPHIR_INIT_VAR(_8$$7);
		zephir_gettype(_8$$7, subject TSRMLS_CC);
		ZEPHIR_INIT_VAR(_9$$7);
		ZEPHIR_CONCAT_SV(_9$$7, "Peek subject must be integer list or string got: ", _8$$7);
		ZEPHIR_CALL_METHOD(NULL, _7$$7, "__construct", NULL, 1, _9$$7);
		zephir_check_call_status();
		zephir_throw_exception_debug(_7$$7, "beanspeak/command/peek.zep", 58 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Peek, getName) {

	zval *commandSuffix = NULL, *_0, *_1$$3;
	zval *name;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(name);
	ZVAL_STRING(name, "PEEK", 1);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("commandSuffix"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(commandSuffix, _0);
	if (!(ZEPHIR_IS_EMPTY(commandSuffix))) {
		ZEPHIR_INIT_VAR(_1$$3);
		zephir_fast_strtoupper(_1$$3, commandSuffix);
		zephir_concat_self(&name, _1$$3 TSRMLS_CC);
	}
	RETURN_CTOR(name);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Peek, getCommandLine) {

	zval *commandSuffix = NULL, *_0;
	zval *command;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(command);
	ZVAL_STRING(command, "peek", 1);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("commandSuffix"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(commandSuffix, _0);
	if (!(ZEPHIR_IS_EMPTY(commandSuffix))) {
		ZEPHIR_CONCAT_VV(return_value, command, commandSuffix);
		RETURN_MM();
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("jobId"), PH_NOISY_CC);
	ZEPHIR_CONCAT_VSV(return_value, command, " ", _0);
	RETURN_MM();

}

/**
 * {@inheritdoc}
 * @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command_Peek, parseResponse) {

	zval *_12$$6;
	zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *_0$$3, *_1$$4, *_2$$4 = NULL, *_4$$4, *_5$$4, *_6$$5, *_7$$5 = NULL, *_8$$5, *_9$$5, *matches = NULL, *_10, _11, *_15, *_13$$6, *_14$$6;
	zval *line = NULL, *data = NULL, *_16;

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
		_0$$3 = zephir_fetch_nproperty_this(this_ptr, SL("jobId"), PH_NOISY_CC);
		if (Z_TYPE_P(_0$$3) != IS_NULL) {
			ZEPHIR_INIT_VAR(_1$$4);
			object_init_ex(_1$$4, beanspeak_command_exception_ce);
			ZEPHIR_CALL_METHOD(&_2$$4, this_ptr, "getname", &_3, 0);
			zephir_check_call_status();
			_4$$4 = zephir_fetch_nproperty_this(this_ptr, SL("jobId"), PH_NOISY_CC);
			ZEPHIR_INIT_VAR(_5$$4);
			ZEPHIR_CONCAT_VSVS(_5$$4, _2$$4, ": Job ID #", _4$$4, " does not exist");
			ZEPHIR_CALL_METHOD(NULL, _1$$4, "__construct", NULL, 1, _5$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(_1$$4, "beanspeak/command/peek.zep", 104 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		} else {
			ZEPHIR_INIT_VAR(_6$$5);
			object_init_ex(_6$$5, beanspeak_command_exception_ce);
			ZEPHIR_CALL_METHOD(&_7$$5, this_ptr, "getname", &_3, 0);
			zephir_check_call_status();
			_8$$5 = zephir_fetch_nproperty_this(this_ptr, SL("commandSuffix"), PH_NOISY_CC);
			ZEPHIR_INIT_VAR(_9$$5);
			ZEPHIR_CONCAT_VSVS(_9$$5, _7$$5, ": There are no jobs in the '", _8$$5, "' status");
			ZEPHIR_CALL_METHOD(NULL, _6$$5, "__construct", NULL, 1, _9$$5);
			zephir_check_call_status();
			zephir_throw_exception_debug(_6$$5, "beanspeak/command/peek.zep", 106 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_INIT_VAR(matches);
	ZVAL_NULL(matches);
	ZEPHIR_INIT_VAR(_10);
	ZEPHIR_SINIT_VAR(_11);
	ZVAL_STRING(&_11, "#^FOUND (\\d+) \\d+$#", 0);
	zephir_preg_match(_10, &_11, line, matches, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(_10)) {
		ZEPHIR_INIT_VAR(_12$$6);
		zephir_create_array(_12$$6, 2, 0 TSRMLS_CC);
		ZEPHIR_OBS_VAR(_13$$6);
		zephir_array_fetch_long(&_13$$6, matches, 1, PH_NOISY, "beanspeak/command/peek.zep", 114 TSRMLS_CC);
		add_assoc_long_ex(_12$$6, SS("id"), zephir_get_intval(_13$$6));
		zephir_array_update_string(&_12$$6, SL("jobdata"), &data, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(_14$$6);
		ZVAL_STRING(_14$$6, "FOUND", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _14$$6, _12$$6);
		zephir_check_temp_parameter(_14$$6);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_15);
	object_init_ex(_15, beanspeak_command_exception_ce);
	ZEPHIR_INIT_VAR(_16);
	ZEPHIR_CONCAT_SV(_16, "Unhandled response: ", line);
	ZEPHIR_CALL_METHOD(NULL, _15, "__construct", NULL, 1, _16);
	zephir_check_call_status();
	zephir_throw_exception_debug(_15, "beanspeak/command/peek.zep", 119 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

