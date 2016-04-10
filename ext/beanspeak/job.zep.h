
extern zend_class_entry *beanspeak_job_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Job);

PHP_METHOD(Beanspeak_Job, getId);
PHP_METHOD(Beanspeak_Job, getBody);
PHP_METHOD(Beanspeak_Job, __construct);
PHP_METHOD(Beanspeak_Job, delete);
PHP_METHOD(Beanspeak_Job, touch);
PHP_METHOD(Beanspeak_Job, release);
PHP_METHOD(Beanspeak_Job, bury);
PHP_METHOD(Beanspeak_Job, stats);
PHP_METHOD(Beanspeak_Job, kick);
PHP_METHOD(Beanspeak_Job, __wakeup);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_job___construct, 0, 0, 3)
	ZEND_ARG_OBJ_INFO(0, queue, Beanspeak\\Client, 0)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, body)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_job_release, 0, 0, 0)
	ZEND_ARG_INFO(0, priority)
	ZEND_ARG_INFO(0, delay)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_job_bury, 0, 0, 0)
	ZEND_ARG_INFO(0, priority)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_job_method_entry) {
	PHP_ME(Beanspeak_Job, getId, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Job, getBody, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Job, __construct, arginfo_beanspeak_job___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Job, delete, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Job, touch, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Job, release, arginfo_beanspeak_job_release, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Job, bury, arginfo_beanspeak_job_bury, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Job, stats, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Job, kick, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Job, __wakeup, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
