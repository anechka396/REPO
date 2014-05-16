#include <iostream>

using namespace std;

const int two = 2;
const int four = 4;

void main()
{
	int value;
	cout << "Enter the value: ";
	cin >> value;
	int* arr;
	int n;
	cout << "Enter the size of array: ";
	cin >> n;
	cout << "Enter the elements of array: " << endl;
	arr = new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	int index;
	_asm
	{
		mov esi, arr
		mov edi, esi
		mov ecx, n
		mov ebx, 0
	START:
		mov eax, ecx
		add eax, ebx
		xor edx, edx
		div two
		push eax
		mul four
		mov edi, esi
		add edi, eax
		mov edx, [edi]
		pop eax
		cmp edx, value
		jl LESS
		cmp edx, value
		jg GR
		cmp edx, value
		je EQUAL
	LESS :
	    mov edi, ecx
		sub edi, ebx
		cmp edi, 1
		je FAILEND
		cmp ebx, ecx
		jg FAILEND
		mov ebx, eax
		jmp START
	GR :
		mov edi, ecx
		sub edi, ebx
		cmp edi, 1
		je FAILEND
		cmp ebx, ecx
		jg FAILEND
		mov ecx, eax
		jmp START
	FAILEND :
		cmp edx, value
		jg END
		inc eax
		jmp END
	EQUAL :
		sub edi, four
		mov edx, [edi]
		cmp edx, value
		jne END
		mov ecx, eax
		jmp START
	END :
		mov index, eax
	}
	cout <<"Index: " << index << endl;
	delete[]arr;
}