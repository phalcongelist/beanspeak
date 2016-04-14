
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
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/array.h"
#include "kernel/exception.h"


/**
 * Beanspeak\Job
 *
 * Represents a job in a beanstalk queue.
 */
ZEPHIR_INIT_CLASS(Beanspeak_Job) {

	ZEPHIR_REGISTER_CLASS(Beanspeak, Job, beanspeak, job, beanspeak_job_method_entry, 0);

	/**
	 * @var Client
	 */
	zend_declare_property_null(beanspeak_job_ce, SL("queue"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 */
	zend_declare_property_null(beanspeak_job_ce, SL("id"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var mixed
	 */
	zend_declare_property_null(beanspeak_job_ce, SL("body"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 */
PHP_METHOD(Beanspeak_Job, getId) {

	

	RETURN_MEMBER(this_ptr, "id");

}

/**
 */
PHP_METHOD(Beanspeak_Job, getBody) {

	

	RETURN_MEMBER(this_ptr, "body");

}

/**
 * Beanspeak\Job constructor
 */
PHP_METHOD(Beanspeak_Job, __construct) {

	zval *id = NULL;
	zval *queue, *id_param = NULL, *body;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &queue, &id_param, &body);

	zephir_get_strval(id, id_param);


	zephir_update_property_this(this_ptr, SL("queue"), queue TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("id"), id TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("body"), body TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Removes a job from the server entirely.
 *
 * <code>
 * $job->delete();
 * </code>
 */
PHP_METHOD(Beanspeak_Job, delete) {

	zend_bool _2;
	zval *queue = NULL, *response = NULL, *_0, *_1, *_3;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("queue"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(queue, _0);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_SV(_1, "delete ", _0);
	ZEPHIR_CALL_METHOD(NULL, queue, "write", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, queue, "readstatus", NULL, 0);
	zephir_check_call_status();
	_2 = zephir_array_isset_long(response, 0);
	if (_2) {
		zephir_array_fetch_long(&_3, response, 0, PH_NOISY | PH_READONLY, "beanspeak/job.zep", 68 TSRMLS_CC);
		_2 = ZEPHIR_IS_STRING(_3, "DELETED");
	}
	RETURN_MM_BOOL(_2);

}

/**
 * Allows a worker to request more time to work on a Job.
 *
 * <code>
 * $job->touch();
 * </code>
 */
PHP_METHOD(Beanspeak_Job, touch) {

	zend_bool _2;
	zval *queue = NULL, *response = NULL, *_0, *_1, *_3;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("queue"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(queue, _0);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_SV(_1, "touch ", _0);
	ZEPHIR_CALL_METHOD(NULL, queue, "write", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, queue, "readstatus", NULL, 0);
	zephir_check_call_status();
	_2 = zephir_array_isset_long(response, 0);
	if (_2) {
		zephir_array_fetch_long(&_3, response, 0, PH_NOISY | PH_READONLY, "beanspeak/job.zep", 87 TSRMLS_CC);
		_2 = ZEPHIR_IS_STRING(_3, "TOUCHED");
	}
	RETURN_MM_BOOL(_2);

}

/**
 * Puts a "reserved" job back into the ready queue (and marks its
 * state as "ready") to be run by any client.
 *
 * <code>
 * $job->release(10, 60 * 60);
 * </code>
 */
PHP_METHOD(Beanspeak_Job, release) {

	zend_bool _4;
	zval *priority_param = NULL, *delay_param = NULL, *queue = NULL, *response = NULL, *_0, _1, _2, *_3, *_5;
	int priority, delay, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &priority_param, &delay_param);

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


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("queue"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(queue, _0);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_LONG(&_1, priority);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_LONG(&_2, delay);
	ZEPHIR_INIT_VAR(_3);
	ZEPHIR_CONCAT_SVSVSV(_3, "release ", _0, " ", &_1, " ", &_2);
	ZEPHIR_CALL_METHOD(NULL, queue, "write", NULL, 0, _3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, queue, "readstatus", NULL, 0);
	zephir_check_call_status();
	_4 = zephir_array_isset_long(response, 0);
	if (_4) {
		zephir_array_fetch_long(&_5, response, 0, PH_NOISY | PH_READONLY, "beanspeak/job.zep", 108 TSRMLS_CC);
		_4 = ZEPHIR_IS_STRING(_5, "RELEASED");
	}
	RETURN_MM_BOOL(_4);

}

/**
 * Puts a job into the "buried" state.
 *
 * <code>
 * $job->release(10, 60 * 60);
 * </code>
 */
PHP_METHOD(Beanspeak_Job, bury) {

	zend_bool _3;
	zval *priority_param = NULL, *queue = NULL, *response = NULL, *_0, _1, *_2, *_4;
	int priority, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &priority_param);

	if (!priority_param) {
		priority = 1024;
	} else {
		priority = zephir_get_intval(priority_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("queue"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(queue, _0);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_LONG(&_1, priority);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SVSV(_2, "bury ", _0, " ", &_1);
	ZEPHIR_CALL_METHOD(NULL, queue, "write", NULL, 0, _2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, queue, "readstatus", NULL, 0);
	zephir_check_call_status();
	_3 = zephir_array_isset_long(response, 0);
	if (_3) {
		zephir_array_fetch_long(&_4, response, 0, PH_NOISY | PH_READONLY, "beanspeak/job.zep", 127 TSRMLS_CC);
		_3 = ZEPHIR_IS_STRING(_4, "BURIED");
	}
	RETURN_MM_BOOL(_3);

}

/**
 * Gives statistical information about the specified job if it exists.
 *
 * <code>
 * $stats = $job->stats();
 * </code>
 */
PHP_METHOD(Beanspeak_Job, stats) {

	zval *queue = NULL, *response = NULL, *_0, *_1, *_2, *_3;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("queue"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(queue, _0);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_SV(_1, "stats-job ", _0);
	ZEPHIR_CALL_METHOD(NULL, queue, "write", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, queue, "readyaml", NULL, 0);
	zephir_check_call_status();
	zephir_array_fetch_long(&_2, response, 0, PH_NOISY | PH_READONLY, "beanspeak/job.zep", 145 TSRMLS_CC);
	if (!ZEPHIR_IS_STRING(_2, "OK")) {
		RETURN_MM_BOOL(0);
	}
	zephir_array_fetch_long(&_3, response, 2, PH_NOISY | PH_READONLY, "beanspeak/job.zep", 149 TSRMLS_CC);
	RETURN_CTOR(_3);

}

/**
 * A variant of Client::kick that operates with a single job identified by its Job ID.
 *
 * <code>
 * $job->kick();
 * </code>
 */
PHP_METHOD(Beanspeak_Job, kick) {

	zend_bool _2;
	zval *queue = NULL, *response = NULL, *_0, *_1, *_3;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("queue"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(queue, _0);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_SV(_1, "kick-job ", _0);
	ZEPHIR_CALL_METHOD(NULL, queue, "write", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, queue, "readstatus", NULL, 0);
	zephir_check_call_status();
	_2 = zephir_array_isset_long(response, 0);
	if (_2) {
		zephir_array_fetch_long(&_3, response, 0, PH_NOISY | PH_READONLY, "beanspeak/job.zep", 168 TSRMLS_CC);
		_2 = ZEPHIR_IS_STRING(_3, "KICKED");
	}
	RETURN_MM_BOOL(_2);

}

/**
 * Checks if the job has been modified after unserializing the object
 */
PHP_METHOD(Beanspeak_Job, __wakeup) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("id"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) != IS_STRING) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_exception_ce, "Unexpected inconsistency in Beanspeak\\Job::__wakeup() - possible break-in attempt!", "beanspeak/job.zep", 177);
		return;
	}
	ZEPHIR_MM_RESTORE();

}

