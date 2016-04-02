
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
#include "kernel/memory.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"


/**
 * Beanspeak\Job
 *
 * Represents a job in a beanstalk queue.
 */
ZEPHIR_INIT_CLASS(Beanspeak_Job) {

	ZEPHIR_REGISTER_CLASS(Beanspeak, Job, beanspeak, job, beanspeak_job_method_entry, 0);

	zend_declare_property_null(beanspeak_job_ce, SL("id"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(beanspeak_job_ce, SL("data"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(beanspeak_job_ce TSRMLS_CC, 1, beanspeak_job_jobinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Job constructor
 */
PHP_METHOD(Beanspeak_Job, __construct) {

	zval *id_param = NULL, *data, *_0;
	int id;

	zephir_fetch_params(0, 2, 0, &id_param, &data);

	if (unlikely(Z_TYPE_P(id_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'id' must be a int") TSRMLS_CC);
		RETURN_NULL();
	}
	id = Z_LVAL_P(id_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, id);
	zephir_update_property_this(this_ptr, SL("id"), _0 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("data"), data TSRMLS_CC);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Job, getId) {

	

	RETURN_MEMBER(this_ptr, "id");

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Job, getData) {

	

	RETURN_MEMBER(this_ptr, "data");

}

