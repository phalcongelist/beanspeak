
extern zend_class_entry *beanspeak_client_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Client);

PHP_METHOD(Beanspeak_Client, getUsedTube);
PHP_METHOD(Beanspeak_Client, getWatchedTubes);
PHP_METHOD(Beanspeak_Client, __construct);
PHP_METHOD(Beanspeak_Client, connect);
PHP_METHOD(Beanspeak_Client, __destruct);
PHP_METHOD(Beanspeak_Client, disconnect);
PHP_METHOD(Beanspeak_Client, isConnected);
PHP_METHOD(Beanspeak_Client, put);
PHP_METHOD(Beanspeak_Client, putInTube);
PHP_METHOD(Beanspeak_Client, useTube);
PHP_METHOD(Beanspeak_Client, peekJob);
PHP_METHOD(Beanspeak_Client, peekDelayed);
PHP_METHOD(Beanspeak_Client, peekBuried);
PHP_METHOD(Beanspeak_Client, peekReady);
PHP_METHOD(Beanspeak_Client, kick);
PHP_METHOD(Beanspeak_Client, watch);
PHP_METHOD(Beanspeak_Client, ignore);
PHP_METHOD(Beanspeak_Client, stats);
PHP_METHOD(Beanspeak_Client, statsTube);
PHP_METHOD(Beanspeak_Client, listTubes);
PHP_METHOD(Beanspeak_Client, listTubeUsed);
PHP_METHOD(Beanspeak_Client, listTubesWatched);
PHP_METHOD(Beanspeak_Client, pauseTube);
PHP_METHOD(Beanspeak_Client, resumeTube);
PHP_METHOD(Beanspeak_Client, quit);
PHP_METHOD(Beanspeak_Client, write);
PHP_METHOD(Beanspeak_Client, read);
PHP_METHOD(Beanspeak_Client, readYaml);
PHP_METHOD(Beanspeak_Client, readStatus);
PHP_METHOD(Beanspeak_Client, yamlParse);
static zend_object_value zephir_init_properties_Beanspeak_Client(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client_put, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, priority)
	ZEND_ARG_INFO(0, delay)
	ZEND_ARG_INFO(0, ttr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client_putintube, 0, 0, 2)
	ZEND_ARG_INFO(0, tube)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, priority)
	ZEND_ARG_INFO(0, delay)
	ZEND_ARG_INFO(0, ttr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client_usetube, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client_peekjob, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client_kick, 0, 0, 1)
	ZEND_ARG_INFO(0, bound)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client_watch, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client_ignore, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client_statstube, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client_listtubeused, 0, 0, 0)
	ZEND_ARG_INFO(0, ask)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client_pausetube, 0, 0, 2)
	ZEND_ARG_INFO(0, tube)
	ZEND_ARG_INFO(0, delay)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client_resumetube, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client_write, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_client_read, 0, 0, 0)
	ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_client_method_entry) {
	PHP_ME(Beanspeak_Client, getUsedTube, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, getWatchedTubes, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, __construct, arginfo_beanspeak_client___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Client, connect, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, __destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	PHP_ME(Beanspeak_Client, disconnect, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, isConnected, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, put, arginfo_beanspeak_client_put, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, putInTube, arginfo_beanspeak_client_putintube, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, useTube, arginfo_beanspeak_client_usetube, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, peekJob, arginfo_beanspeak_client_peekjob, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, peekDelayed, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, peekBuried, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, peekReady, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, kick, arginfo_beanspeak_client_kick, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, watch, arginfo_beanspeak_client_watch, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, ignore, arginfo_beanspeak_client_ignore, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, stats, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, statsTube, arginfo_beanspeak_client_statstube, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, listTubes, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, listTubeUsed, arginfo_beanspeak_client_listtubeused, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, listTubesWatched, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, pauseTube, arginfo_beanspeak_client_pausetube, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, resumeTube, arginfo_beanspeak_client_resumetube, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, quit, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, write, arginfo_beanspeak_client_write, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, read, arginfo_beanspeak_client_read, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, readYaml, NULL, ZEND_ACC_FINAL|ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, readStatus, NULL, ZEND_ACC_FINAL|ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Client, yamlParse, NULL, ZEND_ACC_PRIVATE)
	PHP_FE_END
};
