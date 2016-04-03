
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
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/operators.h"


/**
 * Beanspeak\Command\Kick
 *
 * Moves jobs into the ready queue.
 * The Kick command applies only to the currently used tube.
 *
 * <code>
 * use Beanspeak\Command\Kick;
 *
 * $command = new Kick($bound);
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_Kick) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, Kick, beanspeak, command_kick, beanspeak_command_ce, beanspeak_command_kick_method_entry, 0);

	zend_declare_property_null(beanspeak_command_kick_ce, SL("bound"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(beanspeak_command_kick_ce TSRMLS_CC, 1, beanspeak_response_parser_parserinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Command\Kick constructor
 */
PHP_METHOD(Beanspeak_Command_Kick, __construct) {

	zval *bound_param = NULL, *_0;
	int bound;

	zephir_fetch_params(0, 1, 0, &bound_param);

	if (unlikely(Z_TYPE_P(bound_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'bound' must be a int") TSRMLS_CC);
		RETURN_NULL();
	}
	bound = Z_LVAL_P(bound_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, bound);
	zephir_update_property_this(this_ptr, SL("bound"), _0 TSRMLS_CC);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Kick, getName) {

	

	RETURN_STRING("KICK", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Kick, getCommandLine) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("bound"), PH_NOISY_CC);
	ZEPHIR_CONCAT_SV(return_value, "kick ", _0);
	return;

}

/**
 * {@inheritdoc}
 * @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command_Kick, parseResponse) {

	zval *_2$$3;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *kicked$$3 = NULL, *_0$$3 = NULL, *_1$$3, *_3;
	zval *line = NULL, *data = NULL, *_4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &line_param, &data_param);

	zephir_get_strval(line, line_param);
	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	} else {
		zephir_get_strval(data, data_param);
	}


	if (zephir_start_with_str(line, SL("KICKED"))) {
		ZEPHIR_INIT_VAR(_0$$3);
		ZVAL_STRING(_0$$3, "#^KICKED (.+)$#", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_INIT_VAR(_1$$3);
		ZVAL_STRING(_1$$3, "$1", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_FUNCTION(&kicked$$3, "preg_replace", NULL, 22, _0$$3, _1$$3, line);
		zephir_check_temp_parameter(_0$$3);
		zephir_check_temp_parameter(_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_2$$3);
		zephir_create_array(_2$$3, 1, 0 TSRMLS_CC);
		add_assoc_long_ex(_2$$3, SS("kicked"), zephir_get_intval(kicked$$3));
		ZEPHIR_INIT_NVAR(_0$$3);
		ZVAL_STRING(_0$$3, "KICKED", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _0$$3, _2$$3);
		zephir_check_temp_parameter(_0$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_3);
	object_init_ex(_3, beanspeak_command_exception_ce);
	ZEPHIR_INIT_VAR(_4);
	ZEPHIR_CONCAT_SV(_4, "Unhandled response: ", line);
	ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, 1, _4);
	zephir_check_call_status();
	zephir_throw_exception_debug(_3, "beanspeak/command/kick.zep", 80 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

