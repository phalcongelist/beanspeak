
extern zend_class_entry *beanspeak_dispatcher_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Dispatcher);

PHP_METHOD(Beanspeak_Dispatcher, __construct);
PHP_METHOD(Beanspeak_Dispatcher, getConnection);
PHP_METHOD(Beanspeak_Dispatcher, setConnection);
PHP_METHOD(Beanspeak_Dispatcher, dispatch);
void zep_Beanspeak_Dispatcher__dispatch(int ht, zval *return_value, zval **return_value_ptr, zval *this_ptr, int return_value_used, zval *command_ext TSRMLS_DC);
PHP_METHOD(Beanspeak_Dispatcher, reconnect);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_dispatcher___construct, 0, 0, 0)
	ZEND_ARG_OBJ_INFO(0, connection, Beanspeak\\Connection\\ConnectionInterface, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_dispatcher_setconnection, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, connection, Beanspeak\\Connection\\ConnectionInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_dispatcher_dispatch, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, command, Beanspeak\\Command\\CommandInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_dispatcher__dispatch, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, command, Beanspeak\\Command\\CommandInterface, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_dispatcher_method_entry) {
	PHP_ME(Beanspeak_Dispatcher, __construct, arginfo_beanspeak_dispatcher___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Dispatcher, getConnection, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Dispatcher, setConnection, arginfo_beanspeak_dispatcher_setconnection, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Dispatcher, dispatch, arginfo_beanspeak_dispatcher_dispatch, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Dispatcher, reconnect, NULL, ZEND_ACC_PRIVATE)
	PHP_FE_END
};
