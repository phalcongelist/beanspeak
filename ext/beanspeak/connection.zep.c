
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
#include "kernel/file.h"
#include "kernel/string.h"
#include "kernel/concat.h"


/**
 * Beanspeak\Connection
 *
 * Represents a connection to a beanstalkd instance.
 */
ZEPHIR_INIT_CLASS(Beanspeak_Connection) {

	ZEPHIR_REGISTER_CLASS(Beanspeak, Connection, beanspeak, connection, beanspeak_connection_method_entry, 0);

	zend_declare_property_null(beanspeak_connection_ce, SL("socket"), ZEND_ACC_PRIVATE TSRMLS_CC);

	/**
	 * Connection options
	 */
	zend_declare_property_null(beanspeak_connection_ce, SL("options"), ZEND_ACC_PRIVATE TSRMLS_CC);

	beanspeak_connection_ce->create_object = zephir_init_properties_Beanspeak_Connection;

	zend_class_implements(beanspeak_connection_ce TSRMLS_CC, 1, beanspeak_connection_connectioninterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Connection constructor
 */
PHP_METHOD(Beanspeak_Connection, __construct) {

	zval *_5 = NULL, *_7 = NULL;
	zval *options_param = NULL, *_0$$3, *_1$$4, *_2$$5, *_3$$7, *_4, *_6, *_8, *_9, *_10, *_11, *_12, *_13;
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
	if (!(zephir_array_isset_string(options, SS("write_retries")))) {
		ZEPHIR_INIT_VAR(_3$$7);
		ZVAL_LONG(_3$$7, 8);
		zephir_array_update_string(&options, SL("write_retries"), &_3$$7, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_OBS_VAR(_4);
	zephir_array_fetch_string(&_4, options, SL("host"), PH_NOISY, "beanspeak/connection.zep", 62 TSRMLS_CC);
	zephir_get_strval(_5, _4);
	zephir_array_update_string(&options, SL("host"), &_5, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_VAR(_6);
	zephir_array_fetch_string(&_6, options, SL("port"), PH_NOISY, "beanspeak/connection.zep", 63 TSRMLS_CC);
	zephir_get_strval(_7, _6);
	zephir_array_update_string(&options, SL("port"), &_7, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_VAR(_8);
	zephir_array_fetch_string(&_8, options, SL("timeout"), PH_NOISY, "beanspeak/connection.zep", 64 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_9);
	ZVAL_LONG(_9, zephir_get_intval(_8));
	zephir_array_update_string(&options, SL("timeout"), &_9, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_VAR(_10);
	zephir_array_fetch_string(&_10, options, SL("write_retries"), PH_NOISY, "beanspeak/connection.zep", 65 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_11);
	ZVAL_LONG(_11, zephir_get_intval(_10));
	zephir_array_update_string(&options, SL("write_retries"), &_11, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_VAR(_12);
	zephir_array_fetch_string(&_12, options, SL("persistent"), PH_NOISY, "beanspeak/connection.zep", 66 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_13);
	ZVAL_BOOL(_13, zephir_get_boolval(_12));
	zephir_array_update_string(&options, SL("persistent"), &_13, PH_COPY | PH_SEPARATE);
	zephir_update_property_this(this_ptr, SL("options"), options TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Connection, isConnected) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("socket"), PH_NOISY_CC);
	RETURN_MM_BOOL(Z_TYPE_P(_0) == IS_RESOURCE);

}

/**
 * {@inheritdoc}
 *
 * @throws \Beanspeak\Connection\Exception
 */
PHP_METHOD(Beanspeak_Connection, connect) {

	zval *_0 = NULL, *options$$3 = NULL, *socket$$3 = NULL, *function$$3 = NULL, *_1$$3, *_2$$3, *_3$$3, *_4$$3, *_5$$3, *_6$$3, *_7$$3, _8$$3, _9$$3;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isconnected", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		_1$$3 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
		ZEPHIR_CPY_WRT(options$$3, _1$$3);
		zephir_array_fetch_string(&_2$$3, options$$3, SL("persistent"), PH_NOISY | PH_READONLY, "beanspeak/connection.zep", 91 TSRMLS_CC);
		ZEPHIR_INIT_VAR(function$$3);
		if (zephir_is_true(_2$$3)) {
			ZVAL_STRING(function$$3, "pfsockopen", 1);
		} else {
			ZVAL_STRING(function$$3, "fsockopen", 1);
		}
		zephir_array_fetch_string(&_3$$3, options$$3, SL("host"), PH_NOISY | PH_READONLY, "beanspeak/connection.zep", 97 TSRMLS_CC);
		zephir_array_fetch_string(&_4$$3, options$$3, SL("port"), PH_NOISY | PH_READONLY, "beanspeak/connection.zep", 97 TSRMLS_CC);
		zephir_array_fetch_string(&_5$$3, options$$3, SL("timeout"), PH_NOISY | PH_READONLY, "beanspeak/connection.zep", 97 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_6$$3);
		ZVAL_NULL(_6$$3);
		ZEPHIR_INIT_VAR(_7$$3);
		ZVAL_NULL(_7$$3);
		ZEPHIR_CALL_ZVAL_FUNCTION(&socket$$3, function$$3, NULL, 0, _3$$3, _4$$3, _6$$3, _7$$3, _5$$3);
		zephir_check_call_status();
		if (Z_TYPE_P(socket$$3) != IS_RESOURCE) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_connection_exception_ce, "Can't connect to Beanstalk server.", "beanspeak/connection.zep", 100);
			return;
		}
		ZEPHIR_SINIT_VAR(_8$$3);
		ZVAL_LONG(&_8$$3, -1);
		ZEPHIR_SINIT_VAR(_9$$3);
		ZVAL_LONG(&_9$$3, 0);
		ZEPHIR_CALL_FUNCTION(NULL, "stream_set_timeout", NULL, 13, socket$$3, &_8$$3, &_9$$3);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("socket"), socket$$3 TSRMLS_CC);
	}
	RETURN_MM_MEMBER(this_ptr, "socket");

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Connection, disconnect) {

	zval *socket = NULL, *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("socket"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(socket, _0);
	if (Z_TYPE_P(socket) != IS_RESOURCE) {
		RETURN_MM_BOOL(0);
	}
	zephir_fclose(socket TSRMLS_CC);
	RETURN_MM_BOOL(1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Connection, getHost) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	zephir_array_fetch_string(&_1, _0, SL("host"), PH_NOISY | PH_READONLY, "beanspeak/connection.zep", 133 TSRMLS_CC);
	RETURN_CTORW(_1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Connection, getPort) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	zephir_array_fetch_string(&_1, _0, SL("port"), PH_NOISY | PH_READONLY, "beanspeak/connection.zep", 141 TSRMLS_CC);
	RETURN_CTORW(_1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Connection, getConnectTimeout) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	zephir_array_fetch_string(&_1, _0, SL("timeout"), PH_NOISY | PH_READONLY, "beanspeak/connection.zep", 149 TSRMLS_CC);
	RETURN_CTORW(_1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Connection, getWriteRetries) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	zephir_array_fetch_string(&_1, _0, SL("write_retries"), PH_NOISY | PH_READONLY, "beanspeak/connection.zep", 157 TSRMLS_CC);
	RETURN_CTORW(_1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Connection, isPersistent) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	zephir_array_fetch_string(&_1, _0, SL("persistent"), PH_NOISY | PH_READONLY, "beanspeak/connection.zep", 165 TSRMLS_CC);
	RETURN_CTORW(_1);

}

/**
 * {@inheritdoc}
 *
 * @throws \Beanspeak\Connection\Exception
 */
PHP_METHOD(Beanspeak_Connection, write) {

	zend_bool _2$$3;
	zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, step = 0;
	zval *data_param = NULL, *socket = NULL, *part = NULL, *fwritec = NULL, *retries = NULL, *written = NULL, *_0, *_1, *_3$$4 = NULL, *_4$$4 = NULL;
	zval *data = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &data_param);

	zephir_get_strval(data, data_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "connect", NULL, 0);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(retries);
	zephir_array_fetch_string(&retries, _0, SL("write_retries"), PH_NOISY, "beanspeak/connection.zep", 180 TSRMLS_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("socket"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(socket, _1);
	step = 0;
	ZEPHIR_INIT_VAR(fwritec);
	ZVAL_LONG(fwritec, 0);
	ZEPHIR_INIT_VAR(written);
	ZVAL_LONG(written, 0);
	while (1) {
		if (!(ZEPHIR_LT_LONG(written, zephir_fast_strlen_ev(data)))) {
			break;
		}
		step++;
		_2$$3 = ZEPHIR_LE_LONG(retries, step);
		if (_2$$3) {
			_2$$3 = !zephir_is_true(written);
		}
		if (_2$$3) {
			ZEPHIR_INIT_NVAR(_3$$4);
			object_init_ex(_3$$4, beanspeak_connection_exception_ce);
			ZEPHIR_INIT_LNVAR(_4$$4);
			ZEPHIR_CONCAT_SVS(_4$$4, "Failed to write data to socket after ", retries, " tries");
			ZEPHIR_CALL_METHOD(NULL, _3$$4, "__construct", &_5, 1, _4$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(_3$$4, "beanspeak/connection.zep", 190 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_NVAR(part);
		zephir_substr(part, data, zephir_get_intval(written), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		ZEPHIR_INIT_NVAR(fwritec);
		zephir_fwrite(fwritec, socket, part TSRMLS_CC);
		ZEPHIR_ADD_ASSIGN(written, fwritec);
	}
	RETURN_CCTOR(written);

}

/**
 * {@inheritdoc}
 *
 * @throws \Beanspeak\Connection\Exception
 */
PHP_METHOD(Beanspeak_Connection, read) {

	zval *length_param = NULL, *socket = NULL, *data = NULL, *meta = NULL, *_0, _1, *_2;
	int length, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &length_param);

	if (!length_param) {
		length = 0;
	} else {
		length = zephir_get_intval(length_param);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "connect", NULL, 0);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("socket"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(socket, _0);
	if (!(length)) {
		length = 16384;
	}
	if (zephir_feof(socket TSRMLS_CC)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_connection_exception_ce, "Failed to read data from socket (EOF)", "beanspeak/connection.zep", 221);
		return;
	}
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_LONG(&_1, length);
	ZEPHIR_CALL_FUNCTION(&data, "stream_get_line", NULL, 14, socket, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&meta, "stream_get_meta_data", NULL, 15, socket);
	zephir_check_call_status();
	zephir_array_fetch_string(&_2, meta, SL("timed_out"), PH_NOISY | PH_READONLY, "beanspeak/connection.zep", 227 TSRMLS_CC);
	if (zephir_is_true(_2)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_connection_exception_ce, "Connection timed out upon attempt to read data from socket", "beanspeak/connection.zep", 228);
		return;
	}
	if (ZEPHIR_IS_FALSE_IDENTICAL(data)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_connection_exception_ce, "Failed to read data from socket", "beanspeak/connection.zep", 232);
		return;
	}
	RETURN_CCTOR(data);

}

/**
 * {@inheritdoc}
 * Trailing whitespace is trimmed.
 *
 * @throws \Beanspeak\Connection\Exception
 */
PHP_METHOD(Beanspeak_Connection, getLine) {

	zephir_fcall_cache_entry *_2 = NULL, *_3 = NULL;
	zval *length_param = NULL, *socket = NULL, *data = NULL, *meta = NULL, *_0, _1$$5 = zval_used_for_init, *_4$$3;
	int length, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &length_param);

	if (!length_param) {
		length = 0;
	} else {
		length = zephir_get_intval(length_param);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "connect", NULL, 0);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("socket"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(socket, _0);
	do {
		if (zephir_feof(socket TSRMLS_CC)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_connection_exception_ce, "Failed to get line from socket (EOF)", "beanspeak/connection.zep", 255);
			return;
		}
		if (length) {
			ZEPHIR_SINIT_NVAR(_1$$5);
			ZVAL_LONG(&_1$$5, length);
			ZEPHIR_CALL_FUNCTION(&data, "fgets", &_2, 16, socket, &_1$$5);
			zephir_check_call_status();
		} else {
			ZEPHIR_CALL_FUNCTION(&data, "fgets", &_2, 16, socket);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_FUNCTION(&meta, "stream_get_meta_data", &_3, 15, socket);
		zephir_check_call_status();
		zephir_array_fetch_string(&_4$$3, meta, SL("timed_out"), PH_NOISY | PH_READONLY, "beanspeak/connection.zep", 266 TSRMLS_CC);
		if (zephir_is_true(_4$$3)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_connection_exception_ce, "Connection timed out upon attempt to get line from socket", "beanspeak/connection.zep", 267);
			return;
		}
	} while (ZEPHIR_IS_FALSE_IDENTICAL(data));
	zephir_fast_trim(return_value, data, NULL , ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	RETURN_MM();

}

static zend_object_value zephir_init_properties_Beanspeak_Connection(zend_class_entry *class_type TSRMLS_DC) {

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

