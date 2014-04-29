// The following license applies to all parts of this file.
/*************************************************
The MIT License

Copyright (c) <2008> <flexsim-dll-project contributors>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*************************************************/

/************************************************
This cpp file handles the main DLL entry point as well as connecting to
Flexsim functionality. For the most part you do not need to worry about
this file at all unless you need functionality to be executed when
the DLL is loaded. Other than that, just leave this part alone.
*************************************************/

#include "FlexsimDefs.h"

// Main DLL entry point just calls bindflexsimfunctions().
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	if(ul_reason_for_call == DLL_PROCESS_ATTACH)
		return bindflexsimfunctions();
	else return 1;
}

// Here I do DECLARATIONTYPE FLEXSIM_DEFINITION_PHASE, which allocates memory space for the flexsim function pointers
// then include flexsimfuncs.h
#undef DECLARATIONTYPE
#define DECLARATIONTYPE FLEXSIM_DEFINITION_PHASE 
#include "FlexsimFuncs.h"

