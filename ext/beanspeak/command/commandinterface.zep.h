
extern zend_class_entry *beanspeak_command_commandinterface_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_CommandInterface);

ZEPHIR_INIT_FUNCS(beanspeak_command_commandinterface_method_entry) {
	PHP_ABSTRACT_ME(Beanspeak_Command_CommandInterface, getCommandLine, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Command_CommandInterface, hasData, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Command_CommandInterface, getData, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Command_CommandInterface, getDataLength, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Command_CommandInterface, getResponseParser, NULL)
	PHP_FE_END
};