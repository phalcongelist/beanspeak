
extern zend_class_entry *beanspeak_responseparserinterface_ce;

ZEPHIR_INIT_CLASS(Beanspeak_ResponseParserInterface);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_responseparserinterface_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_responseparserinterface_method_entry) {
	PHP_ABSTRACT_ME(Beanspeak_ResponseParserInterface, parseResponse, arginfo_beanspeak_responseparserinterface_parseresponse)
	PHP_FE_END
};
