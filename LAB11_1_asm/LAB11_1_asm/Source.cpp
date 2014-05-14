//Iakubenko Anna Va
//15) В заданной строке заменить каждое слово на обратное. Слова разделяются одним или более пробелами. (например, "abc qwerty" -> "cba ytrewq") 
#include <iostream>

using namespace std;

void main()
{
	const int MAX = 256;
	char* str;
	char* newStr;
	str = new char[MAX];
	newStr = new char[MAX];
	cout << "Enter the str: ";
	cin.get(str, MAX);
	int len = strlen(str);
	_asm
	{
		xor ebx, ebx // kol-vo bukv
		xor ecx, ecx // dlina slova
		mov esi, str
		mov edi, newStr		
		mov ecx, len

		cmp ecx, 0
		je END

	START:		
		mov eax, [esi]
		cmp ecx, 0
		je END
		cmp al, ' '
		je SPACE
		push eax
		dec ecx
		inc esi
		inc ebx		
		jmp START

	SPACE:
		cmp ebx, 0
		jne OVERTURN
		dec ecx
		mov byte ptr[edi], ' '
		inc edi
		inc esi
		jmp START

	OVERTURN:
		pop eax
		mov byte ptr[edi], al
		inc edi
		dec ebx
		cmp ebx, 0
		jne OVERTURN
		cmp ecx, 0		
		je END	
		mov byte ptr[edi], ' '
		inc edi
		inc esi
		xor ebx, ebx
		dec ecx
		jmp START

	END:
		cmp ebx, 0
		jne OVERTURN
		mov byte ptr[edi], 0		
	}
	cout << "Result: " << newStr<< endl;
}