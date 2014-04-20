#include <iostream>

using namespace std;

int main()
{
	int value = 0;

	cout << "Enter the value: ";
	cin >> value;

	int sum = 0;

	_asm
	{
		    mov     eax, value
			mov     ebx, 2
		    xor     edx, edx
		    div     ebx
			mov     ebx, eax // counter
			xor     ecx, ecx // sum
	    m1: cmp     ebx, 0
			je      m3
			xor     edx, edx
			mov     eax, value
			div     ebx			 
			cmp     edx, 0
			je      m2
			dec     ebx
			jmp     m1
		m2: add     ecx, ebx
			dec     ebx
			jmp     m1
		m3: mov     sum, ecx
	}

	if (value == sum)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
	
	return 0;
}