#include <utility/ostream.h>
#include <syscall/message.h>
#include <syscall/stubs.h>

using namespace EPOS;

OStream cout;

void test_1() {
    // Printa alguma coisa através de mensagens
    Message msg(0, Message::ENTITY::DISPLAY, Message::PRINT, "Teste 1 está funcionando \n");
    msg.act();
}

void test_2() {
    // Usa o stubs common pra printar algo
    stubs::Stubs_Common display(Message::ENTITY::DISPLAY);
    display.invoke(Message::PRINT, "Teste 2 está funcionando \n");
}

void test_3() {
    // usa o stub display para printar algo
    stubs::Display display = stubs::Display();
    display.print("Teste 3 está funcionando \n");
}

int main()
{
    test_1();
    test_2();
    test_3();

    // CPU::syscall(0);

    return 0;
}
