
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Beanspeak\Job\JobInterface
 */
ZEPHIR_INIT_CLASS(Beanspeak_Job_JobInterface) {

	ZEPHIR_REGISTER_INTERFACE(Beanspeak\\Job, JobInterface, beanspeak, job_jobinterface, beanspeak_job_jobinterface_method_entry);

	return SUCCESS;

}

/**
 * Gets the Job ID, unique on the beanstalkd server.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Job_JobInterface, getId);

/**
 * Gets the Job data.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Job_JobInterface, getData);

