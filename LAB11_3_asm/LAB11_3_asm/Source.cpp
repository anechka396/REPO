#include <iostream>
#include <iomanip>

using namespace std;

void main()
{
	int n, m;
	cout << "Enter the size of matrix" << endl;
	cout << "m = ";
	cin >> m;
	cout << "n = ";
	cin >> n;
	int** matrix;


	matrix = new int*[m];
	for (int i = 0; i < m; i++)
	{
		matrix[i] = new int[n];
	}


	for (int i = 0; i < m; i++)
	for (int j = 0; j < n; j++)
		cin >> matrix[i][j];

	for (int i = 0; i < m; i++)
	{
		cout << "\n";
		for (int j = 0; j < n; j++)
			cout << setw(3) << matrix[i][j] << " ";
	}
	cout << endl;

	int sum;

	_asm
	{
		// eax - m
		// ebx - n
		// edx - sum

		xor edx, edx
		mov eax, m
		mov edx, matrix
	start:
		dec eax		
		mov esi, [edx]
		push esi
		add edx, 4		
		cmp eax, 0
		jne start
		xor edx, edx
		xor eax, eax
		mov eax, m
	cycle:
		xor ebx, ebx
		cmp eax, 0
		je endO
		dec eax
		pop esi
	cycle2:
		cmp ebx, n
		je cycle	
		cmp ebx, eax
		jge summa
		inc ebx
		add esi, 4
		jmp cycle2
	summa:
		mov edi, [esi]
		add edx, edi
		inc ebx
		add esi, 4
		jmp cycle2
	endO:
		mov sum, edx
	}

	cout <<"Result: " << sum << endl;
}