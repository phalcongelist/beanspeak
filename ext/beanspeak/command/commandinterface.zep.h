
extern zend_class_entry *beanspeak_command_commandinterface_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_CommandInterface);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_commandinterface_execute, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, connection, Beanspeak\\Connection\\ConnectionInterface, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_commandinterface_method_entry) {
	PHP_ABSTRACT_ME(Beanspeak_Command_CommandInterface, execute, arginfo_beanspeak_command_commandinterface_execute)
	PHP_ABSTRACT_ME(Beanspeak_Command_CommandInterface, getName, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Command_CommandInterface, getCommandLine, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Command_CommandInterface, hasData, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Command_CommandInterface, getData, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Command_CommandInterface, getDataLength, NULL)
	PHP_ABSTRACT_ME(Beanspeak_Command_CommandInterface, __toString, NULL)
	PHP_FE_END
};
