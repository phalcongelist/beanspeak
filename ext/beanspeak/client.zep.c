
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
#include "kernel/file.h"
#include "kernel/string.h"
#include "kernel/concat.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/hash.h"


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

	zend_declare_property_null(beanspeak_client_ce, SL("socket"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(beanspeak_client_ce, SL("options"), ZEND_ACC_PROTECTED TSRMLS_CC);

	beanspeak_client_ce->create_object = zephir_init_properties_Beanspeak_Client;
	return SUCCESS;

}

/**
 * Beanspeak\Client constructor
 */
PHP_METHOD(Beanspeak_Client, __construct) {

	zval *options_param = NULL, *_0$$4;
	zval *options = NULL, *defaults;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &options_param);

	if (!options_param) {
		ZEPHIR_INIT_VAR(options);
		array_init(options);
	} else {
		zephir_get_arrval(options, options_param);
	}


	ZEPHIR_INIT_VAR(defaults);
	zephir_create_array(defaults, 5, 0 TSRMLS_CC);
	add_assoc_stringl_ex(defaults, SS("host"), SL("127.0.0.1"), 1);
	add_assoc_long_ex(defaults, SS("port"), 11300);
	zephir_array_update_string(&defaults, SL("persistent"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
	add_assoc_long_ex(defaults, SS("timeout"), 60);
	add_assoc_long_ex(defaults, SS("wretries"), 8);
	if (1 != 1) {
		zephir_update_property_this(this_ptr, SL("options"), defaults TSRMLS_CC);
	} else {
		ZEPHIR_INIT_VAR(_0$$4);
		zephir_add_function(_0$$4, options, defaults);
		zephir_update_property_this(this_ptr, SL("options"), _0$$4 TSRMLS_CC);
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
 * @throws \Beanspeak\Exception
 */
PHP_METHOD(Beanspeak_Client, connect) {

	zval *e = NULL, *options = NULL, *socket = NULL, *_0 = NULL, *_1, _17, *_2$$4, *_3$$5, *_4$$5, *_5$$5, *_6$$5, *_7$$5, *_8$$6, *_9$$6, *_10$$6, *_11$$6, *_12$$6, *_13$$7, *_14$$7, *_15$$8, *_16$$8 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isconnected", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(_0)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "disconnect", NULL, 0);
		zephir_check_call_status();
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(options, _1);

	/* try_start_1: */

		zephir_array_fetch_string(&_2$$4, options, SL("persistent"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 87 TSRMLS_CC);
		if (zephir_is_true(_2$$4)) {
			zephir_array_fetch_string(&_3$$5, options, SL("host"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 88 TSRMLS_CC);
			zephir_array_fetch_string(&_4$$5, options, SL("port"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 88 TSRMLS_CC);
			zephir_array_fetch_string(&_5$$5, options, SL("timeout"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 88 TSRMLS_CC);
			ZEPHIR_INIT_VAR(_6$$5);
			ZVAL_NULL(_6$$5);
			ZEPHIR_INIT_VAR(_7$$5);
			ZVAL_NULL(_7$$5);
			ZEPHIR_MAKE_REF(_6$$5);
			ZEPHIR_CALL_FUNCTION(&socket, "pfsockopen", NULL, 1, _3$$5, _4$$5, _6$$5, _7$$5, _5$$5);
			ZEPHIR_UNREF(_6$$5);
			zephir_check_call_status_or_jump(try_end_1);
		} else {
			zephir_array_fetch_string(&_8$$6, options, SL("host"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 90 TSRMLS_CC);
			zephir_array_fetch_string(&_9$$6, options, SL("port"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 90 TSRMLS_CC);
			zephir_array_fetch_string(&_10$$6, options, SL("timeout"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 90 TSRMLS_CC);
			ZEPHIR_INIT_VAR(_11$$6);
			ZVAL_NULL(_11$$6);
			ZEPHIR_INIT_VAR(_12$$6);
			ZVAL_NULL(_12$$6);
			ZEPHIR_MAKE_REF(_11$$6);
			ZEPHIR_CALL_FUNCTION(&socket, "fsockopen", NULL, 2, _8$$6, _9$$6, _11$$6, _12$$6, _10$$6);
			ZEPHIR_UNREF(_11$$6);
			zephir_check_call_status_or_jump(try_end_1);
		}
		if (Z_TYPE_P(socket) != IS_RESOURCE) {
			ZEPHIR_INIT_VAR(_13$$7);
			object_init_ex(_13$$7, beanspeak_exception_ce);
			ZEPHIR_INIT_VAR(_14$$7);
			ZVAL_STRING(_14$$7, "Can't connect to Beanstalk server.", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_METHOD(NULL, _13$$7, "__construct", NULL, 3, _14$$7);
			zephir_check_temp_parameter(_14$$7);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_throw_exception_debug(_13$$7, "beanspeak/client.zep", 94 TSRMLS_CC);
			goto try_end_1;

		}

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_instance_of_ev(e, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_INIT_VAR(_15$$8);
			object_init_ex(_15$$8, beanspeak_exception_ce);
			ZEPHIR_CALL_METHOD(&_16$$8, e, "getmessage", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, _15$$8, "__construct", NULL, 3, _16$$8);
			zephir_check_call_status();
			zephir_throw_exception_debug(_15$$8, "beanspeak/client.zep", 97 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_SINIT_VAR(_17);
	ZVAL_LONG(&_17, -1);
	ZEPHIR_CALL_FUNCTION(NULL, "stream_set_timeout", NULL, 4, socket, &_17, ZEPHIR_GLOBAL(global_null));
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("socket"), socket TSRMLS_CC);
	RETURN_CCTOR(socket);

}

/**
 * Destructor, disconnects from the server.
 */
PHP_METHOD(Beanspeak_Client, __destruct) {

	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "disconnect", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Closes the connection to the Beanstalk server.
 *
 * Will throw an exception if closing the connection fails, to allow
 * handling the then undefined state.
 *
 * @throws \Beanspeak\Exception
 */
PHP_METHOD(Beanspeak_Client, disconnect) {

	zval *socket = NULL, *status = NULL, *_0 = NULL, *_1;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isconnected", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("socket"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(socket, _1);
	ZEPHIR_INIT_VAR(status);
	ZVAL_BOOL(status, zephir_fclose(socket TSRMLS_CC));
	if (!(zephir_is_true(status))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_exception_ce, "Failed to close connection.", "beanspeak/client.zep", 136);
		return;
	}
	zephir_update_property_this(this_ptr, SL("socket"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	RETURN_MM_BOOL(1);

}

/**
 * Whether the connection is established or not.
 */
PHP_METHOD(Beanspeak_Client, isConnected) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("socket"), PH_NOISY_CC);
	RETURN_MM_BOOL(Z_TYPE_P(_0) == IS_RESOURCE);

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
 * $put = $ueue->pit($task, 999, 60 * 60, 3600);
 * </code>
 */
PHP_METHOD(Beanspeak_Client, put) {

	zend_bool _5$$4;
	int priority, delay, ttr, ZEPHIR_LAST_CALL_STATUS;
	zval *data, *priority_param = NULL, *delay_param = NULL, *ttr_param = NULL, *status = NULL, *response = NULL, *serialized = NULL, *length = NULL, *_0 = NULL, _1, _2, _3, *_4, *_6$$5;

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
	ZEPHIR_INIT_VAR(length);
	ZVAL_LONG(length, zephir_fast_strlen_ev(serialized));
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_LONG(&_1, priority);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_LONG(&_2, delay);
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_LONG(&_3, ttr);
	ZEPHIR_INIT_VAR(_4);
	ZEPHIR_CONCAT_SVSVSVSVSV(_4, "put ", &_1, " ", &_2, " ", &_3, " ", length, "\r\n", serialized);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _4);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	if (zephir_array_isset_long(response, 1)) {
		zephir_array_fetch_long(&status, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 180 TSRMLS_CC);
		_5$$4 = ZEPHIR_IS_STRING(status, "INSERTED");
		if (!(_5$$4)) {
			_5$$4 = ZEPHIR_IS_STRING(status, "BURIED");
		}
		if (_5$$4) {
			ZEPHIR_OBS_VAR(_6$$5);
			zephir_array_fetch_long(&_6$$5, response, 1, PH_NOISY, "beanspeak/client.zep", 183 TSRMLS_CC);
			RETURN_MM_LONG(zephir_get_intval(_6$$5));
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
	zval *tube_param = NULL, *data, *priority_param = NULL, *delay_param = NULL, *ttr_param = NULL, *response = NULL, *_0$$3, *_1$$3, *_2$$3;
	zval *tube = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 3, &tube_param, &data, &priority_param, &delay_param, &ttr_param);

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


	ZEPHIR_CALL_METHOD(&response, this_ptr, "usetube", NULL, 0, tube);
	zephir_check_call_status();
	if (Z_TYPE_P(response) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(_0$$3);
		ZVAL_LONG(_0$$3, priority);
		ZEPHIR_INIT_VAR(_1$$3);
		ZVAL_LONG(_1$$3, delay);
		ZEPHIR_INIT_VAR(_2$$3);
		ZVAL_LONG(_2$$3, ttr);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "put", NULL, 0, data, _0$$3, _1$$3, _2$$3);
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
 */
PHP_METHOD(Beanspeak_Client, useTube) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, *response = NULL, *status = NULL, *_0 = NULL;
	zval *tube = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tube_param);

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


	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_SV(_1, "use ", tube);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	if (zephir_array_isset_long(response, 1)) {
		zephir_array_fetch_long(&status, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 237 TSRMLS_CC);
		if (ZEPHIR_IS_STRING(status, "USING")) {
			RETURN_THIS();
		}
	}
	RETURN_MM_BOOL(0);

}

/**
 * Lets the client inspect a job in the system.
 *
 * <code>
 * $peekJob = $queue->peek($jobId);
 * </code>
 */
PHP_METHOD(Beanspeak_Client, peekJob) {

	zend_bool _3;
	zval *_2;
	zval *id_param = NULL, *response = NULL, *_0 = NULL, _1, *_4, *_5$$4, *_6$$4 = NULL, *_7$$4, *_8$$4 = NULL;
	int id, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &id_param);

	id = zephir_get_intval(id_param);


	ZEPHIR_SINIT_VAR(_1);
	ZVAL_LONG(&_1, id);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SV(_2, "peek ", &_1);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _2);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_3 = zephir_array_isset_long(response, 2);
	if (_3) {
		zephir_array_fetch_long(&_4, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 263 TSRMLS_CC);
		_3 = ZEPHIR_IS_STRING(_4, "FOUND");
	}
	if (_3) {
		object_init_ex(return_value, beanspeak_job_ce);
		zephir_array_fetch_long(&_5$$4, response, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 264 TSRMLS_CC);
		zephir_array_fetch_long(&_7$$4, response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 264 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_6$$4, this_ptr, "read", NULL, 0, _7$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_8$$4, "unserialize", NULL, 7, _6$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 8, this_ptr, _5$$4, _8$$4);
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

	zend_bool _2;
	zval *response = NULL, *_0 = NULL, *_1, *_3, *_4$$4, *_5$$4 = NULL, *_6$$4, *_7$$4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "peek-delayed", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_2 = zephir_array_isset_long(response, 2);
	if (_2) {
		zephir_array_fetch_long(&_3, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 286 TSRMLS_CC);
		_2 = ZEPHIR_IS_STRING(_3, "FOUND");
	}
	if (_2) {
		object_init_ex(return_value, beanspeak_job_ce);
		zephir_array_fetch_long(&_4$$4, response, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 287 TSRMLS_CC);
		zephir_array_fetch_long(&_6$$4, response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 287 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_5$$4, this_ptr, "read", NULL, 0, _6$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_7$$4, "unserialize", NULL, 7, _5$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 8, this_ptr, _4$$4, _7$$4);
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

	zend_bool _2;
	zval *response = NULL, *_0 = NULL, *_1, *_3, *_4$$4, *_5$$4 = NULL, *_6$$4, *_7$$4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "peek-buried", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_2 = zephir_array_isset_long(response, 2);
	if (_2) {
		zephir_array_fetch_long(&_3, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 309 TSRMLS_CC);
		_2 = ZEPHIR_IS_STRING(_3, "FOUND");
	}
	if (_2) {
		object_init_ex(return_value, beanspeak_job_ce);
		zephir_array_fetch_long(&_4$$4, response, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 310 TSRMLS_CC);
		zephir_array_fetch_long(&_6$$4, response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 310 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_5$$4, this_ptr, "read", NULL, 0, _6$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_7$$4, "unserialize", NULL, 7, _5$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 8, this_ptr, _4$$4, _7$$4);
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

	zend_bool _2;
	zval *response = NULL, *_0 = NULL, *_1, *_3, *_4$$4, *_5$$4 = NULL, *_6$$4, *_7$$4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "peek-ready", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_2 = zephir_array_isset_long(response, 2);
	if (_2) {
		zephir_array_fetch_long(&_3, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 332 TSRMLS_CC);
		_2 = ZEPHIR_IS_STRING(_3, "FOUND");
	}
	if (_2) {
		object_init_ex(return_value, beanspeak_job_ce);
		zephir_array_fetch_long(&_4$$4, response, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 333 TSRMLS_CC);
		zephir_array_fetch_long(&_6$$4, response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 333 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_5$$4, this_ptr, "read", NULL, 0, _6$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_7$$4, "unserialize", NULL, 7, _5$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 8, this_ptr, _4$$4, _7$$4);
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

	zend_bool _3;
	zval *_2;
	zval *bound_param = NULL, *response = NULL, *_0 = NULL, _1, *_4, *_5$$4;
	int bound, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &bound_param);

	bound = zephir_get_intval(bound_param);


	ZEPHIR_SINIT_VAR(_1);
	ZVAL_LONG(&_1, bound);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SV(_2, "kick ", &_1);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _2);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_3 = zephir_array_isset_long(response, 1);
	if (_3) {
		zephir_array_fetch_long(&_4, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 356 TSRMLS_CC);
		_3 = ZEPHIR_IS_STRING(_4, "KICKED");
	}
	if (_3) {
		ZEPHIR_OBS_VAR(_5$$4);
		zephir_array_fetch_long(&_5$$4, response, 1, PH_NOISY, "beanspeak/client.zep", 357 TSRMLS_CC);
		RETURN_MM_LONG(zephir_get_intval(_5$$4));
	}
	RETURN_MM_BOOL(0);

}

/**
 * Adds the named tube to the watch list for the current connection.
 *
 * <code>
 * $count = $queue->watch($tube);
 * </code>
 */
PHP_METHOD(Beanspeak_Client, watch) {

	zend_bool _2;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, *response = NULL, *_0 = NULL, *_3, *_4$$4;
	zval *tube = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tube_param);

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


	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_SV(_1, "watch ", tube);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_2 = zephir_array_isset_long(response, 1);
	if (_2) {
		zephir_array_fetch_long(&_3, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 379 TSRMLS_CC);
		_2 = ZEPHIR_IS_STRING(_3, "WATCHING");
	}
	if (_2) {
		ZEPHIR_OBS_VAR(_4$$4);
		zephir_array_fetch_long(&_4$$4, response, 1, PH_NOISY, "beanspeak/client.zep", 380 TSRMLS_CC);
		RETURN_MM_LONG(zephir_get_intval(_4$$4));
	}
	RETURN_MM_BOOL(0);

}

/**
 * Removes the named tube from the watch list for the current connection.
 *
 * <code>
 * $count = $queue->ignore('tube-name);
 * </code>
 */
PHP_METHOD(Beanspeak_Client, ignore) {

	zend_bool _2;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, *response = NULL, *_0 = NULL, *_3, *_4$$4;
	zval *tube = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tube_param);

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


	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_SV(_1, "ignore ", tube);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_2 = zephir_array_isset_long(response, 1);
	if (_2) {
		zephir_array_fetch_long(&_3, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 402 TSRMLS_CC);
		_2 = ZEPHIR_IS_STRING(_3, "WATCHING");
	}
	if (_2) {
		ZEPHIR_OBS_VAR(_4$$4);
		zephir_array_fetch_long(&_4$$4, response, 1, PH_NOISY, "beanspeak/client.zep", 403 TSRMLS_CC);
		RETURN_MM_LONG(zephir_get_intval(_4$$4));
	}
	RETURN_MM_BOOL(0);

}

/**
 * Gives statistical information about the system as a whole.
 *
 * <code>
 * $queue->stats();
 * </code>
 */
PHP_METHOD(Beanspeak_Client, stats) {

	zval *response = NULL, *_0 = NULL, *_1, *_2, *_3;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "stats", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readyaml", NULL, 9);
	zephir_check_call_status();
	zephir_array_fetch_long(&_2, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 425 TSRMLS_CC);
	if (!ZEPHIR_IS_STRING(_2, "OK")) {
		RETURN_MM_BOOL(0);
	}
	zephir_array_fetch_long(&_3, response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 429 TSRMLS_CC);
	RETURN_CTOR(_3);

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
	zval *tube_param = NULL, *response = NULL, *_0 = NULL, *_2, *_3;
	zval *tube = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tube_param);

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


	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_SV(_1, "stats-tube ", tube);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readyaml", NULL, 9);
	zephir_check_call_status();
	zephir_array_fetch_long(&_2, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 448 TSRMLS_CC);
	if (!ZEPHIR_IS_STRING(_2, "OK")) {
		RETURN_MM_BOOL(0);
	}
	zephir_array_fetch_long(&_3, response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 452 TSRMLS_CC);
	RETURN_CTOR(_3);

}

/**
 * Returns a list of all existing tubes.
 *
 * <code>
 * $tubes = $queue->listTubes();
 * </code>
 */
PHP_METHOD(Beanspeak_Client, listTubes) {

	zval *response = NULL, *_0 = NULL, *_1, *_2, *_3;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "list-tubes", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readyaml", NULL, 9);
	zephir_check_call_status();
	zephir_array_fetch_long(&_2, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 471 TSRMLS_CC);
	if (!ZEPHIR_IS_STRING(_2, "OK")) {
		RETURN_MM_BOOL(0);
	}
	zephir_array_fetch_long(&_3, response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 475 TSRMLS_CC);
	RETURN_CTOR(_3);

}

/**
 * Returns the tube currently being used by the client.
 *
 * <code>
 * $tube = $queue->listTubeUsed();
 * </code>
 */
PHP_METHOD(Beanspeak_Client, listTubeUsed) {

	zend_bool _2;
	zval *response = NULL, *_0 = NULL, *_1, *_3, *_4$$4;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "list-tube-used", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_2 = zephir_array_isset_long(response, 1);
	if (_2) {
		zephir_array_fetch_long(&_3, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 495 TSRMLS_CC);
		_2 = ZEPHIR_IS_STRING(_3, "USING");
	}
	if (_2) {
		zephir_array_fetch_long(&_4$$4, response, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 496 TSRMLS_CC);
		RETURN_CTOR(_4$$4);
	}
	RETURN_MM_BOOL(0);

}

/**
 * Returns a list tubes currently being watched by the client.
 *
 * <code>
 * $tubes = $queue->listTubesWatched();
 * </code>
 */
PHP_METHOD(Beanspeak_Client, listTubesWatched) {

	zval *response = NULL, *_0 = NULL, *_1, *_2, *_3;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "list-tubes-watched", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readyaml", NULL, 9);
	zephir_check_call_status();
	zephir_array_fetch_long(&_2, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 518 TSRMLS_CC);
	if (!ZEPHIR_IS_STRING(_2, "OK")) {
		RETURN_MM_BOOL(0);
	}
	zephir_array_fetch_long(&_3, response, 2, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 522 TSRMLS_CC);
	RETURN_CTOR(_3);

}

/**
 * Can delay any new job being reserved for a given time.
 *
 * <code>
 * $queue->pauseTube('process-video', 60 * 60);
 * </code>
 */
PHP_METHOD(Beanspeak_Client, pauseTube) {

	zend_bool _3;
	int delay, ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, *delay_param = NULL, *response = NULL, *_0 = NULL, _1, *_4;
	zval *tube = NULL, *_2;

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
	delay = zephir_get_intval(delay_param);


	ZEPHIR_SINIT_VAR(_1);
	ZVAL_LONG(&_1, delay);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SVSV(_2, "pause-tube ", tube, " ", &_1);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "write", NULL, 0, _2);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	_3 = !(zephir_array_isset_long(response, 0));
	if (!(_3)) {
		zephir_array_fetch_long(&_4, response, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 541 TSRMLS_CC);
		_3 = !ZEPHIR_IS_STRING(_4, "PAUSED");
	}
	if (_3) {
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
	zval *tube_param = NULL, *_0;
	zval *tube = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tube_param);

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


	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 0);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "pausetube", NULL, 0, tube, _0);
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

	zval *_0, *_1;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "quit", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "disconnect", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_1);
	zephir_read_property_this(&_1, this_ptr, SL("socket"), PH_NOISY_CC);
	RETURN_MM_BOOL(Z_TYPE_P(_1) != IS_RESOURCE);

}

/**
 * Writes data to the socket.
 * Performs a connection if none is available.
 * @throws \Beanspeak\Exception
 */
PHP_METHOD(Beanspeak_Client, write) {

	zend_bool _5$$5;
	zephir_fcall_cache_entry *_1 = NULL, *_8 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, step = 0;
	zval *data_param = NULL, *socket = NULL, *retries = NULL, *written = NULL, *length = NULL, *_0 = NULL, *_3, *_4, *_2$$3 = NULL, *_9$$5 = NULL, *_10$$5 = NULL, *_6$$6 = NULL, *_7$$6 = NULL;
	zval *data = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &data_param);

	zephir_get_strval(data, data_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isconnected", &_1, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "connect", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "isconnected", &_1, 0);
		zephir_check_call_status();
		if (!(zephir_is_true(_2$$3))) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_exception_ce, "Unable to establish connection with beanstalkd server.", "beanspeak/client.zep", 588);
			return;
		}
	}
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("options"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(retries);
	zephir_array_fetch_string(&retries, _3, SL("wretries"), PH_NOISY, "beanspeak/client.zep", 592 TSRMLS_CC);
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("socket"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(socket, _4);
	zephir_concat_self_str(&data, "\r\n", sizeof("\r\n")-1 TSRMLS_CC);
	step = 0;
	ZEPHIR_INIT_VAR(written);
	ZVAL_LONG(written, 0);
	ZEPHIR_INIT_VAR(length);
	ZVAL_LONG(length, zephir_fast_strlen_ev(data));
	while (1) {
		if (!(ZEPHIR_LT(written, length))) {
			break;
		}
		step++;
		_5$$5 = ZEPHIR_LE_LONG(retries, step);
		if (_5$$5) {
			_5$$5 = !zephir_is_true(written);
		}
		if (_5$$5) {
			ZEPHIR_INIT_NVAR(_6$$6);
			object_init_ex(_6$$6, beanspeak_exception_ce);
			ZEPHIR_INIT_LNVAR(_7$$6);
			ZEPHIR_CONCAT_SVS(_7$$6, "Failed to write data to socket after ", retries, " tries");
			ZEPHIR_CALL_METHOD(NULL, _6$$6, "__construct", &_8, 3, _7$$6);
			zephir_check_call_status();
			zephir_throw_exception_debug(_6$$6, "beanspeak/client.zep", 604 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_NVAR(_9$$5);
		ZEPHIR_INIT_NVAR(_10$$5);
		zephir_substr(_10$$5, data, zephir_get_intval(written), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		zephir_fwrite(_9$$5, socket, _10$$5 TSRMLS_CC);
		ZEPHIR_ADD_ASSIGN(written, _9$$5);
	}
	RETURN_CCTOR(written);

}

/**
 * Reads a packet from the socket.
 * Performs a connection if none is available.
 * @throws \Beanspeak\Exception
 */
PHP_METHOD(Beanspeak_Client, read) {

	zval *errors;
	zephir_fcall_cache_entry *_1 = NULL, *_5 = NULL;
	zval *length_param = NULL, *socket = NULL, *data = NULL, *meta = NULL, *_0 = NULL, *_3, *_2$$3 = NULL, _4$$5 = zval_used_for_init, *_6$$5, *_7$$5, _8$$9, _9$$9, *_10$$10, *_11$$10;
	int length, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &length_param);

	if (!length_param) {
		length = 0;
	} else {
		length = zephir_get_intval(length_param);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isconnected", &_1, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "connect", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "isconnected", &_1, 0);
		zephir_check_call_status();
		if (!(zephir_is_true(_2$$3))) {
			RETURN_MM_BOOL(0);
		}
	}
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("socket"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(socket, _3);
	if (length) {
		if (zephir_feof(socket TSRMLS_CC)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_exception_ce, "Failed to read data from socket (EOF).", "beanspeak/client.zep", 634);
			return;
		}
		ZEPHIR_SINIT_VAR(_4$$5);
		ZVAL_LONG(&_4$$5, (length + 2));
		ZEPHIR_CALL_FUNCTION(&data, "stream_get_line", &_5, 10, socket, &_4$$5);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&meta, "stream_get_meta_data", NULL, 11, socket);
		zephir_check_call_status();
		zephir_array_fetch_string(&_6$$5, meta, SL("timed_out"), PH_NOISY | PH_READONLY, "beanspeak/client.zep", 640 TSRMLS_CC);
		if (zephir_is_true(_6$$5)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_exception_ce, "Connection timed out upon attempt to read data from socket.", "beanspeak/client.zep", 641);
			return;
		}
		if (ZEPHIR_IS_FALSE_IDENTICAL(data)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_exception_ce, "Failed to read data from socket.", "beanspeak/client.zep", 645);
			return;
		}
		ZEPHIR_INIT_VAR(_7$$5);
		ZEPHIR_SINIT_NVAR(_4$$5);
		ZVAL_STRING(&_4$$5, "\r\n", 0);
		zephir_fast_trim(_7$$5, data, &_4$$5, ZEPHIR_TRIM_RIGHT TSRMLS_CC);
		ZEPHIR_CPY_WRT(data, _7$$5);
	} else {
		ZEPHIR_SINIT_VAR(_8$$9);
		ZVAL_LONG(&_8$$9, 16384);
		ZEPHIR_SINIT_VAR(_9$$9);
		ZVAL_STRING(&_9$$9, "\r\n", 0);
		ZEPHIR_CALL_FUNCTION(&data, "stream_get_line", &_5, 10, socket, &_8$$9, &_9$$9);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(errors);
	zephir_create_array(errors, 4, 0 TSRMLS_CC);
	add_assoc_stringl_ex(errors, SS("UNKNOWN_COMMAND"), SL("Unnown command."), 1);
	add_assoc_stringl_ex(errors, SS("JOB_TOO_BIG"), SL("Job data exceeds server-enforced limit."), 1);
	add_assoc_stringl_ex(errors, SS("BAD_FORMAT"), SL("Bad command format."), 1);
	add_assoc_stringl_ex(errors, SS("OUT_OF_MEMORY"), SL("Out of memory."), 1);
	if (zephir_array_isset(errors, data)) {
		ZEPHIR_INIT_VAR(_10$$10);
		object_init_ex(_10$$10, beanspeak_exception_ce);
		zephir_array_fetch(&_11$$10, errors, data, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 661 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, _10$$10, "__construct", NULL, 3, _11$$10);
		zephir_check_call_status();
		zephir_throw_exception_debug(_10$$10, "beanspeak/client.zep", 661 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CCTOR(data);

}

/**
 * Fetch a YAML payload from the Beanstalkd server.
 */
PHP_METHOD(Beanspeak_Client, readYaml) {

	zval *response = NULL, *status = NULL, *data = NULL, *bytes = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(data);
	array_init(data);
	ZEPHIR_INIT_VAR(bytes);
	ZVAL_LONG(bytes, 0);
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 6);
	zephir_check_call_status();
	if (zephir_array_isset_long(response, 0)) {
		ZEPHIR_OBS_VAR(status);
		zephir_array_fetch_long(&status, response, 0, PH_NOISY, "beanspeak/client.zep", 677 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(status);
		ZVAL_STRING(status, "UNKNOWN", 1);
	}
	if (zephir_array_isset_long(response, 1)) {
		ZEPHIR_OBS_NVAR(bytes);
		zephir_array_fetch_long(&bytes, response, 1, PH_NOISY, "beanspeak/client.zep", 683 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&data, this_ptr, "yamlparse", NULL, 12);
		zephir_check_call_status();
	}
	zephir_create_array(return_value, 3, 0 TSRMLS_CC);
	zephir_array_fast_append(return_value, status);
	zephir_array_fast_append(return_value, bytes);
	zephir_array_fast_append(return_value, data);
	RETURN_MM();

}

/**
 * Reads the latest status from the Beanstalkd server.
 */
PHP_METHOD(Beanspeak_Client, readStatus) {

	zval *status = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&status, this_ptr, "read", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(status)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_fast_explode_str(return_value, SL(" "), status, LONG_MAX TSRMLS_CC);
	RETURN_MM();

}

PHP_METHOD(Beanspeak_Client, yamlParse) {

	double _20$$14;
	HashTable *_9;
	HashPosition _8;
	zend_bool _0, _3, _5;
	zval *data = NULL, *lines = NULL, *key = NULL, *value = NULL, *values = NULL, *response = NULL, *_1 = NULL, _2, *_4, **_10, _6$$6, _7$$6, _11$$7 = zval_used_for_init, *_12$$7 = NULL, *_13$$8 = NULL, _14$$8 = zval_used_for_init, *_15$$10 = NULL, _16$$10 = zval_used_for_init, *_18$$11, _19$$11 = zval_used_for_init;
	zephir_fcall_cache_entry *_17 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, tmp = 0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(response);
	array_init(response);
	ZEPHIR_CALL_METHOD(&data, this_ptr, "read", NULL, 0);
	zephir_check_call_status();
	_0 = Z_TYPE_P(data) != IS_STRING;
	if (!(_0)) {
		_0 = ZEPHIR_IS_EMPTY(data);
	}
	if (_0) {
		array_init(return_value);
		RETURN_MM();
	}
	if ((zephir_function_exists_ex(SS("yaml_parse") TSRMLS_CC) == SUCCESS)) {
		ZEPHIR_CALL_FUNCTION(&response, "yaml_parse", NULL, 13, data);
		zephir_check_call_status();
		RETURN_CCTOR(response);
	}
	ZEPHIR_INIT_VAR(_1);
	zephir_fast_trim(_1, data, NULL , ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	ZEPHIR_CPY_WRT(data, _1);
	ZEPHIR_INIT_NVAR(_1);
	zephir_fast_trim(_1, data, NULL , ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_STRING(&_2, "#[\r\n]+#", 0);
	ZEPHIR_CALL_FUNCTION(&lines, "preg_split", NULL, 14, &_2, _1);
	zephir_check_call_status();
	_3 = zephir_array_isset_long(lines, 0);
	if (_3) {
		zephir_array_fetch_long(&_4, lines, 0, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 727 TSRMLS_CC);
		_3 = ZEPHIR_IS_STRING(_4, "---");
	}
	if (_3) {
		ZEPHIR_MAKE_REF(lines);
		ZEPHIR_CALL_FUNCTION(NULL, "array_shift", NULL, 15, lines);
		ZEPHIR_UNREF(lines);
		zephir_check_call_status();
	}
	_5 = Z_TYPE_P(lines) != IS_ARRAY;
	if (!(_5)) {
		_5 = ZEPHIR_IS_EMPTY(lines);
	}
	if (_5) {
		ZEPHIR_SINIT_VAR(_6$$6);
		ZVAL_STRING(&_6$$6, "YAML parse error.", 0);
		ZEPHIR_SINIT_VAR(_7$$6);
		ZVAL_LONG(&_7$$6, 512);
		ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 16, &_6$$6, &_7$$6);
		zephir_check_call_status();
		array_init(return_value);
		RETURN_MM();
	}
	zephir_is_iterable(lines, &_9, &_8, 0, 0, "beanspeak/client.zep", 763);
	for (
	  ; zephir_hash_get_current_data_ex(_9, (void**) &_10, &_8) == SUCCESS
	  ; zephir_hash_move_forward_ex(_9, &_8)
	) {
		ZEPHIR_GET_HMKEY(key, _9, _8);
		ZEPHIR_GET_HVALUE(value, _10);
		ZEPHIR_SINIT_NVAR(_11$$7);
		ZVAL_STRING(&_11$$7, ":", 0);
		ZEPHIR_INIT_NVAR(_12$$7);
		zephir_fast_strpos(_12$$7, value, &_11$$7, 0 );
		if (zephir_start_with_str(value, SL("-"))) {
			ZEPHIR_INIT_NVAR(_13$$8);
			ZEPHIR_SINIT_NVAR(_14$$8);
			ZVAL_STRING(&_14$$8, "- ", 0);
			zephir_fast_trim(_13$$8, value, &_14$$8, ZEPHIR_TRIM_LEFT TSRMLS_CC);
			ZEPHIR_CPY_WRT(value, _13$$8);
		} else if (!ZEPHIR_IS_FALSE_IDENTICAL(_12$$7)) {
			ZEPHIR_INIT_NVAR(values);
			zephir_fast_explode_str(values, SL(":"), value, LONG_MAX TSRMLS_CC);
			if (!(zephir_array_isset_long(values, 1))) {
				ZEPHIR_INIT_LNVAR(_15$$10);
				ZEPHIR_CONCAT_SVS(_15$$10, "YAML parse error for line: \"", value, "\"");
				ZEPHIR_SINIT_NVAR(_16$$10);
				ZVAL_LONG(&_16$$10, 512);
				ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", &_17, 16, _15$$10, &_16$$10);
				zephir_check_call_status();
			} else {
				ZEPHIR_OBS_NVAR(key);
				zephir_array_fetch_long(&key, values, 0, PH_NOISY, "beanspeak/client.zep", 745 TSRMLS_CC);
				zephir_array_fetch_long(&_18$$11, values, 1, PH_NOISY | PH_READONLY, "beanspeak/client.zep", 746 TSRMLS_CC);
				ZEPHIR_SINIT_NVAR(_19$$11);
				ZVAL_STRING(&_19$$11, " ", 0);
				ZEPHIR_INIT_NVAR(value);
				zephir_fast_trim(value, _18$$11, &_19$$11, ZEPHIR_TRIM_LEFT TSRMLS_CC);
			}
		}
		if (zephir_is_numeric(value)) {
			tmp = zephir_get_intval(value);
			if (ZEPHIR_IS_LONG(value, tmp)) {
				ZEPHIR_INIT_NVAR(value);
				ZVAL_LONG(value, tmp);
			} else {
				_20$$14 = zephir_get_doubleval(value);
				ZEPHIR_INIT_NVAR(value);
				ZVAL_DOUBLE(value, _20$$14);
			}
		}
		zephir_array_update_zval(&response, key, &value, PH_COPY | PH_SEPARATE);
	}
	RETURN_CCTOR(response);

}

static zend_object_value zephir_init_properties_Beanspeak_Client(zend_class_entry *class_type TSRMLS_DC) {

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

