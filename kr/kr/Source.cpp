#include <iostream>
#include <iomanip>

using namespace std;

int re_3 = 0;
int im_3 = 0;
double r = 0;
double w = 0;

int number1(int a, int b)
{
	int result;
	_asm
	{
		mov eax, a
		mov ebx, b
		xor ecx, ecx
		xor edx, edx
		cmp ebx, ecx
		je NULLa
		cmp eax, ecx
		jg GREATER
		jl LESS
		je NULLa
	GREATER:
		cmp ebx, ecx
		jg FIRST
		jl FOURTH
	LESS:
		cmp ebx, ecx
		jg SECOND
		jl THIRT
	FIRST:
		mov edx, 1
		jmp END
	SECOND:
		  mov edx, 2
		  jmp END
	 THIRT:
		 mov edx, 3
	     jmp END
	FOURTH:
	    mov edx, 4
		jmp END
	NULLa:
		mov edx, 0
	END:
	mov result, edx
	}
	return result;
}

void number2(int re_1, int im_1, int re_2, int im_2)
{
	_asm
	{
		mov eax, re_1
		mov ecx, re_2
		sub eax, ecx
		mov re_3, eax
		mov eax, im_1
		mov ecx, im_2
		sub eax, ecx
		mov im_3, eax

	}

}

void number3(double re_4, double im_4)
{
	_asm
	{
		fld im_4
		fmul st(0), st(0)
		fld re_4
		fmul st(0), st(0)
		fadd st(0), st(1)
		fsqrt 
		fst r
		fld re_4
		fld im_4
		fpatan 
		fstp w
	}
}

void number4(int** matrix, int** resultM)
{
	_asm
	{
		    xor edx, edx
			mov edx, 2
			mov ecx, matrix
			mov esi, [ecx]
			mov ebx, resultM
			mov edi, [ebx]
		cycle:

			push edx
			mov eax, [ecx]
			mov ebx, [edx]
			mul  ebx
			inc ecx
			inc edi
			mov eax, [ecx]
			mov ebx, [edx]
			mul  ebx
			dec ecx
			dec edi
			pop edx
			dec edx
			cmp edx, 0
			jne cycle 
			
	}
}

void main()
{
	int value1;
	int value2;
	cout << "Enter values: " << endl;
	cin >> value1;
	cin >> value2;
	cout << "Result: " << number1(value1, value2)<< endl;

	int re_1;
	int im_1;
	int re_2;
	int im_2;
	cin >> re_1;
	cin >> im_1;
	cin >> re_2;
	cin >> im_2;
	number2(re_1, im_1, re_2, im_2);
	cout << re_3;
	if (im_3 >= 0)
		cout << "+";
	cout << im_3 << "i" << endl;

	double re_4;
	double im_4;
	cin >> re_4;
	cin >> im_4;
	number3(re_4, im_4);
	cout << r <<"*(cos"<<w << "+i*sin"<<w<<")"<< endl;

	int** matrix;
	int** resultM;

	resultM = new int*[2];
	for (int i = 0; i < 2; i++)
	{
		resultM[i] = new int[2];
	}

	for (int i = 0; i < 2; i++)
	for (int j = 0; j < 2; j++)
		resultM[i][j] = 0;


	matrix = new int*[2];
	for (int i = 0; i < 2; i++)
	{
		matrix[i] = new int[2];
	}


	for (int i = 0; i < 2; i++)
	for (int j = 0; j < 2; j++)
		cin >> matrix[i][j];

	for (int i = 0; i < 2; i++)
	{
		cout << "\n";
		for (int j = 0; j < 2; j++)
			cout << setw(3) << matrix[i][j] << " ";
	}
	cout << endl;

	number4(matrix, resultM);

}
