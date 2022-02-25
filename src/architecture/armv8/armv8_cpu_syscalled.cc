// EPOS ARMV8 CPU System Call Entry Implementation

#include <architecture/armv8/armv8_cpu.h>

extern "C" { void _sysexec(void * msg); }

__BEGIN_SYS

void CPU::syscalled(void * msg = 0) {
    db<Syscall>(INF) << "CPU::syscalled(" << msg << ") \t Exception Level: " << CPU::el() << endl;

    if (msg)
        _sysexec(msg);
}

__END_SYS
