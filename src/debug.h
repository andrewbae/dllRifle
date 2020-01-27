#ifndef _DEBUG_H
#define _DEBUG_H

#include <windows.h>

namespace DllRifle{
    namespace Debug {
        class Console {
        private:
            LPDWORD lpdwNumberOfCharsWritten = nullptr;
            HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
            public:
            void __stdcall ConsoleOutput(const void *vBuffer);
        };
    }
}

#endif