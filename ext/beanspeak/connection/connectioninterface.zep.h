
extern zend_class_entry *beanspeak_connection_connectioninterface_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Connection_ConnectionInterface);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_connection_connectioninterface_write, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_connection_connectioninterface_read, 0, 0, 0)
	ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_connection_connectioninterface_getline, 0, 0, 0)
	ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_connection_connectioninterface_method_entry) {
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, connect, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, disconnect, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, getHost, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, getPort, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, getConnectTimeout, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, getWriteRetries, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, isPersistent, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, isConnected, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, write, arginfo_beanspeak_connection_connectioninterface_write)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, read, arginfo_beanspeak_connection_connectioninterface_read)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, getLine, arginfo_beanspeak_connection_connectioninterface_getline)
	PHP_FE_END
};
