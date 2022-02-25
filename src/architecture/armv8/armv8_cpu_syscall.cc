// EPOS ARMV8 CPU System Call Entry Implementation

#include <architecture/armv8/armv8_cpu.h>

__BEGIN_SYS

void CPU::syscall(void * msg)
{
    db<CPU>(INF) << "CPU::syscall(" << msg << ")" << endl;
    CPU::svc();
}

__END_SYS
