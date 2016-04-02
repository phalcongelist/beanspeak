
extern zend_class_entry *beanspeak_beanspeak_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Beanspeak);

PHP_METHOD(Beanspeak_Beanspeak, __construct);
PHP_METHOD(Beanspeak_Beanspeak, setDispatcher);
PHP_METHOD(Beanspeak_Beanspeak, getDispatcher);
PHP_METHOD(Beanspeak_Beanspeak, put);
PHP_METHOD(Beanspeak_Beanspeak, choose);
PHP_METHOD(Beanspeak_Beanspeak, reserve);
PHP_METHOD(Beanspeak_Beanspeak, stats);
PHP_METHOD(Beanspeak_Beanspeak, pauseTube);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak___construct, 0, 0, 0)
	ZEND_ARG_OBJ_INFO(0, dispatcher, Beanspeak\\Dispatcher\\DispatcherInterface, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_setdispatcher, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, dispatcher, Beanspeak\\Dispatcher\\DispatcherInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_put, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_choose, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_reserve, 0, 0, 0)
	ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_pausetube, 0, 0, 2)
	ZEND_ARG_INFO(0, tube)
	ZEND_ARG_INFO(0, delay)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_beanspeak_method_entry) {
	PHP_ME(Beanspeak_Beanspeak, __construct, arginfo_beanspeak_beanspeak___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Beanspeak, setDispatcher, arginfo_beanspeak_beanspeak_setdispatcher, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, getDispatcher, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, put, arginfo_beanspeak_beanspeak_put, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, choose, arginfo_beanspeak_beanspeak_choose, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, reserve, arginfo_beanspeak_beanspeak_reserve, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, stats, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, pauseTube, arginfo_beanspeak_beanspeak_pausetube, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
