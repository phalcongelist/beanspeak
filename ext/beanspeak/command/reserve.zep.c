
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
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/exception.h"


/**
 * Beanspeak\Command\Reserve
 *
 * Reserves/locks a ready job from the specified tube.
 *
 * <code>
 * use Beanspeak\Command\Reserve;
 *
 * $reserve = new Reserve(60 * 60 * 2);
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_Reserve) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, Reserve, beanspeak, command_reserve, beanspeak_command_ce, beanspeak_command_reserve_method_entry, 0);

	zend_declare_property_null(beanspeak_command_reserve_ce, SL("timeout"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(beanspeak_command_reserve_ce TSRMLS_CC, 1, beanspeak_response_parser_parserinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Command\Reserve constructor
 */
PHP_METHOD(Beanspeak_Command_Reserve, __construct) {

	zend_bool _0;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *timeout = NULL, *_1 = NULL, *_2$$3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &timeout);

	if (!timeout) {
		timeout = ZEPHIR_GLOBAL(global_null);
	}


	_0 = Z_TYPE_P(timeout) == IS_LONG;
	if (!(_0)) {
		ZEPHIR_CALL_FUNCTION(&_1, "ctype_digit", NULL, 21, timeout);
		zephir_check_call_status();
		_0 = zephir_is_true(_1);
	}
	if (_0) {
		ZEPHIR_INIT_ZVAL_NREF(_2$$3);
		ZVAL_LONG(_2$$3, zephir_get_intval(timeout));
		zephir_update_property_this(this_ptr, SL("timeout"), _2$$3 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Reserve, getName) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("timeout"), PH_NOISY_CC);
	if (zephir_is_true(_0)) {
		RETURN_STRING("RESERVE-WITH-TIMEOUT", 1);
	}
	RETURN_STRING("RESERVE", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Reserve, getCommandLine) {

	zval *timeout = NULL, *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("timeout"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(timeout, _0);
	if (Z_TYPE_P(timeout) == IS_LONG) {
		ZEPHIR_CONCAT_SV(return_value, "reserve-with-timeout ", timeout);
		RETURN_MM();
	}
	RETURN_MM_STRING("reserve", 1);

}

/**
 * {@inheritdoc}
 * @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command_Reserve, parseResponse) {

	zval *_2$$3;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *matches$$3 = NULL, *_0$$3, _1$$3, *_3$$3, *_4$$3, *_5$$3, *_6$$4, *_7;
	zval *line = NULL, *data = NULL, *_8;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &line_param, &data_param);

	zephir_get_strval(line, line_param);
	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	} else {
		zephir_get_strval(data, data_param);
	}


	if (zephir_start_with_str(line, SL("RESERVED"))) {
		ZEPHIR_INIT_VAR(matches$$3);
		ZVAL_NULL(matches$$3);
		ZEPHIR_INIT_VAR(_0$$3);
		ZEPHIR_SINIT_VAR(_1$$3);
		ZVAL_STRING(&_1$$3, "#^RESERVED (\\d+) (\\d+)$#", 0);
		zephir_preg_match(_0$$3, &_1$$3, line, matches$$3, 0, 0 , 0  TSRMLS_CC);
		ZEPHIR_INIT_VAR(_2$$3);
		zephir_create_array(_2$$3, 3, 0 TSRMLS_CC);
		ZEPHIR_OBS_VAR(_3$$3);
		zephir_array_fetch_long(&_3$$3, matches$$3, 1, PH_NOISY, "beanspeak/command/reserve.zep", 88 TSRMLS_CC);
		add_assoc_long_ex(_2$$3, SS("id"), zephir_get_intval(_3$$3));
		ZEPHIR_OBS_VAR(_4$$3);
		zephir_array_fetch_long(&_4$$3, matches$$3, 2, PH_NOISY, "beanspeak/command/reserve.zep", 89 TSRMLS_CC);
		add_assoc_long_ex(_2$$3, SS("bytes"), zephir_get_intval(_4$$3));
		zephir_array_update_string(&_2$$3, SL("jobdata"), &data, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(_5$$3);
		ZVAL_STRING(_5$$3, "RESERVED", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _5$$3, _2$$3);
		zephir_check_temp_parameter(_5$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_start_with_str(line, SL("TIMED_OUT"))) {
		ZEPHIR_INIT_VAR(_6$$4);
		ZVAL_STRING(_6$$4, "TIMED_OUT", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _6$$4);
		zephir_check_temp_parameter(_6$$4);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_7);
	object_init_ex(_7, beanspeak_command_exception_ce);
	ZEPHIR_INIT_VAR(_8);
	ZEPHIR_CONCAT_SV(_8, "Unhandled response: ", line);
	ZEPHIR_CALL_METHOD(NULL, _7, "__construct", NULL, 1, _8);
	zephir_check_call_status();
	zephir_throw_exception_debug(_7, "beanspeak/command/reserve.zep", 98 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

