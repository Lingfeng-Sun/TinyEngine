

#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdlib.h>
#include "Global.h"
#include "mimalloc.h"
#include "TinyLog.h"

int main(int argc, char* argv[])
{
    ty::Global::Initialize();

    mi_option_set(mi_option_verbose, 1);

    void* q = malloc(64);
    free(q);

    void* p1 = ty_aligned_malloc(64, 64);
    ty_aligned_free(p1);

    int* p = new int(42);
    if (p)
    {
        std::cout << "p: " << *p << std::endl;
        delete p;
    }
    int* arr = new int[10];
    if (arr)
    {
        for (int i = 0; i < 10; i++)
        {
            arr[i] = i;
        }
        for (int i = 0; i < 10; i++)
        {
            std::cout << "arr[" << i << "]: " << arr[i] << std::endl;
        }
        delete[] arr;
    }

    ty::TyLog::LogInfo("Hello World!");

    system("pause");
}
