
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
#include "kernel/array.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"


/**
 * Beanstalk\Connection
 *
 * Represents a connection to a beanstalkd instance
 */
ZEPHIR_INIT_CLASS(Beanstalk_Connection) {

	ZEPHIR_REGISTER_CLASS(Beanstalk, Connection, beanstalk, connection, beanstalk_connection_method_entry, 0);

	zend_declare_property_null(beanstalk_connection_ce, SL("socket"), ZEND_ACC_PRIVATE TSRMLS_CC);

	/**
	 * Connection options
	 */
	zend_declare_property_null(beanstalk_connection_ce, SL("options"), ZEND_ACC_PRIVATE TSRMLS_CC);

	beanstalk_connection_ce->create_object = zephir_init_properties_Beanstalk_Connection;

	zend_class_implements(beanstalk_connection_ce TSRMLS_CC, 1, beanstalk_connection_connectioninterface_ce);
	return SUCCESS;

}

/**
 * Beanstalk\Connection constructor
 */
PHP_METHOD(Beanstalk_Connection, __construct) {

	zval *_4 = NULL, *_6 = NULL;
	zval *options_param = NULL, *_0$$3, *_1$$4, *_2$$5, *_3, *_5, *_7, *_8, *_9, *_10;
	zval *options = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &options_param);

	if (!options_param) {
		ZEPHIR_INIT_VAR(options);
		array_init(options);
	} else {
		zephir_get_arrval(options, options_param);
	}


	if (!(zephir_array_isset_string(options, SS("host")))) {
		ZEPHIR_INIT_VAR(_0$$3);
		ZVAL_STRING(_0$$3, "127.0.0.1", 1);
		zephir_array_update_string(&options, SL("host"), &_0$$3, PH_COPY | PH_SEPARATE);
	}
	if (!(zephir_array_isset_string(options, SS("port")))) {
		ZEPHIR_INIT_VAR(_1$$4);
		ZVAL_LONG(_1$$4, 11300);
		zephir_array_update_string(&options, SL("port"), &_1$$4, PH_COPY | PH_SEPARATE);
	}
	if (!(zephir_array_isset_string(options, SS("timeout")))) {
		ZEPHIR_INIT_VAR(_2$$5);
		ZVAL_LONG(_2$$5, 60);
		zephir_array_update_string(&options, SL("timeout"), &_2$$5, PH_COPY | PH_SEPARATE);
	}
	if (!(zephir_array_isset_string(options, SS("persistent")))) {
		zephir_array_update_string(&options, SL("persistent"), &ZEPHIR_GLOBAL(global_false), PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_OBS_VAR(_3);
	zephir_array_fetch_string(&_3, options, SL("host"), PH_NOISY, "beanstalk/connection.zep", 58 TSRMLS_CC);
	zephir_get_strval(_4, _3);
	zephir_array_update_string(&options, SL("host"), &_4, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_VAR(_5);
	zephir_array_fetch_string(&_5, options, SL("port"), PH_NOISY, "beanstalk/connection.zep", 59 TSRMLS_CC);
	zephir_get_strval(_6, _5);
	zephir_array_update_string(&options, SL("port"), &_6, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_VAR(_7);
	zephir_array_fetch_string(&_7, options, SL("timeout"), PH_NOISY, "beanstalk/connection.zep", 60 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_8);
	ZVAL_LONG(_8, zephir_get_intval(_7));
	zephir_array_update_string(&options, SL("timeout"), &_8, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_VAR(_9);
	zephir_array_fetch_string(&_9, options, SL("persistent"), PH_NOISY, "beanstalk/connection.zep", 61 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_10);
	ZVAL_BOOL(_10, zephir_get_boolval(_9));
	zephir_array_update_string(&options, SL("persistent"), &_10, PH_COPY | PH_SEPARATE);
	zephir_update_property_this(this_ptr, SL("options"), options TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 *
 * @throws \Beanstalk\Connection\Exception
 */
PHP_METHOD(Beanstalk_Connection, connect) {

	zval *options = NULL, *socket = NULL, *function = NULL, *_0, *_1, *_2, *_3, *_4, *_5, *_6, _7, _8;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(options, _0);
	zephir_array_fetch_string(&_1, options, SL("persistent"), PH_NOISY | PH_READONLY, "beanstalk/connection.zep", 77 TSRMLS_CC);
	ZEPHIR_INIT_VAR(function);
	if (zephir_is_true(_1)) {
		ZVAL_STRING(function, "pfsockopen", 1);
	} else {
		ZVAL_STRING(function, "fsockopen", 1);
	}
	zephir_array_fetch_string(&_2, options, SL("host"), PH_NOISY | PH_READONLY, "beanstalk/connection.zep", 83 TSRMLS_CC);
	zephir_array_fetch_string(&_3, options, SL("port"), PH_NOISY | PH_READONLY, "beanstalk/connection.zep", 83 TSRMLS_CC);
	zephir_array_fetch_string(&_4, options, SL("timeout"), PH_NOISY | PH_READONLY, "beanstalk/connection.zep", 83 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_5);
	ZVAL_NULL(_5);
	ZEPHIR_INIT_VAR(_6);
	ZVAL_NULL(_6);
	ZEPHIR_CALL_ZVAL_FUNCTION(&socket, function, NULL, 0, _2, _3, _5, _6, _4);
	zephir_check_call_status();
	if (Z_TYPE_P(socket) != IS_RESOURCE) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanstalk_connection_exception_ce, "Can't connect to Beanstalk server.", "beanstalk/connection.zep", 86);
		return;
	}
	ZEPHIR_SINIT_VAR(_7);
	ZVAL_LONG(&_7, -1);
	ZEPHIR_SINIT_VAR(_8);
	ZVAL_LONG(&_8, 0);
	ZEPHIR_CALL_FUNCTION(NULL, "stream_set_timeout", NULL, 2, socket, &_7, &_8);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("socket"), socket TSRMLS_CC);
	RETURN_CCTOR(socket);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanstalk_Connection, getHost) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	zephir_array_fetch_string(&_1, _0, SL("host"), PH_NOISY | PH_READONLY, "beanstalk/connection.zep", 101 TSRMLS_CC);
	RETURN_CTORW(_1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanstalk_Connection, getPort) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	zephir_array_fetch_string(&_1, _0, SL("port"), PH_NOISY | PH_READONLY, "beanstalk/connection.zep", 109 TSRMLS_CC);
	RETURN_CTORW(_1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanstalk_Connection, getConnectTimeout) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	zephir_array_fetch_string(&_1, _0, SL("timeout"), PH_NOISY | PH_READONLY, "beanstalk/connection.zep", 117 TSRMLS_CC);
	RETURN_CTORW(_1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanstalk_Connection, isPersistent) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	zephir_array_fetch_string(&_1, _0, SL("persistent"), PH_NOISY | PH_READONLY, "beanstalk/connection.zep", 125 TSRMLS_CC);
	RETURN_CTORW(_1);

}

static zend_object_value zephir_init_properties_Beanstalk_Connection(zend_class_entry *class_type TSRMLS_DC) {

		zval *_0, *_1$$3;

		ZEPHIR_MM_GROW();
	
	{
		zval *this_ptr = NULL;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
		if (Z_TYPE_P(_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(_1$$3);
			array_init(_1$$3);
			zephir_update_property_this(this_ptr, SL("options"), _1$$3 TSRMLS_CC);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJVAL_P(this_ptr);
	}

}

