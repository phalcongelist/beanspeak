
extern zend_class_entry *beanspeak_command_stats_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_Stats);

PHP_METHOD(Beanspeak_Command_Stats, getName);
PHP_METHOD(Beanspeak_Command_Stats, getCommandLine);
PHP_METHOD(Beanspeak_Command_Stats, getResponseParser);

ZEPHIR_INIT_FUNCS(beanspeak_command_stats_method_entry) {
	PHP_ME(Beanspeak_Command_Stats, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Stats, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Stats, getResponseParser, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
