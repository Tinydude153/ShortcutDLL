Compiled with MinGW-W64 x86_64-msvcrt-posix-seh 13.1.0
DLL: g++ -shared -I".h" -o shl.dll ShellLink\shortcut.cpp -lole32 -luuid
EXE: g++ -I".h" ShellLink\main.cpp "...\shl.dll"
