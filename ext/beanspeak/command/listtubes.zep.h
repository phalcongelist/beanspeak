
extern zend_class_entry *beanspeak_command_listtubes_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_ListTubes);

PHP_METHOD(Beanspeak_Command_ListTubes, getName);
PHP_METHOD(Beanspeak_Command_ListTubes, getCommandLine);
PHP_METHOD(Beanspeak_Command_ListTubes, getResponseParser);

ZEPHIR_INIT_FUNCS(beanspeak_command_listtubes_method_entry) {
	PHP_ME(Beanspeak_Command_ListTubes, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_ListTubes, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_ListTubes, getResponseParser, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
