
#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main() {

	testFunction();
	mainExe();
	_CrtDumpMemoryLeaks();
	
	return 0;
}