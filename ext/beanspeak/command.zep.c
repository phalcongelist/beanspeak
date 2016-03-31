
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
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/operators.h"


/**
 * Beanspeak\Command
 *
 * A command to be sent to the beanstalkd server, and response processing logic.
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
 */
PHP_METHOD(Beanspeak_Command, hasData) {

	

	RETURN_BOOL(0);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command, getData) {

	zval *_0, *_1 = NULL, *_2;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	object_init_ex(_0, beanspeak_command_exception_ce);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getname", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SVS(_2, "The ", _1, " command has no data");
	ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 2, _2);
	zephir_check_call_status();
	zephir_throw_exception_debug(_0, "beanspeak/command.zep", 53 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command, getDataLength) {

	zval *_0, *_1 = NULL, *_2;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	object_init_ex(_0, beanspeak_command_exception_ce);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getname", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SVS(_2, "The ", _1, " command has no data");
	ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 2, _2);
	zephir_check_call_status();
	zephir_throw_exception_debug(_0, "beanspeak/command.zep", 61 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * {@inheritdoc}
 * Concrete implementation must either:
 * a) implement ResponseParserInterface
 * b) override this getResponseParser method
 */
PHP_METHOD(Beanspeak_Command, getResponseParser) {

	

	RETURN_THISW();

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

/**
 * Creates a Response for the given data.
 */
PHP_METHOD(Beanspeak_Command, createResponse) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *data = NULL;
	zval *name_param = NULL, *data_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &data_param);

	zephir_get_strval(name, name_param);
	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		array_init(data);
	} else {
		zephir_get_arrval(data, data_param);
	}


	object_init_ex(return_value, beanspeak_response_arrayresponse_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 3, name, data);
	zephir_check_call_status();
	RETURN_MM();

}

