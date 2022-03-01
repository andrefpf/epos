// EPOS ARMV8 CPU System Call Entry Implementation

#include <architecture/armv8/armv8_cpu.h>

__BEGIN_SYS

void CPU::syscall(void * msg)
{
    CPU::r1(reinterpret_cast<CPU::Reg>(msg));
    CPU::svc();
}

__END_SYS
