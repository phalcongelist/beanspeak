
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/string.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/fcall.h"


/**
 * Beanspeak\Command
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command) {

	ZEPHIR_REGISTER_CLASS(Beanspeak, Command, beanspeak, command, beanspeak_command_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_class_implements(beanspeak_command_ce TSRMLS_CC, 1, beanspeak_command_commandinterface_ce);
	return SUCCESS;

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command, getCommandName) {

	zval *_0, *_1, *_2 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_INIT_VAR(_1);
	zephir_get_called_class(_1 TSRMLS_CC);
	zephir_fast_explode_str(_0, SL("\\"), _1, LONG_MAX TSRMLS_CC);
	ZEPHIR_MAKE_REF(_0);
	ZEPHIR_CALL_FUNCTION(&_2, "array_pop", NULL, 2, _0);
	ZEPHIR_UNREF(_0);
	zephir_check_call_status();
	zephir_fast_strtoupper(return_value, _2);
	RETURN_MM();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command, __toString) {

	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getcommandline", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

