
extern zend_class_entry *beanspeak_response_parser_parserinterface_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Response_Parser_ParserInterface);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_response_parser_parserinterface_parse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_response_parser_parserinterface_method_entry) {
	PHP_ABSTRACT_ME(Beanspeak_Response_Parser_ParserInterface, parse, arginfo_beanspeak_response_parser_parserinterface_parse)
	PHP_FE_END
};
