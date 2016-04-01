
extern zend_class_entry *beanspeak_job_jobinterface_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Job_JobInterface);

ZEPHIR_INIT_FUNCS(beanspeak_job_jobinterface_method_entry) {
	PHP_ABSTRACT_ME(Beanspeak_Job_JobInterface, getId, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Job_JobInterface, getData, NULL)
	PHP_FE_END
};
