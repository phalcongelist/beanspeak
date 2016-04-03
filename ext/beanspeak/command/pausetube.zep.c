
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/fcall.h"
#include "kernel/array.h"


/**
 * Beanspeak\Command\PauseTube
 *
 * The pause-tube command can delay any new job being reserved for a given time.
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

	zval *_8$$5;
	zephir_fcall_cache_entry *_2 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *_0$$3, *_1$$3 = NULL, *_3$$3, *_4$$4, *_5$$4 = NULL, *_6$$4, *_7$$4, *_9$$5, *_10$$5, *_11;
	zval *line = NULL, *data = NULL, *_12;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &line_param, &data_param);

	zephir_get_strval(line, line_param);
	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	} else {
		zephir_get_strval(data, data_param);
	}


	if (zephir_start_with_str(line, SL("BAD_FORMAT"))) {
		ZEPHIR_INIT_VAR(_0$$3);
		object_init_ex(_0$$3, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "getname", &_2, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_3$$3);
		ZEPHIR_CONCAT_VS(_3$$3, _1$$3, ": Invalid tube name format");
		ZEPHIR_CALL_METHOD(NULL, _0$$3, "__construct", NULL, 1, _3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(_0$$3, "beanspeak/command/pausetube.zep", 72 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_start_with_str(line, SL("NOT_FOUND"))) {
		ZEPHIR_INIT_VAR(_4$$4);
		object_init_ex(_4$$4, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_5$$4, this_ptr, "getname", &_2, 0);
		zephir_check_call_status();
		_6$$4 = zephir_fetch_nproperty_this(this_ptr, SL("tube"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_7$$4);
		ZEPHIR_CONCAT_VSVS(_7$$4, _5$$4, ": tube ", _6$$4, " doesn't exist");
		ZEPHIR_CALL_METHOD(NULL, _4$$4, "__construct", NULL, 1, _7$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_4$$4, "beanspeak/command/pausetube.zep", 76 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_start_with_str(line, SL("PAUSED"))) {
		ZEPHIR_INIT_VAR(_8$$5);
		zephir_create_array(_8$$5, 1, 0 TSRMLS_CC);
		ZEPHIR_OBS_VAR(_9$$5);
		zephir_read_property_this(&_9$$5, this_ptr, SL("delay"), PH_NOISY_CC);
		zephir_array_update_string(&_8$$5, SL("delay"), &_9$$5, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(_10$$5);
		ZVAL_STRING(_10$$5, "PAUSED", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _10$$5, _8$$5);
		zephir_check_temp_parameter(_10$$5);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_11);
	object_init_ex(_11, beanspeak_command_exception_ce);
	ZEPHIR_INIT_VAR(_12);
	ZEPHIR_CONCAT_SV(_12, "Unhandled response: ", line);
	ZEPHIR_CALL_METHOD(NULL, _11, "__construct", NULL, 1, _12);
	zephir_check_call_status();
	zephir_throw_exception_debug(_11, "beanspeak/command/pausetube.zep", 83 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

