
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"


/**
 * Beanspeak\Beanspeak
 *
 * Class to access the beanstalk queue service.
 *
 * beanstalkd up to the latest version 1.10 is supported.
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
 * $task = [
 *     'recipient' => 'user@mail.com',
 *     'subject'   => 'Welcome',
 *     'content'   => $content,
 * ];
 *
 * $queue->put($task, 999, 60 * 60, 3600);
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, put) {

	int priority, delay, ttr, ZEPHIR_LAST_CALL_STATUS;
	zval *data, *priority_param = NULL, *delay_param = NULL, *ttr_param = NULL, *response = NULL, *_0, *_1, *_2, *_3, *_4, *_5;

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


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_put_ce);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, priority);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, delay);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_LONG(_4, ttr);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 4, data, _2, _3, _4);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_5);
	zephir_read_property(&_5, response, SL("id"), PH_NOISY_CC);
	RETURN_CCTOR(_5);

}

/**
 * Removes a job from the server entirely.
 *
 * <code>
 * $queue->delete(12);
 * $queue->delete($jobObject);
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, delete) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *job, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &job);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_delete_ce);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 5, job);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Allows a worker to request more time to work on a Job.
 *
 * <code>
 * $queue->touch(543);
 * $queue->touch($jobObject);
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, touch) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *job, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &job);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_touch_ce);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 6, job);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Adds the named tube to the watch list for the current connection.
 *
 * <code>
 * $count = $queue->watch($tube);
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, watch) {

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
	object_init_ex(_1, beanspeak_command_watch_ce);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 7, tube);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property(&_2, response, SL("count"), PH_NOISY_CC);
	RETURN_CCTOR(_2);

}

/**
 * Puts a "reserved" job back into the ready queue (and marks its
 * state as "ready") to be run by any client.
 *
 * <code>
 * $queue->release(12, 10, 60 * 60);
 * $queue->release($jobObject, 10, 60 * 60);
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, release) {

	int priority, delay, ZEPHIR_LAST_CALL_STATUS;
	zval *job, *priority_param = NULL, *delay_param = NULL, *_0, *_1, *_2, *_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &job, &priority_param, &delay_param);

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


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_release_ce);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, priority);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, delay);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 8, job, _2, _3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Puts a job into the "buried" state.
 *
 * <code>
 * $queue->release(12, 10, 60 * 60);
 * $queue->release($jobObject, 10, 60 * 60);
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, bury) {

	int priority, ZEPHIR_LAST_CALL_STATUS;
	zval *job, *priority_param = NULL, *_0, *_1, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &job, &priority_param);

	if (!priority_param) {
		priority = 1024;
	} else {
		priority = zephir_get_intval(priority_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_bury_ce);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, priority);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 9, job, _2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	RETURN_THIS();

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
	zval *tube_param = NULL, *response = NULL, *_0, *_1;
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
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 10, tube);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Reserves/locks a ready job from the specified tube.
 *
 * <code>
 * $queue->reserve();
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, reserve) {

	zval *timeout_param = NULL, *response = NULL, *_0, *_1, *_2, *_3 = NULL, *_4$$3, *_5$$3, *_6$$3 = NULL;
	int timeout, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &timeout_param);

	if (!timeout_param) {
		timeout = -1;
	} else {
		timeout = zephir_get_intval(timeout_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_reserve_ce);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, timeout);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 11, _2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_3, response, "getresponsename", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(_3, "RESERVED")) {
		object_init_ex(return_value, beanspeak_job_ce);
		ZEPHIR_OBS_VAR(_4$$3);
		zephir_read_property(&_4$$3, response, SL("id"), PH_NOISY_CC);
		ZEPHIR_OBS_VAR(_5$$3);
		zephir_read_property(&_5$$3, response, SL("jobdata"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&_6$$3, "unserialize", NULL, 12, _5$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 13, _4$$3, _6$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(0);

}

/**
 * Lets the client inspect a job in the system.
 *
 * <code>
 * $peekJob     = $queue->peek(91);        // Returns a Job ID
 * $peekReady   = $queue->peek('ready');   // Inspect the next ready job.
 * $peekDelayed = $queue->peek('delayed'); // Return the delayed job with the shortest delay left.
 * $peekBuried  = $queue->peek('buried');  // Return the next job in the list of buried jobs.
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, peek) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *subject, *response = NULL, *_0, *_1, *_2, *_3, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &subject);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_peek_ce);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 14, subject);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	object_init_ex(return_value, beanspeak_job_ce);
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property(&_2, response, SL("id"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(_3);
	zephir_read_property(&_3, response, SL("jobdata"), PH_NOISY_CC);
	ZEPHIR_CALL_FUNCTION(&_4, "unserialize", NULL, 12, _3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 13, _2, _4);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Lets the client inspect a job in the system.
 *
 * <code>
 * $queue->peekJob();
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, peekJob) {

	zval *id_param = NULL, *_0;
	int id, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &id_param);

	id = zephir_get_intval(id_param);


	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, id);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "peek", NULL, 0, _0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the delayed job with the shortest delay left.
 *
 * <code>
 * $queue->peekDelayed();
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, peekDelayed) {

	zval *_0;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "delayed", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "peek", NULL, 0, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the next job in the list of buried jobs.
 *
 * <code>
 * $queue->peekBuried();
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, peekBuried) {

	zval *_0;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "buried", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "peek", NULL, 0, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Inspect the next ready job.
 *
 * <code>
 * $queue->peekReady();
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, peekReady) {

	zval *_0;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "ready", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "peek", NULL, 0, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns a list of all existing tubes.
 *
 * <code>
 * $queue->listTubes();
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, listTubes) {

	zval *_0, *_1;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_listtubes_ce);
	if (zephir_has_constructor(_1 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_RETURN_CALL_METHOD(_0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns the tube currently being used by the client.
 *
 * <code>
 * $tube = $queue->listTubeUsed();
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, listTubeUsed) {

	zval *response = NULL, *_0, *_1, *_2;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_listtubeused_ce);
	if (zephir_has_constructor(_1 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&response, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property(&_2, response, SL("tube"), PH_NOISY_CC);
	RETURN_CCTOR(_2);

}

/**
 * Returns a list tubes currently being watched by the client.
 *
 * <code>
 * $queue->listTubesWatched();
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, listTubesWatched) {

	zval *_0, *_1;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_listtubeswatched_ce);
	if (zephir_has_constructor(_1 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_RETURN_CALL_METHOD(_0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	RETURN_MM();

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
 * Gives statistical information about the specified tube if it exists.
 *
 * <code>
 * $queue->statsTube('process-bitcoin');
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, statsTube) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, *_0, *_1;
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
	object_init_ex(_1, beanspeak_command_statstube_ce);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 15, tube);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(_0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Gives statistical information about the specified tube if it exists.
 *
 * <code>
 * $stats = $queue->statsJob(90);
 * $stats = $queue->statsJob($jobObject);
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, statsJob) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *job, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &job);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_statsjob_ce);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 16, job);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(_0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Moves jobs into the ready queue.
 * The Kick command applies only to the currently used tube.
 *
 * <code>
 * $queue->kick(3);
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, kick) {

	zval *bound_param = NULL, *response = NULL, *_0, *_1, *_2, *_3;
	int bound, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &bound_param);

	bound = zephir_get_intval(bound_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_kick_ce);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, bound);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 17, _2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_3);
	zephir_read_property(&_3, response, SL("kicked"), PH_NOISY_CC);
	RETURN_CCTOR(_3);

}

/**
 * A variant of kick that operates with a single job identified by its Job ID.
 *
 * <code>
 * $queue->kickJob(90);
 * $queue->kickJob($jobObject);
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, kickJob) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *job, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &job);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_kickjob_ce);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 18, job);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Removes the named tube from the watch list for the current connection.
 *
 * <code>
 * $count = $queue->ignore('tube-name);
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, ignore) {

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
	object_init_ex(_1, beanspeak_command_ignore_ce);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 19, tube);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property(&_2, response, SL("count"), PH_NOISY_CC);
	RETURN_CCTOR(_2);

}

/**
 * Can delay any new job being reserved for a given time.
 *
 * <code>
 * $queue->pauseTube('process-video', 60 * 60);
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, pauseTube) {

	int delay, ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, *delay_param = NULL, *response = NULL, *_0, *_1, *_2;
	zval *tube = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &tube_param, &delay_param);

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
	if (!delay_param) {
		delay = 0;
	} else {
		delay = zephir_get_intval(delay_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, beanspeak_command_pausetube_ce);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, delay);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 20, tube, _2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, _0, "dispatch", NULL, 0, _1);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Simply closes the connection.
 *
 * <code>
 * $queue->quit();
 * </code>
 */
PHP_METHOD(Beanspeak_Beanspeak, quit) {

	zval *dispatcher = NULL, *connection = NULL, *_0, *_1 = NULL, *_3 = NULL, *_2$$3;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(dispatcher, _0);
	ZEPHIR_CALL_METHOD(&connection, dispatcher, "getconnection", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, connection, "isconnected", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(_1)) {
		ZEPHIR_INIT_VAR(_2$$3);
		object_init_ex(_2$$3, beanspeak_command_quit_ce);
		if (zephir_has_constructor(_2$$3 TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, _2$$3, "__construct", NULL, 0);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(NULL, dispatcher, "dispatch", NULL, 0, _2$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, connection, "disconnect", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_3, connection, "isconnected", NULL, 0);
	zephir_check_call_status();
	RETURN_MM_BOOL(ZEPHIR_IS_FALSE_IDENTICAL(_3));

}

