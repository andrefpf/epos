#include <utility/ostream.h>
#include <syscall/message.h>

using namespace EPOS;

OStream cout;

void test_1() {
    // Printa alguma coisa através de mensagens
    Message msg(0, Message::ENTITY::DISPLAY, Message::PRINT, "Teste 1 está funcionando");
    msg.act();
}


int main()
{
    test_1();

    // CPU::syscall(0);

    return 0;
}
