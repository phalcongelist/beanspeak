
extern zend_class_entry *beanspeak_connection_connectioninterface_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Connection_ConnectionInterface);

ZEPHIR_INIT_FUNCS(beanspeak_connection_connectioninterface_method_entry) {
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, connect, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, getHost, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, getPort, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, getConnectTimeout, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, isPersistent, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Connection_ConnectionInterface, isConnected, NULL)
	PHP_FE_END
};
