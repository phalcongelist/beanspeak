
extern zend_class_entry *beanspeak_command_listtubeused_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_ListTubeUsed);

PHP_METHOD(Beanspeak_Command_ListTubeUsed, getName);
PHP_METHOD(Beanspeak_Command_ListTubeUsed, getCommandLine);
PHP_METHOD(Beanspeak_Command_ListTubeUsed, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_listtubeused_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_listtubeused_method_entry) {
	PHP_ME(Beanspeak_Command_ListTubeUsed, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_ListTubeUsed, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_ListTubeUsed, parseResponse, arginfo_beanspeak_command_listtubeused_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
