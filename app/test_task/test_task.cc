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
        cout << "Starting test 1" << endl;
        fork(&test_1);
        fork(&test_1);
    } else {
        cout << "Hi, I am Task " << id << endl;
        print_inf();
    }

    cout << "task " << id << " finished test 1" << endl << endl;
    return 0;
}


int main()
{
    test_1();

    return 0;
}
