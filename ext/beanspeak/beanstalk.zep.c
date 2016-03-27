
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
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/array.h"


/**
 * Beanspeak\Beanspeak
 *
 * Class to access the beanspeak queue service.
 */
ZEPHIR_INIT_CLASS(Beanspeak_Beanspeak) {

	ZEPHIR_REGISTER_CLASS(Beanspeak, Beanspeak, beanspeak, beanspeak, beanspeak_beanspeak_method_entry, 0);

	zend_declare_property_null(beanspeak_beanspeak_ce, SL("connection"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(beanspeak_beanspeak_ce TSRMLS_CC, 1, beanspeak_connection_connectionawareinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Beanspeak constructor
 */
PHP_METHOD(Beanspeak_Beanspeak, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *connection = NULL, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &connection);

	if (!connection) {
		ZEPHIR_CPY_WRT(connection, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(connection);
	}


	ZEPHIR_INIT_VAR(_0);
	if (!(zephir_is_true(connection))) {
		ZEPHIR_INIT_NVAR(_0);
		object_init_ex(_0, beanspeak_connection_ce);
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 1);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(_0, connection);
	}
	ZEPHIR_CPY_WRT(connection, _0);
	zephir_update_property_this(this_ptr, SL("connection"), connection TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Beanspeak, getConnection) {

	

	RETURN_MEMBER(this_ptr, "connection");

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Beanspeak, setConnection) {

	zval *connection;

	zephir_fetch_params(0, 1, 0, &connection);



	zephir_update_property_this(this_ptr, SL("connection"), connection TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Creates a new connection object, based on the existing connection object
 */
PHP_METHOD(Beanspeak_Beanspeak, reconnect) {

	zval *_0;
	zval *newc = NULL, *oldc = NULL, *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(oldc);
	zephir_read_property_this(&oldc, this_ptr, SL("connection"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(newc);
	object_init_ex(newc, beanspeak_connection_ce);
	ZEPHIR_INIT_VAR(_0);
	zephir_create_array(_0, 4, 0 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_1, oldc, "gethost", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL("host"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_1, oldc, "getport", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL("port"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_1, oldc, "getconnecttimeout", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL("timeout"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_1, oldc, "ispersistent", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL("persistent"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(NULL, newc, "__construct", NULL, 1, _0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, newc, "connect", NULL, 2);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("connection"), newc TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

