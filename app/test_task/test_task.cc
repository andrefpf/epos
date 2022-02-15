// EPOS Task Test Program

#include <time.h>
#include <process.h>
#include <machine.h>
#include <utility/fork.h>

using namespace EPOS;

int print_inf();

OStream cout;

int print_inf() {
    Task * task = Task::self();
    Address_Space * as = task->address_space();
    cout << "===========================================" << "\n"
         << "=Address Space page directory: " << as->pd() << "=\n"
         << "=Code Logical Addr: " << static_cast<void *>(task->code()) << "=\n"
         << "=Code Physical Addr: " << static_cast<void *>(as->physical(task->code())) << "=\n"
         << "=Code Size: " << task->code_segment()->size() << " bytes long" << "=\n"
         << "=Data Logical Addr: " << static_cast<void *>(task->data()) << "=\n"
         << "=Data Physical Addr: " << static_cast<void *>(as->physical(task->data())) << "=\n"
         << "=Data Size: " << task->data_segment()->size() << " bytes long" << "=\n"
         << "===========================================" << endl;
    return 0;
}

int test_1() {
    int id = Task::self()->id();

    if (id == 0) {
    	cout << "=====Starting test 1=====" << endl;
        fork(&test_1);
        fork(&test_1);
    } else {
        cout << "Hi, I am Task " << id << endl;
        print_inf();
    }

    cout << "task " << id << " finished test 1" << endl << endl;
    return 0;
}

int test_2()
{
    cout << "=====Starting test 2=====" << endl;
    cout << "Task Addres Space and Segment test" << endl;
    System_Info * si = System::info();
    cout << "App location in System Info \n" 
         << " App Code Segment :" << CPU::Phy_Addr(si->pmm.app_code) << "\n"
         << " App Data Segment :" << CPU::Phy_Addr(si->pmm.app_data)
         << endl;

    Task * task0 = Task::self();
    Address_Space * as0 = task0->address_space();
    cout << "\nMy address space's page directory is located at " << as0->pd() << endl;

    Segment * cs0 = task0->code_segment();
    CPU::Log_Addr code0 = task0->code();
    CPU::Phy_Addr code_phy = as0->physical(code0);
    cout << "\nMy code segment is : " << "\n"
         << "Logical Addr: " << static_cast<void *>(code0) << "\n"
         << "Physical Addr: " << static_cast<void *>(code_phy) << "\n"
         << "Size: " << cs0->size() << " bytes long" << endl;

    // Assert if Logical Memory is Valid in Code Segment
    cout << "\nAssert if logic code is valid" << endl;
    assert(code0 == Memory_Map::APP_CODE);

    Segment * ds0 = task0->data_segment();
    CPU::Log_Addr data0 = task0->data();
    CPU::Phy_Addr data_phy = as0->physical(data0);
    cout << "\nMy data segment is : " << "\n"
         << "Logical Addr: " << static_cast<void *>(data0) << "\n"
         << "Physical Addr: " << static_cast<void *>(data_phy) << "\n"
         << "Size: " << ds0->size() << " bytes long" << endl;
    
    // Assert if Logical Memory is Valid in Data Segment
    cout << "\nAssert if logic data is valid" << endl;
    assert(data0 == Memory_Map::APP_DATA);

    // Assert if the Physicall memory data is located with correct space from code
    cout << "Assert if phy data has size needed" << endl;
    assert((data_phy + ds0->size()) == code_phy);

    cout << "I'm done, bye!" << endl;
	    return 0;
}

int func_a() {
    cout << "Nǐ hǎo wǒ shì “rènwù”: "<< Task::self()->id() << endl;
    int step = 1000000;
    for (int i = 0; i < 100000000; ++i) {
      if (!(i % step)) {
        ASM("_func_a_h:");
        cout << "Checkpoint! ("<<Task::self()->id() <<")("<<i/step<<")" << endl;
        // Alarm::delay(100000);
      }
    }
    cout << "Task " << Task::self()->id() << "Shuō zàijiàn!" << endl;
    return 0;
}

int test_3()
{  
    cout << "=====Starting test 3=====" << endl;
    cout << "=====Test Task Timer "<< Task::self()->id()<<"=====" << endl;

    if (Task::self()->id() == 0) {
        fork(&func_a);
        fork(&func_a);
        cout << "Hello World! I'm Task: "<< Task::self()->id() << endl;
    }
    if (Task::self()->id() == 1) {
        cout << "Nǐ hǎo shìjiè wǒ shì rènwù: "<< Task::self()->id() << endl;
	func_a();
    }
    if (Task::self()->id() == 2) {
        cout << "Annyeong haseyo wǒ shì rènwù: "<< Task::self()->id() << endl;
        func_a();
    }

    print_inf();
    cout << "Zàijiàn! onz" << endl;
    return 0;
}

int main()
{
    test_1();
    test_2();
    test_3();
    return 0;
}
