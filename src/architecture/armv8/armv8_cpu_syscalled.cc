// EPOS ARMV8 CPU System Call Entry Implementation

#include <architecture/armv8/armv8_cpu.h>

extern "C" { void _exec(void * msg); }

__BEGIN_SYS

void CPU::syscalled(void * msg = 0) {
    _exec(msg);
}

__END_SYS
