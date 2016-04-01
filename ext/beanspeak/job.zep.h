
extern zend_class_entry *beanspeak_job_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Job);

PHP_METHOD(Beanspeak_Job, __construct);
PHP_METHOD(Beanspeak_Job, getId);
PHP_METHOD(Beanspeak_Job, getData);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_job___construct, 0, 0, 2)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_job_method_entry) {
	PHP_ME(Beanspeak_Job, __construct, arginfo_beanspeak_job___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Job, getId, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Job, getData, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
