
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
#include "ext/spl/spl_array.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/string.h"


/**
 * Beanspeak\Response\ArrayResponse
 *
 * A response with an ArrayObject interface to key => value data.
 */
ZEPHIR_INIT_CLASS(Beanspeak_Response_ArrayResponse) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Response, ArrayResponse, beanspeak, response_arrayresponse, spl_ce_ArrayObject, beanspeak_response_arrayresponse_method_entry, 0);

	zend_declare_property_null(beanspeak_response_arrayresponse_ce, SL("name"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(beanspeak_response_arrayresponse_ce TSRMLS_CC, 1, beanspeak_response_responseinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Response\ArrayResponse constructor
 */
PHP_METHOD(Beanspeak_Response_ArrayResponse, __construct) {

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


	zephir_update_property_this(this_ptr, SL("name"), name TSRMLS_CC);
	ZEPHIR_CALL_PARENT(NULL, beanspeak_response_arrayresponse_ce, this_ptr, "__construct", NULL, 0, data);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Response_ArrayResponse, getResponseName) {

	

	RETURN_MEMBER(this_ptr, "name");

}

/**
 * Object property access to ArrayObject data.
 */
PHP_METHOD(Beanspeak_Response_ArrayResponse, __get) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *key = NULL, *_0 = NULL, *_1 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_CALL_METHOD(&key, this_ptr, "transformpropertyname", NULL, 14, name);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "offsetexists", NULL, 0, key);
	zephir_check_call_status();
	if (zephir_is_true(_1)) {
		ZEPHIR_CALL_METHOD(&_0, this_ptr, "offsetget", NULL, 0, key);
		zephir_check_call_status();
	} else {
		ZVAL_NULL(_0);
	}
	RETURN_CCTOR(_0);

}

/**
 * Object property access to ArrayObject data.
 */
PHP_METHOD(Beanspeak_Response_ArrayResponse, __isset) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *key = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_CALL_METHOD(&key, this_ptr, "transformpropertyname", NULL, 14, name);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "offsetexists", NULL, 0, key);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Tranform underscored property name to hyphenated array key.
 */
PHP_METHOD(Beanspeak_Response_ArrayResponse, transformPropertyName) {

	zval *name_param = NULL, _0, _1, *_2;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_STRING(&_0, "_", 0);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "-", 0);
	ZEPHIR_INIT_VAR(_2);
	zephir_fast_str_replace(&_2, &_0, &_1, name TSRMLS_CC);
	RETURN_CCTOR(_2);

}

