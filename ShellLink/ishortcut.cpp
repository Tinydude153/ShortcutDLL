#include <ShellLink/shortcut.h>

extern "C" __declspec(dllexport) Shortcut* ShInitialize() { 
    return new Shortcut();
}

extern "C" __declspec(dllexport) void ShUninitialize() {
    std::cout << "lve";
    //delete sh;
}
