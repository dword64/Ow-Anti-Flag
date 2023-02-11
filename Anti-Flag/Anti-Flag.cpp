/*
    Successor of Anti-Flag and Anti-Flag-V2.

    Developers:
    - DWORD64
    - Sixmax
*/
#if !_WIN32
#include <iostream>
int main()
{
    printf("You can only compile this on and for Windows.\n");
    return 0;
}
#else 
#include "Executer.hpp"
int main()
{
    return Exe::run();
}
#endif
/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/