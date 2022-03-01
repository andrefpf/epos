#include <utility/ostream.h>
#include <synchronizer.h>
#include <process.h>

using namespace EPOS;

OStream cout;

int func_a();
int func_b();

int func_a() {
    cout << "Start of func_a job" << endl;

    for (int i = 0; i < 10000000; ++i) {
        if (!(i % 100000)) {
            cout << "Func A " << i / 100000 << endl;
        }
    }

    cout << "End of func_a job" << endl;

    return 0;
}


int main()
{
    cout << "Hello Syscall!" << endl;

    Thread a(&func_a);

    cout << "Start of main job" << endl;

    for (int i = 0; i < 10000000; ++i) {
        if (!(i % 100000)) {
            cout << "Main " << i / 100000 << endl;
        }
    }

    cout << "End of main job" << endl;

    a.join();

    cout << "Finished!" << endl;

    return 0;
}