
extern zend_class_entry *beanstalk_beanstalk_ce;

ZEPHIR_INIT_CLASS(Beanstalk_Beanstalk);

PHP_METHOD(Beanstalk_Beanstalk, __construct);
PHP_METHOD(Beanstalk_Beanstalk, getConnection);
PHP_METHOD(Beanstalk_Beanstalk, setConnection);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanstalk_beanstalk___construct, 0, 0, 0)
	ZEND_ARG_OBJ_INFO(0, connection, Beanstalk\\Connection\\ConnectionInterface, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanstalk_beanstalk_setconnection, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, connection, Beanstalk\\Connection\\ConnectionInterface, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanstalk_beanstalk_method_entry) {
	PHP_ME(Beanstalk_Beanstalk, __construct, arginfo_beanstalk_beanstalk___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanstalk_Beanstalk, getConnection, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanstalk_Beanstalk, setConnection, arginfo_beanstalk_beanstalk_setconnection, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
