
extern zend_class_entry *beanspeak_responseinterface_ce;

ZEPHIR_INIT_CLASS(Beanspeak_ResponseInterface);

ZEPHIR_INIT_FUNCS(beanspeak_responseinterface_method_entry) {
	PHP_ABSTRACT_ME(Beanspeak_ResponseInterface, getResponseName, NULL)
	PHP_FE_END
};
