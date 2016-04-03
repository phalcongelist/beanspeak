
extern zend_class_entry *beanspeak_beanspeak_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Beanspeak);

PHP_METHOD(Beanspeak_Beanspeak, __construct);
PHP_METHOD(Beanspeak_Beanspeak, setDispatcher);
PHP_METHOD(Beanspeak_Beanspeak, getDispatcher);
PHP_METHOD(Beanspeak_Beanspeak, put);
PHP_METHOD(Beanspeak_Beanspeak, delete);
PHP_METHOD(Beanspeak_Beanspeak, touch);
PHP_METHOD(Beanspeak_Beanspeak, watch);
PHP_METHOD(Beanspeak_Beanspeak, release);
PHP_METHOD(Beanspeak_Beanspeak, bury);
PHP_METHOD(Beanspeak_Beanspeak, choose);
PHP_METHOD(Beanspeak_Beanspeak, reserve);
PHP_METHOD(Beanspeak_Beanspeak, peek);
PHP_METHOD(Beanspeak_Beanspeak, peekJob);
PHP_METHOD(Beanspeak_Beanspeak, peekDelayed);
PHP_METHOD(Beanspeak_Beanspeak, peekBuried);
PHP_METHOD(Beanspeak_Beanspeak, peekReady);
PHP_METHOD(Beanspeak_Beanspeak, listTubes);
PHP_METHOD(Beanspeak_Beanspeak, listTubeUsed);
PHP_METHOD(Beanspeak_Beanspeak, listTubesWatched);
PHP_METHOD(Beanspeak_Beanspeak, stats);
PHP_METHOD(Beanspeak_Beanspeak, statsTube);
PHP_METHOD(Beanspeak_Beanspeak, statsJob);
PHP_METHOD(Beanspeak_Beanspeak, kick);
PHP_METHOD(Beanspeak_Beanspeak, kickJob);
PHP_METHOD(Beanspeak_Beanspeak, ignore);
PHP_METHOD(Beanspeak_Beanspeak, pauseTube);
PHP_METHOD(Beanspeak_Beanspeak, quit);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak___construct, 0, 0, 0)
	ZEND_ARG_OBJ_INFO(0, dispatcher, Beanspeak\\Dispatcher\\DispatcherInterface, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_setdispatcher, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, dispatcher, Beanspeak\\Dispatcher\\DispatcherInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_put, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, priority)
	ZEND_ARG_INFO(0, delay)
	ZEND_ARG_INFO(0, ttr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_delete, 0, 0, 1)
	ZEND_ARG_INFO(0, job)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_touch, 0, 0, 1)
	ZEND_ARG_INFO(0, job)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_watch, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_release, 0, 0, 1)
	ZEND_ARG_INFO(0, job)
	ZEND_ARG_INFO(0, priority)
	ZEND_ARG_INFO(0, delay)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_bury, 0, 0, 1)
	ZEND_ARG_INFO(0, job)
	ZEND_ARG_INFO(0, priority)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_choose, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_reserve, 0, 0, 0)
	ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_peek, 0, 0, 1)
	ZEND_ARG_INFO(0, subject)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_peekjob, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_statstube, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_statsjob, 0, 0, 1)
	ZEND_ARG_INFO(0, job)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_kick, 0, 0, 1)
	ZEND_ARG_INFO(0, bound)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_kickjob, 0, 0, 1)
	ZEND_ARG_INFO(0, job)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_ignore, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_beanspeak_pausetube, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
	ZEND_ARG_INFO(0, delay)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_beanspeak_method_entry) {
	PHP_ME(Beanspeak_Beanspeak, __construct, arginfo_beanspeak_beanspeak___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Beanspeak, setDispatcher, arginfo_beanspeak_beanspeak_setdispatcher, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, getDispatcher, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, put, arginfo_beanspeak_beanspeak_put, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, delete, arginfo_beanspeak_beanspeak_delete, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, touch, arginfo_beanspeak_beanspeak_touch, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, watch, arginfo_beanspeak_beanspeak_watch, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, release, arginfo_beanspeak_beanspeak_release, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, bury, arginfo_beanspeak_beanspeak_bury, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, choose, arginfo_beanspeak_beanspeak_choose, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, reserve, arginfo_beanspeak_beanspeak_reserve, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, peek, arginfo_beanspeak_beanspeak_peek, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, peekJob, arginfo_beanspeak_beanspeak_peekjob, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, peekDelayed, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, peekBuried, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, peekReady, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, listTubes, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, listTubeUsed, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, listTubesWatched, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, stats, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, statsTube, arginfo_beanspeak_beanspeak_statstube, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, statsJob, arginfo_beanspeak_beanspeak_statsjob, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, kick, arginfo_beanspeak_beanspeak_kick, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, kickJob, arginfo_beanspeak_beanspeak_kickjob, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, ignore, arginfo_beanspeak_beanspeak_ignore, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, pauseTube, arginfo_beanspeak_beanspeak_pausetube, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Beanspeak, quit, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
