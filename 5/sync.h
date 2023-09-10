#include <stdint.h>

#ifndef _SYNC_H_
#define _SYNC_H_
/*
 * Synchronization primitives.
 * TODO: Move into a separate header file and make an API out of it
 */

class __mGuard {
public:
	__mGuard() : primask(__get_PRIMASK()), loops(1) {
		__disable_irq();
	}
	~__mGuard() {
		if (primask == 0) {
			__enable_irq();
			// http://infocenter.arm.com/help/topic/com.arm.doc.dai0321a/BIHBFEIB.html
			__ISB();
		}
	}
	uint32_t enter() { return loops--; }
private:
	uint32_t primask;
	uint32_t loops;
};

#define msynchronized for (__mGuard __guard; __guard.enter(); )

#endif