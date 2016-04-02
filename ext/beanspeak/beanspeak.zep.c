
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"


/**
 * Beanspeak\Beanspeak
 *
 * Class to access the beanstalk queue service.
 *
 * <code>
 * use Beanspeak\Beanspeak;
 *
 * $queue = new Beanspeak([
 *     'host'       => '127.0.0.1',
 *     'port'       => 11300,
 *     'persistent' => true,
 * ]);
 * </code>
 *
 * @link https://github.com/kr/beanstalkd/
 */
ZEPHIR_INIT_CLASS(Beanspeak_Beanspeak) {

	ZEPHIR_REGISTER_CLASS(Beanspeak, Beanspeak, beanspeak, beanspeak, beanspeak_beanspeak_method_entry, 0);

	/**
	 * The internal Dispatcher.
	 * @var \Beanspeak\Dispatcher\DispatcherInterface
	 */
	zend_declare_property_null(beanspeak_beanspeak_ce, SL("dispatcher"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(beanspeak_beanspeak_ce TSRMLS_CC, 1, beanspeak_dispatcher_dispatcherawareinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Beanspeak constructor
 */
PHP_METHOD(Beanspeak_Beanspeak, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *dispatcher = NULL, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &dispatcher);

	if (!dispatcher) {
		ZEPHIR_CPY_WRT(dispatcher, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(dispatcher);
	}


	ZEPHIR_INIT_VAR(_0);
	if (!(zephir_is_true(dispatcher))) {
		ZEPHIR_INIT_NVAR(_0);
		object_init_ex(_0, beanspeak_dispatcher_ce);
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 3);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(_0, dispatcher);
	}
	ZEPHIR_CPY_WRT(dispatcher, _0);
	zephir_update_property_this(this_ptr, SL("dispatcher"), dispatcher TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Beanspeak, setDispatcher) {

	zval *dispatcher;

	zephir_fetch_params(0, 1, 0, &dispatcher);



	zephir_update_property_this(this_ptr, SL("dispatcher"), dispatcher TSRMLS_CC);
	RETURN_THISW();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Beanspeak, getDispatcher) {

	

	RETURN_MEMBER(this_ptr, "dispatcher");

}

/**
 * Inserts jobs into the queue.
 *
 * <code>
 * $queue->put(
 *     [
 *         'recipient' => 'user@mail.com',
 *         'subject'   => 'Welcome',
 *         'content'   => $content,
 *     ],
 *     [
 *         'priority' => 999,
 *         'delay'    => 60 * 60,
 *         'ttr'      => 3600,
 *     ],
 * );
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, put) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *options = NULL;
	zval *data, *options_param = NULL, *priority = NULL, *delay = NULL, *ttr = NULL, *serialized = NULL, *response = NULL, *_0, *_1, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &data, &options_param);

	if (!options_param) {
		ZEPHIR_INIT_VAR(options);
		array_init(options);
	} else {
		zephir_get_arrval(options, options_param);
	}


	ZEPHIR_OBS_VAR(priority);
	if (!(zephir_array_isset_string_fetch(&priority, options, SS("priority"), 0 TSRMLS_CC))) {
		ZEPHIR_INIT_NVAR(priority);
		ZVAL_LONG(priority, 100);
	}
	ZEPHIR_OBS_VAR(delay);
	if (!(zephir_array_isset_string_fetch(&delay, options, SS("delay"), 0 TSRMLS_CC))) {
		ZEPHIR_INIT_NVAR(delay);
		ZVAL_LONG(delay, 0);
	}
	ZEPHIR_OBS_VAR(ttr);
	if (!(zephir_array_isset_string_fetch(&ttr, options, SS("ttr"), 0 TSRMLS_CC))) {
		ZEPHIR_INIT_NVAR(ttr);
		ZVAL_LONG(ttr, 86400);
	}
	ZEPHIR_CALL_FUNCTION(&serialized, "serialize", NULL, 4, data);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_put_ce);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 5, serialized, priority, delay, ttr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property(&_2, response, SL("id"), PH_NOISY_CC);
	RETURN_CCTOR(_2);

}

/**
 * Change the active tube.
 *
 * <code>
 * $queue->choose('mail-queue');
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, choose) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, *response = NULL, *_0, *_1, *_2;
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


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_choose_ce);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 6, tube);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property(&_2, response, SL("tube"), PH_NOISY_CC);
	RETURN_CCTOR(_2);

}

/**
 * Reserves/locks a ready job from the specified tube.
 *
 * <code>
 * $queue->reserve();
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, reserve) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *timeout = NULL, *response = NULL, *_0, *_1, *_2 = NULL, *_3$$3, *_4$$3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &timeout);

	if (!timeout) {
		timeout = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_reserve_ce);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 7, timeout);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, response, "getresponsename", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(_2, "RESERVED")) {
		object_init_ex(return_value, beanspeak_job_ce);
		ZEPHIR_OBS_VAR(_3$$3);
		zephir_read_property(&_3$$3, response, SL("id"), PH_NOISY_CC);
		ZEPHIR_OBS_VAR(_4$$3);
		zephir_read_property(&_4$$3, response, SL("jobdata"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 8, _3$$3, _4$$3);
		zephir_check_call_status();
		RETURN_MM();
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
PHP_METHOD(Beanspeak_Beanspeak, stats) {

	zval *_0, *_1;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_stats_ce);
	if (zephir_has_constructor(_1 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_RETURN_CALL_METHOD(_0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * The pause-tube command can delay any new job being reserved for a given time.
 *
 * <code>
 * $queue->pauseTube('process-video', 60 * 60);
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, pauseTube) {

	int delay, ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, *delay_param = NULL, *response = NULL, *_0, *_1, *_2, *_3;
	zval *tube = NULL;

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
	if (unlikely(Z_TYPE_P(delay_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'delay' must be a int") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	delay = Z_LVAL_P(delay_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_pausetube_ce);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, delay);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 9, tube, _2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_3);
	zephir_read_property(&_3, response, SL("delay"), PH_NOISY_CC);
	RETURN_CCTOR(_3);

}

