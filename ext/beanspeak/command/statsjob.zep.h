
extern zend_class_entry *beanspeak_command_statsjob_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_StatsJob);

PHP_METHOD(Beanspeak_Command_StatsJob, __construct);
PHP_METHOD(Beanspeak_Command_StatsJob, getName);
PHP_METHOD(Beanspeak_Command_StatsJob, getCommandLine);
PHP_METHOD(Beanspeak_Command_StatsJob, getResponseParser);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_statsjob___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, job)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_statsjob_method_entry) {
	PHP_ME(Beanspeak_Command_StatsJob, __construct, arginfo_beanspeak_command_statsjob___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_StatsJob, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_StatsJob, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_StatsJob, getResponseParser, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
