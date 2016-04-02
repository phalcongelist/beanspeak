
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
		ZEPHIR_CALL_FUNCTION(&_1, "ctype_digit", NULL, 13, timeout);
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
 */
PHP_METHOD(Beanspeak_Command_Reserve, parseResponse) {

	zval *_1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *response = NULL, *_0, *_2;
	zval *line = NULL, *data = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &line_param, &data_param);

	zephir_get_strval(line, line_param);
	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	} else {
		zephir_get_strval(data, data_param);
	}


	if (!(zephir_start_with_str(line, SL("RESERVED")))) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, line);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(response);
	zephir_fast_explode_str(response, SL(" "), line, LONG_MAX TSRMLS_CC);
	zephir_array_fetch_long(&_0, response, 0, PH_NOISY | PH_READONLY, "beanspeak/command/reserve.zep", 88 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	zephir_create_array(_1, 2, 0 TSRMLS_CC);
	ZEPHIR_OBS_VAR(_2);
	zephir_array_fetch_long(&_2, response, 1, PH_NOISY, "beanspeak/command/reserve.zep", 89 TSRMLS_CC);
	add_assoc_long_ex(_1, SS("id"), zephir_get_intval(_2));
	zephir_array_update_string(&_1, SL("jobdata"), &data, PH_COPY | PH_SEPARATE);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _0, _1);
	zephir_check_call_status();
	RETURN_MM();

}

