
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
#include "kernel/exception.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/fcall.h"
#include "kernel/array.h"


/**
 * Beanspeak\Command\PauseTube
 *
 * Can delay any new job being reserved for a given time.
 *
 * <code>
 * use Beanspeak\Command\PauseTube;
 *
 * $pause = new PauseTube('process-video', 60 * 60);
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_PauseTube) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, PauseTube, beanspeak, command_pausetube, beanspeak_command_ce, beanspeak_command_pausetube_method_entry, 0);

	zend_declare_property_null(beanspeak_command_pausetube_ce, SL("tube"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(beanspeak_command_pausetube_ce, SL("delay"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(beanspeak_command_pausetube_ce TSRMLS_CC, 1, beanspeak_response_parser_parserinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Command\PauseTube constructor
 * @link https://github.com/kr/beanstalkd/pull/216
 * @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command_PauseTube, __construct) {

	int delay;
	zval *tube_param = NULL, *delay_param = NULL, *_0;
	zval *tube = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &tube_param, &delay_param);

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
	if (unlikely(Z_TYPE_P(delay_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'delay' must be a int") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	delay = Z_LVAL_P(delay_param);


	if (delay > 4294967296) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_command_exception_ce, "The \"delay\" param must less than 4294967296", "beanspeak/command/pausetube.zep", 48);
		return;
	}
	zephir_update_property_this(this_ptr, SL("tube"), tube TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, delay);
	zephir_update_property_this(this_ptr, SL("delay"), _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_PauseTube, getName) {

	

	RETURN_STRING("PAUSE-TUBE", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_PauseTube, getCommandLine) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("tube"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("delay"), PH_NOISY_CC);
	ZEPHIR_CONCAT_SVSV(return_value, "pause-tube ", _0, " ", _1);
	return;

}

/**
 * {@inheritdoc}
 * @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command_PauseTube, parseResponse) {

	zval *_0$$3;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *_1$$3, *_2$$3, *_3$$4, *_4$$4 = NULL, *_5$$4, *_6$$4, *_7;
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


	if (zephir_start_with_str(line, SL("PAUSED"))) {
		ZEPHIR_INIT_VAR(_0$$3);
		zephir_create_array(_0$$3, 1, 0 TSRMLS_CC);
		ZEPHIR_OBS_VAR(_1$$3);
		zephir_read_property_this(&_1$$3, this_ptr, SL("delay"), PH_NOISY_CC);
		zephir_array_update_string(&_0$$3, SL("delay"), &_1$$3, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(_2$$3);
		ZVAL_STRING(_2$$3, "PAUSED", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _2$$3, _0$$3);
		zephir_check_temp_parameter(_2$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_start_with_str(line, SL("NOT_FOUND"))) {
		ZEPHIR_INIT_VAR(_3$$4);
		object_init_ex(_3$$4, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_4$$4, this_ptr, "getname", NULL, 0);
		zephir_check_call_status();
		_5$$4 = zephir_fetch_nproperty_this(this_ptr, SL("tube"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_6$$4);
		ZEPHIR_CONCAT_VSVS(_6$$4, _4$$4, ": tube ", _5$$4, " doesn't exist");
		ZEPHIR_CALL_METHOD(NULL, _3$$4, "__construct", NULL, 1, _6$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_3$$4, "beanspeak/command/pausetube.zep", 84 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(_7);
	object_init_ex(_7, beanspeak_command_exception_ce);
	ZEPHIR_INIT_VAR(_8);
	ZEPHIR_CONCAT_SV(_8, "Unhandled response: ", line);
	ZEPHIR_CALL_METHOD(NULL, _7, "__construct", NULL, 1, _8);
	zephir_check_call_status();
	zephir_throw_exception_debug(_7, "beanspeak/command/pausetube.zep", 87 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

