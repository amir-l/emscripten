#include "pthread_impl.h"

int pthread_setschedparam(pthread_t t, int policy, const struct sched_param *param)
{
#ifdef __EMSCRIPTEN__ // XXX Emscripten web or Node workers doesn't support prioritizing threads
	// no-op
	return 0;
#else
	int r;
	__lock(t->killlock);
	r = t->dead ? ESRCH : -__syscall(SYS_sched_setscheduler, t->tid, policy, param);
	__unlock(t->killlock);
	return r;
#endif
}
