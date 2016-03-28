
extern zend_class_entry *beanspeak_connection_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Connection);

PHP_METHOD(Beanspeak_Connection, __construct);
PHP_METHOD(Beanspeak_Connection, isConnected);
PHP_METHOD(Beanspeak_Connection, connect);
PHP_METHOD(Beanspeak_Connection, disconnect);
PHP_METHOD(Beanspeak_Connection, getHost);
PHP_METHOD(Beanspeak_Connection, getPort);
PHP_METHOD(Beanspeak_Connection, getConnectTimeout);
PHP_METHOD(Beanspeak_Connection, getWriteRetries);
PHP_METHOD(Beanspeak_Connection, isPersistent);
PHP_METHOD(Beanspeak_Connection, write);
PHP_METHOD(Beanspeak_Connection, read);
PHP_METHOD(Beanspeak_Connection, getLine);
static zend_object_value zephir_init_properties_Beanspeak_Connection(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_connection___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_connection_write, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_connection_read, 0, 0, 0)
	ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_connection_getline, 0, 0, 0)
	ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_connection_method_entry) {
	PHP_ME(Beanspeak_Connection, __construct, arginfo_beanspeak_connection___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Connection, isConnected, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Connection, connect, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Connection, disconnect, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Connection, getHost, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Connection, getPort, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Connection, getConnectTimeout, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Connection, getWriteRetries, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Connection, isPersistent, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Connection, write, arginfo_beanspeak_connection_write, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Connection, read, arginfo_beanspeak_connection_read, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Connection, getLine, arginfo_beanspeak_connection_getline, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
