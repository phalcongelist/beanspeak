
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
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "kernel/hash.h"
#include "kernel/file.h"
#include "kernel/string.h"
#include "kernel/concat.h"
#include "ext/spl/spl_exceptions.h"


/**
 * Beanspeak\Client
 *
 * Class to access the beanstalk queue service.
 *
 * Implements the beanstalk protocol spec 1.10.
 *
 * <code>
 * use Beanspeak\Client;
 *
 * // Each connection parameter is optional
 * $queue = new Client([
 *     'host'       => '127.0.0.1', // The beanstalk server hostname or IP address to connect to
 *     'port'       => 11300,       // The port of the server to connect to
 *     'timeout'    => 60,          // Timeout in seconds when establishing the connection
 *     'persistent' => true,        // Whether to make the connection persistent or not
 *     'wretries'   => 8,           // Write retries
 * ]);
 * </code>
 *
 * @link https://github.com/kr/beanstalkd/
 */
ZEPHIR_INIT_CLASS(Beanspeak_Client) {

	ZEPHIR_REGISTER_CLASS(Beanspeak, Client, beanspeak, client, beanspeak_client_method_entry, 0);

	/**
	 * The current socket connection.
	 * @var resource
	 */
	zend_declare_property_null(beanspeak_client_ce, SL("socket"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The current connection options.
	 * @var array
	 */
	zend_declare_property_null(beanspeak_client_ce, SL("options"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The current used tube.
	 * @var string
	 */
	zend_declare_property_string(beanspeak_client_ce, SL("usedTube"), "default", ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The current watched tubes.
	 * @var array
	 */
	zend_declare_property_null(beanspeak_client_ce, SL("watchedTubes"), ZEND_ACC_PROTECTED TSRMLS_CC);

	beanspeak_client_ce->create_object = zephir_init_properties_Beanspeak_Client;
	return SUCCESS;

}

/**
 * Beanspeak\Client constructor
 */
PHP_METHOD(Beanspeak_Client, __construct) {

	zval *options_param = NULL, __$true, _0$$4;
	zval options, defaults;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&defaults);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&_0$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &options_param);

	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}


	ZEPHIR_INIT_VAR(&defaults);
	zephir_create_array(&defaults, 5, 0 TSRMLS_CC);
	add_assoc_stringl_ex(&defaults, SL("host"), SL("127.0.0.1"));
	add_assoc_long_ex(&defaults, SL("port"), 11300);
	zephir_array_update_string(&defaults, SL("persistent"), &__$true, PH_COPY | PH_SEPARATE);
	add_assoc_long_ex(&defaults, SL("timeout"), 60);
	add_assoc_long_ex(&defaults, SL("wretries"), 8);
	if (1 != 1) {
		zephir_update_property_zval(this_ptr, SL("options"), &defaults);
	} else {
		ZEPHIR_INIT_VAR(&_0$$4);
		zephir_add_function(&_0$$4, &options, &defaults);
		zephir_update_property_zval(this_ptr, SL("options"), &_0$$4);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Makes a connection to the Beanstalk server.
 *
 * The resulting stream will not have any timeout set on it.
 * Which means it can wait an unlimited amount of time until a packet
 * becomes available.
 *
 * @throws Exception
 */
PHP_METHOD(Beanspeak_Client, connect) {

	zend_string *_20;
	zend_ulong _19;
	zephir_fcall_cache_entry *_22 = NULL;
	zval __$null, e, options, socket, usedTube, tube, _0, _1, _17, *_18, _23, _2$$4, _3$$5, _4$$5, _5$$5, _6$$5, _7$$5, _8$$6, _9$$6, _10$$6, _11$$6, _12$$6, _13$$7, _14$$7, _15$$8, _16$$8, _21$$11, _24$$12;
	int ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&e);
	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&socket);
	ZVAL_UNDEF(&usedTube);
	ZVAL_UNDEF(&tube);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_21$$11);
	ZVAL_UNDEF(&_24$$12);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isconnected", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "disconnect", NULL, 0);
		zephir_check_call_status();
	}
	zephir_read_property(&_1, this_ptr, SL("options"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&options, &_1);

	/* try_start_1: */

		zephir_array_fetch_string(&_2$$4, &options, SL("persistent"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 108 TSRMLS_CC);
		if (zephir_is_true(&_2$$4)) {
			zephir_array_fetch_string(&_3$$5, &options, SL("host"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 109 TSRMLS_CC);
			zephir_array_fetch_string(&_4$$5, &options, SL("port"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 109 TSRMLS_CC);
			zephir_array_fetch_string(&_5$$5, &options, SL("timeout"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 109 TSRMLS_CC);
			ZVAL_NULL(&_6$$5);
			ZVAL_NULL(&_7$$5);
			ZEPHIR_MAKE_REF(&_6$$5);
			ZEPHIR_MAKE_REF(&_7$$5);
			ZEPHIR_CALL_FUNCTION(&socket, "pfsockopen", NULL, 1, &_3$$5, &_4$$5, &_6$$5, &_7$$5, &_5$$5);
			ZEPHIR_UNREF(&_6$$5);
			ZEPHIR_UNREF(&_7$$5);
			zephir_check_call_status_or_jump(try_end_1);
		} else {
			zephir_array_fetch_string(&_8$$6, &options, SL("host"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 111 TSRMLS_CC);
			zephir_array_fetch_string(&_9$$6, &options, SL("port"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 111 TSRMLS_CC);
			zephir_array_fetch_string(&_10$$6, &options, SL("timeout"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 111 TSRMLS_CC);
			ZVAL_NULL(&_11$$6);
			ZVAL_NULL(&_12$$6);
			ZEPHIR_MAKE_REF(&_11$$6);
			ZEPHIR_MAKE_REF(&_12$$6);
			ZEPHIR_CALL_FUNCTION(&socket, "fsockopen", NULL, 2, &_8$$6, &_9$$6, &_11$$6, &_12$$6, &_10$$6);
			ZEPHIR_UNREF(&_11$$6);
			ZEPHIR_UNREF(&_12$$6);
			zephir_check_call_status_or_jump(try_end_1);
		}
		if (Z_TYPE_P(&socket) != IS_RESOURCE) {
			ZEPHIR_INIT_VAR(&_13$$7);
			object_init_ex(&_13$$7, beanspeak_exception_ce);
			ZEPHIR_INIT_VAR(&_14$$7);
			ZVAL_STRING(&_14$$7, "Can't connect to Beanstalk server.");
			ZEPHIR_CALL_METHOD(NULL, &_13$$7, "__construct", NULL, 3, &_14$$7);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_throw_exception_debug(&_13$$7, "beanspeak/client.zep", 115 TSRMLS_CC);
			goto try_end_1;

		}

	try_end_1:

	if (EG(exception)) {
		ZVAL_OBJ(&e, EG(exception));
		Z_ADDREF_P(&e);
		if (zephir_instance_of_ev(&e, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_INIT_VAR(&_15$$8);
			object_init_ex(&_15$$8, beanspeak_exception_ce);
			ZEPHIR_CALL_METHOD(&_16$$8, &e, "getmessage", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &_15$$8, "__construct", NULL, 3, &_16$$8);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_15$$8, "beanspeak/client.zep", 118 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZVAL_LONG(&_1, -1);
	ZEPHIR_CALL_FUNCTION(NULL, "stream_set_timeout", NULL, 4, &socket, &_1, &__$null);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("socket"), &socket);
	zephir_read_property(&_1, this_ptr, SL("usedTube"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&usedTube, &_1);
	if (!ZEPHIR_IS_STRING(&usedTube, "default")) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "usetube", NULL, 0, &usedTube);
		zephir_check_call_status();
	}
	zephir_read_property(&_1, this_ptr, SL("watchedTubes"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_17);
	zephir_is_iterable(&_1, 0, "beanspeak/client.zep", 137);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_1), _19, _20, _18)
	{
		ZEPHIR_INIT_NVAR(&tube);
		if (_20 != NULL) { 
			ZVAL_STR_COPY(&tube, _20);
		} else {
			ZVAL_LONG(&tube, _19);
		}
		ZEPHIR_INIT_NVAR(&_17);
		ZVAL_COPY(&_17, _18);
		if (!ZEPHIR_IS_STRING(&tube, "default")) {
			zephir_read_property(&_21$$11, this_ptr, SL("watchedTubes"), PH_NOISY_CC | PH_READONLY);
			zephir_array_unset(&_21$$11, &tube, PH_SEPARATE);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "watch", &_22, 0, &tube);
			zephir_check_call_status();
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&_17);
	ZEPHIR_INIT_NVAR(&tube);
	zephir_read_property(&_23, this_ptr, SL("watchedTubes"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_string(&_23, SL("default")))) {
		ZEPHIR_INIT_VAR(&_24$$12);
		ZVAL_STRING(&_24$$12, "default");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "ignore", NULL, 0, &_24$$12);
		zephir_check_call_status();
	}
	RETURN_CCTOR(socket);

}

/**
 * Closes the connection to the Beanstalk server.
 *
 * Will throw an exception if closing the connection fails, to allow
 * handling the then undefined state.
 *
 * @throws Exception
 */
PHP_METHOD(Beanspeak_Client, disconnect) {

	zval _3;
	zval __$null, __$true, socket, status, _0, _1, _2;
	int ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_NULL(&__$null);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&socket);
	ZVAL_UNDEF(&status);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isconnected", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		RETURN_MM_BOOL(0);
	}
	zephir_read_property(&_1, this_ptr, SL("socket"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&socket, &_1);
	ZEPHIR_INIT_VAR(&status);
	ZVAL_BOOL(&status, zephir_fclose(&socket TSRMLS_CC));
	if (!(zephir_is_true(&status))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_exception_ce, "Failed to close connection.", "beanspeak/client.zep", 164);
		return;
	}
	zephir_update_property_zval(this_ptr, SL("socket"), &__$null);
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "default");
	zephir_update_property_zval(this_ptr, SL("usedTube"), &_2);
	ZEPHIR_INIT_VAR(&_3);
	zephir_create_array(&_3, 1, 0 TSRMLS_CC);
	zephir_array_update_string(&_3, SL("default"), &__$true, PH_COPY | PH_SEPARATE);
	zephir_update_property_zval(this_ptr, SL("watchedTubes"), &_3);
	RETURN_MM_BOOL(1);

}

/**
 * Whether the connection is established or not.
 */
PHP_METHOD(Beanspeak_Client, isConnected) {

	zval _0;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("socket"), PH_NOISY_CC);
	RETURN_MM_BOOL(Z_TYPE_P(&_0) == IS_RESOURCE);

}

/**
 * Inserts a job into the client's currently used tube.
 *
 * <code>
 * $task = [
 *     'recipient' => 'user@mail.com',
 *     'subject'   => 'Welcome',
 *     'content'   => $content,
 * ];
 *
 * $put = $queue->pit($task, 999, 60 * 60, 3600);
 * </code>
 */
PHP_METHOD(Beanspeak_Client, put) {

	zend_bool _4$$3;
	int priority, delay, ttr, ZEPHIR_LAST_CALL_STATUS;
	zval *data, data_sub, *priority_param = NULL, *delay_param = NULL, *ttr_param = NULL, status, response, serialized, length, _0, _1, _2, _3, _5$$4;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&status);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&serialized);
	ZVAL_UNDEF(&length);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 3, &data, &priority_param, &delay_param, &ttr_param);

	if (!priority_param) {
		priority = 1024;
	} else {
		priority = zephir_get_intval(priority_param);
	}
	if (!delay_param) {
		delay = 0;
	} else {
		delay = zephir_get_intval(delay_param);
	}
	if (!ttr_param) {
		ttr = 86400;
	} else {
		ttr = zephir_get_intval(ttr_param);
	}


	ZEPHIR_CALL_FUNCTION(&serialized, "serialize", NULL, 5, data);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&length);
	ZVAL_LONG(&length, zephir_fast_strlen_ev(&serialized));
	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, priority);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_LONG(&_1, delay);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_LONG(&_2, ttr);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SVSVSVSVSV(&_3, "put ", &_0, " ", &_1, " ", &_2, " ", &length, "\r\n", &serialized);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	if (zephir_array_isset_long(&response, 1)) {
		zephir_array_fetch_long(&status, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 208 TSRMLS_CC);
		_4$$3 = ZEPHIR_IS_STRING(&status, "INSERTED");
		if (!(_4$$3)) {
			_4$$3 = ZEPHIR_IS_STRING(&status, "BURIED");
		}
		if (_4$$3) {
			ZEPHIR_OBS_VAR(&_5$$4);
			zephir_array_fetch_long(&_5$$4, &response, 1, PH_NOISY, "beanspeak/client.zep", 211 TSRMLS_CC);
			RETURN_MM_LONG(zephir_get_intval(&_5$$4));
		}
	}
	RETURN_MM_BOOL(0);

}

/**
 * Inserts a job into the desired tube.
 *
 * <code>
 * $task = [
 *     'recipient' => 'user@mail.com',
 *     'subject'   => 'Welcome',
 *     'content'   => $content,
 * ];
 *
 * $queue->putInTube('tube-name', $task, 999, 60 * 60, 3600);
 * </code>
 */
PHP_METHOD(Beanspeak_Client, putInTube) {

	int priority, delay, ttr, ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, *data, data_sub, *priority_param = NULL, *delay_param = NULL, *ttr_param = NULL, response, _0$$3, _1$$3, _2$$3;
	zval tube;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&tube);
	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 3, &tube_param, &data, &priority_param, &delay_param, &ttr_param);

	if (unlikely(Z_TYPE_P(tube_param) != IS_STRING && Z_TYPE_P(tube_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tube' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (likely(Z_TYPE_P(tube_param) == IS_STRING)) {
		zephir_get_strval(&tube, tube_param);
	} else {
		ZEPHIR_INIT_VAR(&tube);
		ZVAL_EMPTY_STRING(&tube);
	}
	if (!priority_param) {
		priority = 1024;
	} else {
		priority = zephir_get_intval(priority_param);
	}
	if (!delay_param) {
		delay = 0;
	} else {
		delay = zephir_get_intval(delay_param);
	}
	if (!ttr_param) {
		ttr = 86400;
	} else {
		ttr = zephir_get_intval(ttr_param);
	}


	ZEPHIR_CALL_METHOD(&response, this_ptr, "usetube", NULL, 0, &tube);
	zephir_check_call_status();
	if (Z_TYPE_P(&response) == IS_OBJECT) {
		ZVAL_LONG(&_0$$3, priority);
		ZVAL_LONG(&_1$$3, delay);
		ZVAL_LONG(&_2$$3, ttr);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "put", NULL, 0, data, &_0$$3, &_1$$3, &_2$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(0);

}

/**
 * Change the active tube.
 *
 * The "use" command is for producers. Subsequent put commands will put jobs
 * into the tube specified by this command. If no use command has been issued,
 * jobs will be put into the tube named "default".
 *
 * <code>
 * $queue->useTube('mail-queue');
 * </code>
 *
 * @throws Exception
 */
PHP_METHOD(Beanspeak_Client, useTube) {

	zend_bool _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, response, status, used, _2, _3, _4, _5;
	zval tube, _0;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&tube);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&status);
	ZVAL_UNDEF(&used);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tube_param);

	if (unlikely(Z_TYPE_P(tube_param) != IS_STRING && Z_TYPE_P(tube_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tube' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (likely(Z_TYPE_P(tube_param) == IS_STRING)) {
		zephir_get_strval(&tube, tube_param);
	} else {
		ZEPHIR_INIT_VAR(&tube);
		ZVAL_EMPTY_STRING(&tube);
	}


	ZEPHIR_OBS_VAR(&used);
	zephir_read_property(&used, this_ptr, SL("usedTube"), PH_NOISY_CC);
	if (ZEPHIR_IS_EQUAL(&used, &tube)) {
		RETURN_THIS();
	}
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_CONCAT_SV(&_0, "use ", &tube);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_1 = zephir_array_isset_long(&response, 1);
	if (_1) {
		zephir_array_fetch_long(&_2, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 269 TSRMLS_CC);
		_1 = ZEPHIR_IS_STRING(&_2, "USING");
	}
	if (_1) {
		ZEPHIR_OBS_VAR(&status);
		zephir_array_fetch_long(&status, &response, 0, PH_NOISY, "beanspeak/client.zep", 270 TSRMLS_CC);
		if (ZEPHIR_IS_STRING(&status, "USING")) {
			zephir_update_property_zval(this_ptr, SL("usedTube"), &tube);
			RETURN_THIS();
		}
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, beanspeak_exception_ce);
	ZEPHIR_INIT_VAR(&_4);
	zephir_fast_join_str(&_4, SL(" "), &response TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SV(&_5, "Unable to change the active tube. Server response: ", &_4);
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "beanspeak/client.zep", 280 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Lets the client inspect a job in the system.
 *
 * <code>
 * $peekJob = $queue->peek($jobId);
 * </code>
 */
PHP_METHOD(Beanspeak_Client, peekJob) {

	zend_bool _2;
	zval _1;
	zval *id_param = NULL, response, _0, _3, _4$$3, _5$$3, _6$$3, _7$$3;
	int id, ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &id_param);

	id = zephir_get_intval(id_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, id);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SV(&_1, "peek ", &_0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_2 = zephir_array_isset_long(&response, 2);
	if (_2) {
		zephir_array_fetch_long(&_3, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 297 TSRMLS_CC);
		_2 = ZEPHIR_IS_STRING(&_3, "FOUND");
	}
	if (_2) {
		object_init_ex(return_value, beanspeak_job_ce);
		zephir_array_fetch_long(&_4$$3, &response, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 298 TSRMLS_CC);
		zephir_array_fetch_long(&_6$$3, &response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 298 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_5$$3, this_ptr, "read", NULL, 0, &_6$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_7$$3, "unserialize", NULL, 7, &_5$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 8, this_ptr, &_4$$3, &_7$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(0);

}

/**
 * Return the delayed job with the shortest delay left.
 *
 * <code>
 * $queue->peekDelayed();
 * </code>
 */
PHP_METHOD(Beanspeak_Client, peekDelayed) {

	zend_bool _1;
	zval response, _0, _2, _3$$3, _4$$3, _5$$3, _6$$3;
	int ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "peek-delayed");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_1 = zephir_array_isset_long(&response, 2);
	if (_1) {
		zephir_array_fetch_long(&_2, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 318 TSRMLS_CC);
		_1 = ZEPHIR_IS_STRING(&_2, "FOUND");
	}
	if (_1) {
		object_init_ex(return_value, beanspeak_job_ce);
		zephir_array_fetch_long(&_3$$3, &response, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 319 TSRMLS_CC);
		zephir_array_fetch_long(&_5$$3, &response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 319 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_4$$3, this_ptr, "read", NULL, 0, &_5$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_6$$3, "unserialize", NULL, 7, &_4$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 8, this_ptr, &_3$$3, &_6$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(0);

}

/**
 * Return the next job in the list of buried jobs.
 *
 * <code>
 * $queue->peekBuried();
 * </code>
 */
PHP_METHOD(Beanspeak_Client, peekBuried) {

	zend_bool _1;
	zval response, _0, _2, _3$$3, _4$$3, _5$$3, _6$$3;
	int ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "peek-buried");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_1 = zephir_array_isset_long(&response, 2);
	if (_1) {
		zephir_array_fetch_long(&_2, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 339 TSRMLS_CC);
		_1 = ZEPHIR_IS_STRING(&_2, "FOUND");
	}
	if (_1) {
		object_init_ex(return_value, beanspeak_job_ce);
		zephir_array_fetch_long(&_3$$3, &response, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 340 TSRMLS_CC);
		zephir_array_fetch_long(&_5$$3, &response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 340 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_4$$3, this_ptr, "read", NULL, 0, &_5$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_6$$3, "unserialize", NULL, 7, &_4$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 8, this_ptr, &_3$$3, &_6$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(0);

}

/**
 * Inspect the next ready job.
 *
 * <code>
 * $queue->peekReady();
 * </code>
 */
PHP_METHOD(Beanspeak_Client, peekReady) {

	zend_bool _1;
	zval response, _0, _2, _3$$3, _4$$3, _5$$3, _6$$3;
	int ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "peek-ready");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_1 = zephir_array_isset_long(&response, 2);
	if (_1) {
		zephir_array_fetch_long(&_2, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 360 TSRMLS_CC);
		_1 = ZEPHIR_IS_STRING(&_2, "FOUND");
	}
	if (_1) {
		object_init_ex(return_value, beanspeak_job_ce);
		zephir_array_fetch_long(&_3$$3, &response, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 361 TSRMLS_CC);
		zephir_array_fetch_long(&_5$$3, &response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 361 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_4$$3, this_ptr, "read", NULL, 0, &_5$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_6$$3, "unserialize", NULL, 7, &_4$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 8, this_ptr, &_3$$3, &_6$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(0);

}

/**
 * Moves jobs into the ready queue.
 * The Kick command applies only to the currently used tube.
 *
 * <code>
 * $queue->kick(3);
 * </code>
 */
PHP_METHOD(Beanspeak_Client, kick) {

	zend_bool _2;
	zval _1;
	zval *bound_param = NULL, response, _0, _3, _4$$3;
	int bound, ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &bound_param);

	bound = zephir_get_intval(bound_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, bound);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SV(&_1, "kick ", &_0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_2 = zephir_array_isset_long(&response, 1);
	if (_2) {
		zephir_array_fetch_long(&_3, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 382 TSRMLS_CC);
		_2 = ZEPHIR_IS_STRING(&_3, "KICKED");
	}
	if (_2) {
		ZEPHIR_OBS_VAR(&_4$$3);
		zephir_array_fetch_long(&_4$$3, &response, 1, PH_NOISY, "beanspeak/client.zep", 383 TSRMLS_CC);
		RETURN_MM_LONG(zephir_get_intval(&_4$$3));
	}
	RETURN_MM_BOOL(0);

}

/**
 * Adds the named tube to the watch list, to reserve jobs from.
 *
 * <code>
 * $count = $queue->watch($tube);
 * </code>
 *
 * @throws Exception
 */
PHP_METHOD(Beanspeak_Client, watch) {

	zend_bool _2$$3;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, __$true, response, watchedTubes, _0, _3$$3, _4$$4, _5$$4, _6$$4;
	zval tube, _1$$3;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&tube);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&watchedTubes);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tube_param);

	if (unlikely(Z_TYPE_P(tube_param) != IS_STRING && Z_TYPE_P(tube_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tube' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (likely(Z_TYPE_P(tube_param) == IS_STRING)) {
		zephir_get_strval(&tube, tube_param);
	} else {
		ZEPHIR_INIT_VAR(&tube);
		ZVAL_EMPTY_STRING(&tube);
	}


	zephir_read_property(&_0, this_ptr, SL("watchedTubes"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&watchedTubes, &_0);
	if (!(zephir_array_isset(&watchedTubes, &tube))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		ZEPHIR_CONCAT_SV(&_1$$3, "watch ", &tube);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
		zephir_check_call_status();
		_2$$3 = !(zephir_array_isset_long(&response, 1));
		if (!(_2$$3)) {
			zephir_array_fetch_long(&_3$$3, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 407 TSRMLS_CC);
			_2$$3 = !ZEPHIR_IS_STRING(&_3$$3, "WATCHING");
		}
		if (_2$$3) {
			ZEPHIR_INIT_VAR(&_4$$4);
			object_init_ex(&_4$$4, beanspeak_exception_ce);
			ZEPHIR_INIT_VAR(&_5$$4);
			zephir_fast_join_str(&_5$$4, SL(" "), &response TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_6$$4);
			ZEPHIR_CONCAT_SV(&_6$$4, "Unhandled response: ", &_5$$4);
			ZEPHIR_CALL_METHOD(NULL, &_4$$4, "__construct", NULL, 3, &_6$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_4$$4, "beanspeak/client.zep", 408 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_array(this_ptr, SL("watchedTubes"), &tube, &__$true TSRMLS_CC);
	}
	RETURN_THIS();

}

/**
 * Adds the named tube to the watch list, to reserve jobs from, and
 * ignores any other tubes remaining on the watchlist.
 *
 * <code>
 * $count = $queue->watchOnly($tube);
 * </code>
 *
 * @throws Exception
 */
PHP_METHOD(Beanspeak_Client, watchOnly) {

	zend_string *_4;
	zend_ulong _3;
	zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, watchedTubes, watchedTube, _0, _1, *_2;
	zval tube;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&tube);
	ZVAL_UNDEF(&watchedTubes);
	ZVAL_UNDEF(&watchedTube);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tube_param);

	if (unlikely(Z_TYPE_P(tube_param) != IS_STRING && Z_TYPE_P(tube_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tube' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (likely(Z_TYPE_P(tube_param) == IS_STRING)) {
		zephir_get_strval(&tube, tube_param);
	} else {
		ZEPHIR_INIT_VAR(&tube);
		ZVAL_EMPTY_STRING(&tube);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "watch", NULL, 0, &tube);
	zephir_check_call_status();
	zephir_read_property(&_0, this_ptr, SL("watchedTubes"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&watchedTubes, &_0);
	ZEPHIR_INIT_VAR(&_1);
	zephir_is_iterable(&watchedTubes, 0, "beanspeak/client.zep", 442);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&watchedTubes), _3, _4, _2)
	{
		ZEPHIR_INIT_NVAR(&watchedTube);
		if (_4 != NULL) { 
			ZVAL_STR_COPY(&watchedTube, _4);
		} else {
			ZVAL_LONG(&watchedTube, _3);
		}
		ZEPHIR_INIT_NVAR(&_1);
		ZVAL_COPY(&_1, _2);
		if (ZEPHIR_IS_EQUAL(&watchedTube, &tube)) {
			continue;
		}
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "ignore", &_5, 0, &watchedTube);
		zephir_check_call_status();
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&_1);
	ZEPHIR_INIT_NVAR(&watchedTube);
	RETURN_THIS();

}

/**
 * Reserves/locks a ready job from the specified tube.
 *
 * <code>
 * $job = $queue->reserve();
 * </code>
 *
 * @throws Exception
 */
PHP_METHOD(Beanspeak_Client, reserve) {

	zend_bool _2;
	zval command;
	zval *timeout_param = NULL, response, _1, _3, _4, _5, _6, _0$$3;
	int timeout, ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&command);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &timeout_param);

	if (!timeout_param) {
		timeout = -1;
	} else {
		timeout = zephir_get_intval(timeout_param);
	}


	if (timeout >= 0) {
		ZEPHIR_SINIT_VAR(_0$$3);
		ZVAL_LONG(&_0$$3, timeout);
		ZEPHIR_INIT_VAR(&command);
		ZEPHIR_CONCAT_SV(&command, "reserve-with-timeout ", &_0$$3);
	} else {
		ZEPHIR_INIT_NVAR(&command);
		ZVAL_STRING(&command, "reserve");
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &command);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	zephir_array_fetch_long(&_1, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 469 TSRMLS_CC);
	_2 = !ZEPHIR_IS_STRING(&_1, "RESERVED");
	if (!(_2)) {
		_2 = !(zephir_array_isset_long(&response, 2));
	}
	if (_2) {
		RETURN_MM_BOOL(0);
	}
	object_init_ex(return_value, beanspeak_job_ce);
	zephir_array_fetch_long(&_3, &response, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 473 TSRMLS_CC);
	zephir_array_fetch_long(&_5, &response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 473 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "read", NULL, 0, &_5);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_6, "unserialize", NULL, 7, &_4);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 8, this_ptr, &_3, &_6);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Reserves/locks a ready job from the specified tube.
 *
 * <code>
 * $job = $queue->reserve();
 * </code>
 *
 * @throws Exception
 */
PHP_METHOD(Beanspeak_Client, reserveFromTube) {

	int timeout, ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, *timeout_param = NULL, _0;
	zval tube;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&tube);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &tube_param, &timeout_param);

	zephir_get_strval(&tube, tube_param);
	if (!timeout_param) {
		timeout = -1;
	} else {
		timeout = zephir_get_intval(timeout_param);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "watch", NULL, 0, &tube);
	zephir_check_call_status();
	ZVAL_LONG(&_0, timeout);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "reserve", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Removes the named tube from the watch list for the current connection.
 *
 * <code>
 * $count = $queue->ignore('tube-name);
 * </code>
 *
 * @throws Exception
 */
PHP_METHOD(Beanspeak_Client, ignore) {

	zend_bool _3$$3;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, response, watchedTubes, _0, _2$$3, _4$$3, _5$$5, _6$$5, _7$$5;
	zval tube, _1$$3;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&tube);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&watchedTubes);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tube_param);

	if (unlikely(Z_TYPE_P(tube_param) != IS_STRING && Z_TYPE_P(tube_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tube' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (likely(Z_TYPE_P(tube_param) == IS_STRING)) {
		zephir_get_strval(&tube, tube_param);
	} else {
		ZEPHIR_INIT_VAR(&tube);
		ZVAL_EMPTY_STRING(&tube);
	}


	zephir_read_property(&_0, this_ptr, SL("watchedTubes"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&watchedTubes, &_0);
	if (zephir_array_isset(&watchedTubes, &tube)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		ZEPHIR_CONCAT_SV(&_1$$3, "ignore ", &tube);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
		zephir_check_call_status();
		zephir_array_fetch_long(&_2$$3, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 511 TSRMLS_CC);
		if (ZEPHIR_IS_STRING(&_2$$3, "NOT_IGNORED")) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_exception_ce, "Cannot ignore last tube in watchlist.", "beanspeak/client.zep", 512);
			return;
		}
		_3$$3 = !(zephir_array_isset_long(&response, 1));
		if (!(_3$$3)) {
			zephir_array_fetch_long(&_4$$3, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 515 TSRMLS_CC);
			_3$$3 = !ZEPHIR_IS_STRING(&_4$$3, "WATCHING");
		}
		if (_3$$3) {
			ZEPHIR_INIT_VAR(&_5$$5);
			object_init_ex(&_5$$5, beanspeak_exception_ce);
			ZEPHIR_INIT_VAR(&_6$$5);
			zephir_fast_join_str(&_6$$5, SL(" "), &response TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_7$$5);
			ZEPHIR_CONCAT_SV(&_7$$5, "Unhandled response: ", &_6$$5);
			ZEPHIR_CALL_METHOD(NULL, &_5$$5, "__construct", NULL, 3, &_7$$5);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_5$$5, "beanspeak/client.zep", 516 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_array_unset(&watchedTubes, &tube, PH_SEPARATE);
		zephir_update_property_zval(this_ptr, SL("watchedTubes"), &watchedTubes);
	}
	RETURN_THIS();

}

/**
 * Gives statistical information about the system as a whole.
 *
 * <code>
 * $queue->stats();
 * </code>
 */
PHP_METHOD(Beanspeak_Client, stats) {

	zval response, _0, _1, _2;
	int ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "stats");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readyaml", NULL, 9);
	zephir_check_call_status();
	zephir_array_fetch_long(&_1, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 540 TSRMLS_CC);
	if (!ZEPHIR_IS_STRING(&_1, "OK")) {
		RETURN_MM_BOOL(0);
	}
	zephir_array_fetch_long(&_2, &response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 544 TSRMLS_CC);
	RETURN_CTOR(_2);

}

/**
 * Gives statistical information about the specified tube if it exists.
 *
 * <code>
 * $stats = $queue->statsTube('process-bitcoin');
 * </code>
 */
PHP_METHOD(Beanspeak_Client, statsTube) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, response, _1, _2;
	zval tube, _0;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&tube);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tube_param);

	if (unlikely(Z_TYPE_P(tube_param) != IS_STRING && Z_TYPE_P(tube_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tube' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (likely(Z_TYPE_P(tube_param) == IS_STRING)) {
		zephir_get_strval(&tube, tube_param);
	} else {
		ZEPHIR_INIT_VAR(&tube);
		ZVAL_EMPTY_STRING(&tube);
	}


	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_CONCAT_SV(&_0, "stats-tube ", &tube);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readyaml", NULL, 9);
	zephir_check_call_status();
	zephir_array_fetch_long(&_1, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 561 TSRMLS_CC);
	if (!ZEPHIR_IS_STRING(&_1, "OK")) {
		RETURN_MM_BOOL(0);
	}
	zephir_array_fetch_long(&_2, &response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 565 TSRMLS_CC);
	RETURN_CTOR(_2);

}

/**
 * Returns a list of all existing tubes.
 *
 * <code>
 * $tubes = $queue->listTubes();
 * </code>
 */
PHP_METHOD(Beanspeak_Client, listTubes) {

	zval response, _0, _1, _2;
	int ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "list-tubes");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readyaml", NULL, 9);
	zephir_check_call_status();
	zephir_array_fetch_long(&_1, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 582 TSRMLS_CC);
	if (!ZEPHIR_IS_STRING(&_1, "OK")) {
		RETURN_MM_BOOL(0);
	}
	zephir_array_fetch_long(&_2, &response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 586 TSRMLS_CC);
	RETURN_CTOR(_2);

}

/**
 * Returns the tube currently being used by the client.
 *
 * <code>
 * $tube = $queue->listTubeUsed(); // local cache
 * $tube = $queue->listTubeUsed(); // ask server
 * </code>
 *
 * @throws Exception
 */
PHP_METHOD(Beanspeak_Client, listTubeUsed) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *ask_param = NULL, response, _0, _2, _5, _6, _3$$4, _4$$4;
	zend_bool ask, _1;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &ask_param);

	if (!ask_param) {
		ask = 0;
	} else {
		ask = zephir_get_boolval(ask_param);
	}


	if (!(ask)) {
		RETURN_MM_MEMBER(this_ptr, "usedTube");
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "list-tube-used");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_1 = zephir_array_isset_long(&response, 1);
	if (_1) {
		zephir_array_fetch_long(&_2, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 611 TSRMLS_CC);
		_1 = ZEPHIR_IS_STRING(&_2, "USING");
	}
	if (_1) {
		zephir_array_fetch_long(&_3$$4, &response, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 612 TSRMLS_CC);
		zephir_update_property_zval(this_ptr, SL("usedTube"), &_3$$4);
		zephir_array_fetch_long(&_4$$4, &response, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 613 TSRMLS_CC);
		RETURN_CTOR(_4$$4);
	}
	ZEPHIR_INIT_NVAR(&_0);
	object_init_ex(&_0, beanspeak_exception_ce);
	ZEPHIR_INIT_VAR(&_5);
	zephir_fast_join_str(&_5, SL(" "), &response TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CONCAT_SV(&_6, "Unhandled response form beanstalkd server: ", &_5);
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 3, &_6);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_0, "beanspeak/client.zep", 616 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Returns a list tubes currently being watched by the client.
 *
 * <code>
 * $tubes = $queue->listTubesWatched(); // local cache
 * $tubes = $queue->listTubesWatched(true); // ask server
 * </code>
 *
 * @throws Exception
 */
PHP_METHOD(Beanspeak_Client, listTubesWatched) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *ask_param = NULL, __$true, response, _1, _2, _6, _7, _0$$3, _3$$4, _4$$4, _5$$4;
	zend_bool ask;
	ZEPHIR_INIT_THIS();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &ask_param);

	if (!ask_param) {
		ask = 0;
	} else {
		ask = zephir_get_boolval(ask_param);
	}


	if (!(ask)) {
		zephir_read_property(&_0$$3, this_ptr, SL("watchedTubes"), PH_NOISY_CC | PH_READONLY);
		zephir_array_keys(return_value, &_0$$3 TSRMLS_CC);
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "list-tubes-watched");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readyaml", NULL, 9);
	zephir_check_call_status();
	zephir_array_fetch_long(&_2, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 640 TSRMLS_CC);
	if (!ZEPHIR_IS_STRING(&_2, "OK")) {
		ZEPHIR_INIT_VAR(&_3$$4);
		object_init_ex(&_3$$4, beanspeak_exception_ce);
		ZEPHIR_INIT_VAR(&_4$$4);
		zephir_fast_join_str(&_4$$4, SL(" "), &response TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_5$$4);
		ZEPHIR_CONCAT_SV(&_5$$4, "Unhandled response form beanstalkd server: ", &_4$$4);
		ZEPHIR_CALL_METHOD(NULL, &_3$$4, "__construct", NULL, 3, &_5$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$4, "beanspeak/client.zep", 641 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_array_fetch_long(&_6, &response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 644 TSRMLS_CC);
	ZEPHIR_CALL_FUNCTION(&_7, "array_fill_keys", NULL, 10, &_6, &__$true);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("watchedTubes"), &_7);
	RETURN_MM_MEMBER(this_ptr, "watchedTubes");

}

/**
 * Can delay any new job being reserved for a given time.
 *
 * <code>
 * $queue->pauseTube('process-video', 60 * 60);
 * </code>
 */
PHP_METHOD(Beanspeak_Client, pauseTube) {

	zend_bool _2;
	int delay, ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, *delay_param = NULL, response, _0, _3;
	zval tube, _1;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&tube);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &tube_param, &delay_param);

	if (unlikely(Z_TYPE_P(tube_param) != IS_STRING && Z_TYPE_P(tube_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tube' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (likely(Z_TYPE_P(tube_param) == IS_STRING)) {
		zephir_get_strval(&tube, tube_param);
	} else {
		ZEPHIR_INIT_VAR(&tube);
		ZVAL_EMPTY_STRING(&tube);
	}
	delay = zephir_get_intval(delay_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, delay);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SVSV(&_1, "pause-tube ", &tube, " ", &_0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_2 = !(zephir_array_isset_long(&response, 0));
	if (!(_2)) {
		zephir_array_fetch_long(&_3, &response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 663 TSRMLS_CC);
		_2 = !ZEPHIR_IS_STRING(&_3, "PAUSED");
	}
	if (_2) {
		RETURN_MM_BOOL(0);
	}
	RETURN_MM_BOOL(1);

}

/**
 * Resume the tube.
 *
 * <code>
 * $queue->resumeTube('process-video');
 * </code>
 */
PHP_METHOD(Beanspeak_Client, resumeTube) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, _0;
	zval tube;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&tube);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tube_param);

	if (unlikely(Z_TYPE_P(tube_param) != IS_STRING && Z_TYPE_P(tube_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tube' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (likely(Z_TYPE_P(tube_param) == IS_STRING)) {
		zephir_get_strval(&tube, tube_param);
	} else {
		ZEPHIR_INIT_VAR(&tube);
		ZVAL_EMPTY_STRING(&tube);
	}


	ZVAL_LONG(&_0, 0);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "pausetube", NULL, 0, &tube, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Simply closes the connection.
 *
 * <code>
 * $queue->quit();
 * </code>
 */
PHP_METHOD(Beanspeak_Client, quit) {

	zval _0, _1;
	int ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "quit");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "disconnect", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&_1);
	zephir_read_property(&_1, this_ptr, SL("socket"), PH_NOISY_CC);
	RETURN_MM_BOOL(Z_TYPE_P(&_1) != IS_RESOURCE);

}

/**
 * Writes data to the socket.
 * Performs a connection if none is available.
 * @throws Exception
 */
PHP_METHOD(Beanspeak_Client, write) {

	zend_bool _5$$5;
	zephir_fcall_cache_entry *_1 = NULL, *_8 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, step = 0;
	zval *data_param = NULL, socket, retries, written, length, _0, _3, _4, _2$$3, _9$$5, _10$$5, _6$$6, _7$$6;
	zval data;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&socket);
	ZVAL_UNDEF(&retries);
	ZVAL_UNDEF(&written);
	ZVAL_UNDEF(&length);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &data_param);

	zephir_get_strval(&data, data_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isconnected", &_1, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "connect", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "isconnected", &_1, 0);
		zephir_check_call_status();
		if (!(zephir_is_true(&_2$$3))) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_exception_ce, "Unable to establish connection with beanstalkd server.", "beanspeak/client.zep", 710);
			return;
		}
	}
	zephir_read_property(&_3, this_ptr, SL("options"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_OBS_VAR(&retries);
	zephir_array_fetch_string(&retries, &_3, SL("wretries"), PH_NOISY, "beanspeak/client.zep", 714 TSRMLS_CC);
	zephir_read_property(&_4, this_ptr, SL("socket"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&socket, &_4);
	zephir_concat_self_str(&data, "\r\n", sizeof("\r\n")-1 TSRMLS_CC);
	step = 0;
	ZEPHIR_INIT_VAR(&written);
	ZVAL_LONG(&written, 0);
	ZEPHIR_INIT_VAR(&length);
	ZVAL_LONG(&length, zephir_fast_strlen_ev(&data));
	while (1) {
		if (!(ZEPHIR_LT(&written, &length))) {
			break;
		}
		step++;
		_5$$5 = ZEPHIR_LE_LONG(&retries, step);
		if (_5$$5) {
			_5$$5 = !zephir_is_true(&written);
		}
		if (_5$$5) {
			ZEPHIR_INIT_NVAR(&_6$$6);
			object_init_ex(&_6$$6, beanspeak_exception_ce);
			ZEPHIR_INIT_LNVAR(_7$$6);
			ZEPHIR_CONCAT_SVS(&_7$$6, "Failed to write data to socket after ", &retries, " tries.");
			ZEPHIR_CALL_METHOD(NULL, &_6$$6, "__construct", &_8, 3, &_7$$6);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_6$$6, "beanspeak/client.zep", 726 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_NVAR(&_9$$5);
		ZEPHIR_INIT_NVAR(&_10$$5);
		zephir_substr(&_10$$5, &data, zephir_get_intval(&written), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		zephir_fwrite(&_9$$5, &socket, &_10$$5 TSRMLS_CC);
		ZEPHIR_ADD_ASSIGN(&written, &_9$$5);
	}
	RETURN_CCTOR(written);

}

/**
 * Reads a packet from the socket.
 * Performs a connection if none is available.
 * @throws Exception
 */
PHP_METHOD(Beanspeak_Client, read) {

	zval errors;
	zephir_fcall_cache_entry *_1 = NULL, *_5 = NULL;
	zval *length_param = NULL, socket, data, meta, _0, _3, _2$$3, _4$$5, _6$$5, _7$$5, _8$$5, _9$$9, _10$$9, _11$$10, _12$$10;
	int length, ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&socket);
	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&meta);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$9);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_11$$10);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&errors);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &length_param);

	if (!length_param) {
		length = 0;
	} else {
		length = zephir_get_intval(length_param);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isconnected", &_1, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "connect", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "isconnected", &_1, 0);
		zephir_check_call_status();
		if (!(zephir_is_true(&_2$$3))) {
			RETURN_MM_BOOL(0);
		}
	}
	zephir_read_property(&_3, this_ptr, SL("socket"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&socket, &_3);
	if (length) {
		if (zephir_feof(&socket TSRMLS_CC)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_exception_ce, "Failed to read data from socket (EOF).", "beanspeak/client.zep", 756);
			return;
		}
		ZVAL_LONG(&_4$$5, (length + 2));
		ZEPHIR_CALL_FUNCTION(&data, "stream_get_line", &_5, 11, &socket, &_4$$5);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&meta, "stream_get_meta_data", NULL, 12, &socket);
		zephir_check_call_status();
		zephir_array_fetch_string(&_6$$5, &meta, SL("timed_out"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 762 TSRMLS_CC);
		if (zephir_is_true(&_6$$5)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_exception_ce, "Connection timed out upon attempt to read data from socket.", "beanspeak/client.zep", 763);
			return;
		}
		if (ZEPHIR_IS_FALSE_IDENTICAL(&data)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_exception_ce, "Failed to read data from socket.", "beanspeak/client.zep", 767);
			return;
		}
		ZEPHIR_INIT_VAR(&_7$$5);
		ZEPHIR_INIT_VAR(&_8$$5);
		ZVAL_STRING(&_8$$5, "\r\n");
		zephir_fast_trim(&_7$$5, &data, &_8$$5, ZEPHIR_TRIM_RIGHT TSRMLS_CC);
		ZEPHIR_CPY_WRT(&data, &_7$$5);
	} else {
		ZVAL_LONG(&_9$$9, 16384);
		ZEPHIR_INIT_VAR(&_10$$9);
		ZVAL_STRING(&_10$$9, "\r\n");
		ZEPHIR_CALL_FUNCTION(&data, "stream_get_line", &_5, 11, &socket, &_9$$9, &_10$$9);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&errors);
	zephir_create_array(&errors, 4, 0 TSRMLS_CC);
	add_assoc_stringl_ex(&errors, SL("UNKNOWN_COMMAND"), SL("Unnown command."));
	add_assoc_stringl_ex(&errors, SL("JOB_TOO_BIG"), SL("Job data exceeds server-enforced limit."));
	add_assoc_stringl_ex(&errors, SL("BAD_FORMAT"), SL("Bad command format."));
	add_assoc_stringl_ex(&errors, SL("OUT_OF_MEMORY"), SL("Out of memory."));
	if (zephir_array_isset(&errors, &data)) {
		ZEPHIR_INIT_VAR(&_11$$10);
		object_init_ex(&_11$$10, beanspeak_exception_ce);
		zephir_array_fetch(&_12$$10, &errors, &data, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 783 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, &_11$$10, "__construct", NULL, 3, &_12$$10);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_11$$10, "beanspeak/client.zep", 783 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CCTOR(data);

}

/**
 * Fetch a YAML payload from the Beanstalkd server.
 */
PHP_METHOD(Beanspeak_Client, readYaml) {

	zval response, status, data, bytes;
	int ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&status);
	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&bytes);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&data);
	array_init(&data);
	ZEPHIR_INIT_VAR(&bytes);
	ZVAL_LONG(&bytes, 0);
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	if (zephir_array_isset_long(&response, 0)) {
		ZEPHIR_OBS_VAR(&status);
		zephir_array_fetch_long(&status, &response, 0, PH_NOISY, "beanspeak/client.zep", 799 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(&status);
		ZVAL_STRING(&status, "UNKNOWN");
	}
	if (zephir_array_isset_long(&response, 1)) {
		ZEPHIR_OBS_NVAR(&bytes);
		zephir_array_fetch_long(&bytes, &response, 1, PH_NOISY, "beanspeak/client.zep", 805 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&data, this_ptr, "yamlparse", NULL, 13);
		zephir_check_call_status();
	}
	zephir_create_array(return_value, 3, 0 TSRMLS_CC);
	zephir_array_fast_append(return_value, &status);
	zephir_array_fast_append(return_value, &bytes);
	zephir_array_fast_append(return_value, &data);
	RETURN_MM();

}

/**
 * Reads the latest status from the Beanstalkd server.
 */
PHP_METHOD(Beanspeak_Client, readStatus) {

	zval status;
	int ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&status);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&status, this_ptr, "read", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(&status)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_fast_explode_str(return_value, SL(" "), &status, LONG_MAX TSRMLS_CC);
	RETURN_MM();

}

PHP_METHOD(Beanspeak_Client, yamlParse) {

	double _20$$14;
	zend_string *_10;
	zend_ulong _9;
	zend_bool _0, _3, _5;
	zval data, lines, key, value, values, response, _1, _2, _4, *_8, _6$$6, _7$$6, _11$$7, _12$$7, _13$$8, _14$$8, _15$$10, _16$$10, _18$$11, _19$$11;
	zephir_fcall_cache_entry *_17 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, tmp = 0;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&lines);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$8);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_18$$11);
	ZVAL_UNDEF(&_19$$11);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&response);
	array_init(&response);
	ZEPHIR_CALL_METHOD(&data, this_ptr, "read", NULL, 0);
	zephir_check_call_status();
	_0 = Z_TYPE_P(&data) != IS_STRING;
	if (!(_0)) {
		_0 = ZEPHIR_IS_EMPTY(&data);
	}
	if (_0) {
		array_init(return_value);
		RETURN_MM();
	}
	if ((zephir_function_exists_ex(SL("yaml_parse") TSRMLS_CC) == SUCCESS)) {
		ZEPHIR_CALL_FUNCTION(&response, "yaml_parse", NULL, 14, &data);
		zephir_check_call_status();
		RETURN_CCTOR(response);
	}
	ZEPHIR_INIT_VAR(&_1);
	zephir_fast_trim(&_1, &data, NULL , ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	ZEPHIR_CPY_WRT(&data, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_fast_trim(&_1, &data, NULL , ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "#[\r\n]+#");
	ZEPHIR_CALL_FUNCTION(&lines, "preg_split", NULL, 15, &_2, &_1);
	zephir_check_call_status();
	_3 = zephir_array_isset_long(&lines, 0);
	if (_3) {
		zephir_array_fetch_long(&_4, &lines, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 849 TSRMLS_CC);
		_3 = ZEPHIR_IS_STRING(&_4, "---");
	}
	if (_3) {
		ZEPHIR_MAKE_REF(&lines);
		ZEPHIR_CALL_FUNCTION(NULL, "array_shift", NULL, 16, &lines);
		ZEPHIR_UNREF(&lines);
		zephir_check_call_status();
	}
	_5 = Z_TYPE_P(&lines) != IS_ARRAY;
	if (!(_5)) {
		_5 = ZEPHIR_IS_EMPTY(&lines);
	}
	if (_5) {
		ZEPHIR_INIT_VAR(&_6$$6);
		ZVAL_STRING(&_6$$6, "YAML parse error.");
		ZVAL_LONG(&_7$$6, 512);
		ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 17, &_6$$6, &_7$$6);
		zephir_check_call_status();
		array_init(return_value);
		RETURN_MM();
	}
	zephir_is_iterable(&lines, 0, "beanspeak/client.zep", 885);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&lines), _9, _10, _8)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_10 != NULL) { 
			ZVAL_STR_COPY(&key, _10);
		} else {
			ZVAL_LONG(&key, _9);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _8);
		ZEPHIR_INIT_NVAR(&_11$$7);
		ZVAL_STRING(&_11$$7, ":");
		ZEPHIR_INIT_NVAR(&_12$$7);
		zephir_fast_strpos(&_12$$7, &value, &_11$$7, 0 );
		if (zephir_start_with_str(&value, SL("-"))) {
			ZEPHIR_INIT_NVAR(&_13$$8);
			ZEPHIR_INIT_NVAR(&_14$$8);
			ZVAL_STRING(&_14$$8, "- ");
			zephir_fast_trim(&_13$$8, &value, &_14$$8, ZEPHIR_TRIM_LEFT TSRMLS_CC);
			ZEPHIR_CPY_WRT(&value, &_13$$8);
		} else if (!ZEPHIR_IS_FALSE_IDENTICAL(&_12$$7)) {
			ZEPHIR_INIT_NVAR(&values);
			zephir_fast_explode_str(&values, SL(":"), &value, LONG_MAX TSRMLS_CC);
			if (!(zephir_array_isset_long(&values, 1))) {
				ZEPHIR_INIT_LNVAR(_15$$10);
				ZEPHIR_CONCAT_SVS(&_15$$10, "YAML parse error for line: \"", &value, "\"");
				ZVAL_LONG(&_16$$10, 512);
				ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", &_17, 17, &_15$$10, &_16$$10);
				zephir_check_call_status();
			} else {
				ZEPHIR_OBS_NVAR(&key);
				zephir_array_fetch_long(&key, &values, 0, PH_NOISY, "beanspeak/client.zep", 867 TSRMLS_CC);
				zephir_array_fetch_long(&_18$$11, &values, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 868 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&_19$$11);
				ZVAL_STRING(&_19$$11, " ");
				ZEPHIR_INIT_NVAR(&value);
				zephir_fast_trim(&value, &_18$$11, &_19$$11, ZEPHIR_TRIM_LEFT TSRMLS_CC);
			}
		}
		if (zephir_is_numeric(&value)) {
			tmp = zephir_get_intval(&value);
			if (ZEPHIR_IS_LONG(&value, tmp)) {
				ZEPHIR_INIT_NVAR(&value);
				ZVAL_LONG(&value, tmp);
			} else {
				_20$$14 = zephir_get_doubleval(&value);
				ZEPHIR_INIT_NVAR(&value);
				ZVAL_DOUBLE(&value, _20$$14);
			}
		}
		zephir_array_update_zval(&response, &key, &value, PH_COPY | PH_SEPARATE);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	RETURN_CCTOR(response);

}

zend_object *zephir_init_properties_Beanspeak_Client(zend_class_entry *class_type TSRMLS_DC) {

		zval _1$$3;
	zval __$true, _0, _2, _3$$4;
		ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("watchedTubes"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			zephir_create_array(&_1$$3, 1, 0 TSRMLS_CC);
			zephir_array_update_string(&_1$$3, SL("default"), &__$true, PH_COPY | PH_SEPARATE);
			zephir_update_property_zval(this_ptr, SL("watchedTubes"), &_1$$3);
		}
		zephir_read_property(&_2, this_ptr, SL("options"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval(this_ptr, SL("options"), &_3$$4);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

