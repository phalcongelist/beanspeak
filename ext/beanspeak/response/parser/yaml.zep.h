
extern zend_class_entry *beanspeak_response_parser_yaml_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Response_Parser_Yaml);

PHP_METHOD(Beanspeak_Response_Parser_Yaml, __construct);
PHP_METHOD(Beanspeak_Response_Parser_Yaml, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_response_parser_yaml___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_response_parser_yaml_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_response_parser_yaml_method_entry) {
	PHP_ME(Beanspeak_Response_Parser_Yaml, __construct, arginfo_beanspeak_response_parser_yaml___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Response_Parser_Yaml, parseResponse, arginfo_beanspeak_response_parser_yaml_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
