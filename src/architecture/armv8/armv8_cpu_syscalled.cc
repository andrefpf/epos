// EPOS ARMV8 CPU System Call Entry Implementation

#include <architecture/armv8/armv8_cpu.h>

extern "C" { void _sysexec(); }

__BEGIN_SYS

void CPU::syscalled()
{
    db<CPU>(INF) << "CPU::syscalled()" << endl;
}

__END_SYS
