
extern zend_class_entry *beanspeak_dispatcher_dispatcherinterface_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Dispatcher_DispatcherInterface);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_dispatcher_dispatcherinterface_dispatch, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, command, Beanspeak\\Command\\CommandInterface, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_dispatcher_dispatcherinterface_method_entry) {
	PHP_ABSTRACT_ME(Beanspeak_Dispatcher_DispatcherInterface, dispatch, arginfo_beanspeak_dispatcher_dispatcherinterface_dispatch)
	PHP_FE_END
};
