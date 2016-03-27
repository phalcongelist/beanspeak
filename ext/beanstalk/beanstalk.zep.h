
extern zend_class_entry *beanstalk_beanstalk_ce;

ZEPHIR_INIT_CLASS(Beanstalk_Beanstalk);

PHP_METHOD(Beanstalk_Beanstalk, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanstalk_beanstalk___construct, 0, 0, 0)
	ZEND_ARG_OBJ_INFO(0, connection, Beanstalk\\ConnectionInterface, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanstalk_beanstalk_method_entry) {
	PHP_ME(Beanstalk_Beanstalk, __construct, arginfo_beanstalk_beanstalk___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_FE_END
};
