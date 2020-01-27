#include "debug.h"

void __stdcall DllRifle::Debug::Console::ConsoleOutput(const void *vBuffer) 
{
    WriteConsoleA(hConsoleOutput, vBuffer, sizeof(vBuffer), lpdwNumberOfCharsWritten, NULL);
}
