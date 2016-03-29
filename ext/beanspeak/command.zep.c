
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
#include "kernel/concat.h"
#include "kernel/operators.h"
#include "kernel/exception.h"


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
PHP_METHOD(Beanspeak_Command, getName) {

	zval *_0, *_1, *_2 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_INIT_VAR(_1);
	zephir_get_called_class(_1 TSRMLS_CC);
	zephir_fast_explode_str(_0, SL("\\"), _1, LONG_MAX TSRMLS_CC);
	ZEPHIR_MAKE_REF(_0);
	ZEPHIR_CALL_FUNCTION(&_2, "array_pop", NULL, 1, _0);
	ZEPHIR_UNREF(_0);
	zephir_check_call_status();
	zephir_fast_strtoupper(return_value, _2);
	RETURN_MM();

}

/**
 * {@inheritdoc}
 *
 * @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command, execute) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *connection, *preparedcmd = NULL, *_0 = NULL, *_1 = NULL, *_2$$3 = NULL, *_3$$3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &connection);



	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getcommandline", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(preparedcmd);
	ZEPHIR_CONCAT_VS(preparedcmd, _0, "\r\n");
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "hasdata", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(_1)) {
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "getdata", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_3$$3);
		ZEPHIR_CONCAT_VS(_3$$3, _2$$3, "\r\n");
		zephir_concat_self(&preparedcmd, _3$$3 TSRMLS_CC);
	}
	ZEPHIR_CALL_METHOD(NULL, connection, "write", NULL, 0, preparedcmd);
	zephir_check_call_status();
	object_init_ex(return_value, beanspeak_response_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 2, this_ptr, connection);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command, hasData) {

	

	RETURN_BOOL(0);

}

PHP_METHOD(Beanspeak_Command, getData) {

	

	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(beanspeak_command_exception_ce, "Command has no data", "beanspeak/command.zep", 71);
	return;

}

PHP_METHOD(Beanspeak_Command, getDataLength) {

	

	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(beanspeak_command_exception_ce, "Command has no data", "beanspeak/command.zep", 79);
	return;

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

