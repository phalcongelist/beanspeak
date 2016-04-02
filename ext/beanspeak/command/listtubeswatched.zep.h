
extern zend_class_entry *beanspeak_command_listtubeswatched_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_ListTubesWatched);

PHP_METHOD(Beanspeak_Command_ListTubesWatched, getName);
PHP_METHOD(Beanspeak_Command_ListTubesWatched, getCommandLine);
PHP_METHOD(Beanspeak_Command_ListTubesWatched, getResponseParser);

ZEPHIR_INIT_FUNCS(beanspeak_command_listtubeswatched_method_entry) {
	PHP_ME(Beanspeak_Command_ListTubesWatched, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_ListTubesWatched, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_ListTubesWatched, getResponseParser, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
