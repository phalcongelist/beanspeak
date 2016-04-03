
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/fcall.h"
#include "kernel/array.h"


/**
 * Beanspeak\Command\Ignore
 *
 * Removes the named tube from the watch list for the current connection.
 *
 * <code>
 * use Beanspeak\Command\Ignore;
 *
 * $command = new Ignore($tube);
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_Ignore) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, Ignore, beanspeak, command_ignore, beanspeak_command_ce, beanspeak_command_ignore_method_entry, 0);

	zend_declare_property_null(beanspeak_command_ignore_ce, SL("tube"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(beanspeak_command_ignore_ce TSRMLS_CC, 1, beanspeak_response_parser_parserinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Command\Ignore constructor
 */
PHP_METHOD(Beanspeak_Command_Ignore, __construct) {

	zval *tube_param = NULL;
	zval *tube = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tube_param);

	if (unlikely(Z_TYPE_P(tube_param) != IS_STRING && Z_TYPE_P(tube_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tube' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (likely(Z_TYPE_P(tube_param) == IS_STRING)) {
		zephir_get_strval(tube, tube_param);
	} else {
		ZEPHIR_INIT_VAR(tube);
		ZVAL_EMPTY_STRING(tube);
	}


	zephir_update_property_this(this_ptr, SL("tube"), tube TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Ignore, getName) {

	

	RETURN_STRING("IGNORE", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Ignore, getCommandLine) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("tube"), PH_NOISY_CC);
	ZEPHIR_CONCAT_SV(return_value, "ignore ", _0);
	return;

}

/**
 * {@inheritdoc}
 * @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command_Ignore, parseResponse) {

	zval *_2$$3;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *ignored$$3 = NULL, *_0$$3 = NULL, *_1$$3, *_3$$4, *_4$$4 = NULL, *_5$$4, *_6;
	zval *line = NULL, *data = NULL, *_7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &line_param, &data_param);

	zephir_get_strval(line, line_param);
	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	} else {
		zephir_get_strval(data, data_param);
	}


	if (zephir_start_with_str(line, SL("WATCHING"))) {
		ZEPHIR_INIT_VAR(_0$$3);
		ZVAL_STRING(_0$$3, "#^WATCHING (\\d+)$#", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_INIT_VAR(_1$$3);
		ZVAL_STRING(_1$$3, "$1", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_FUNCTION(&ignored$$3, "preg_replace", NULL, 21, _0$$3, _1$$3, line);
		zephir_check_temp_parameter(_0$$3);
		zephir_check_temp_parameter(_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_2$$3);
		zephir_create_array(_2$$3, 1, 0 TSRMLS_CC);
		add_assoc_long_ex(_2$$3, SS("count"), zephir_get_intval(ignored$$3));
		ZEPHIR_INIT_NVAR(_0$$3);
		ZVAL_STRING(_0$$3, "WATCHING", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _0$$3, _2$$3);
		zephir_check_temp_parameter(_0$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_start_with_str(line, SL("NOT_IGNORED"))) {
		ZEPHIR_INIT_VAR(_3$$4);
		object_init_ex(_3$$4, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_4$$4, this_ptr, "getname", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_5$$4);
		ZEPHIR_CONCAT_VS(_5$$4, _4$$4, ": cannot ignore last tube in watchlist");
		ZEPHIR_CALL_METHOD(NULL, _3$$4, "__construct", NULL, 1, _5$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_3$$4, "beanspeak/command/ignore.zep", 80 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(_6);
	object_init_ex(_6, beanspeak_command_exception_ce);
	ZEPHIR_INIT_VAR(_7);
	ZEPHIR_CONCAT_SV(_7, "Unhandled response: ", line);
	ZEPHIR_CALL_METHOD(NULL, _6, "__construct", NULL, 1, _7);
	zephir_check_call_status();
	zephir_throw_exception_debug(_6, "beanspeak/command/ignore.zep", 83 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

