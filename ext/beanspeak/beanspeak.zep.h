
extern zend_class_entry *beanspeak_beanspeak_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Beanspeak);

PHP_METHOD(Beanspeak_Beanspeak, __construct);
PHP_METHOD(Beanspeak_Beanspeak, getConnection);
PHP_METHOD(Beanspeak_Beanspeak, setConnection);
PHP_METHOD(Beanspeak_Beanspeak, reconnect);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak___construct, 0, 0, 0)
	ZEND_ARG_OBJ_INFO(0, connection, Beanspeak\\Connection\\ConnectionInterface, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_setconnection, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, connection, Beanspeak\\Connection\\ConnectionInterface, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_beanspeak_method_entry) {
	PHP_ME(Beanspeak_Beanspeak, __construct, arginfo_beanspeak_beanspeak___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Beanspeak, getConnection, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, setConnection, arginfo_beanspeak_beanspeak_setconnection, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, reconnect, NULL, ZEND_ACC_PRIVATE)
	PHP_FE_END
};
