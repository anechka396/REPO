//Yakubenko Anna LAB8_asm

#include <iostream>

using namespace std;

int main()
{
	int a = 0;
	int b = 0;
	int res = 0;
	cout << "Enter the first value: ";
	cin >> a;
	cout << "Enter the second value: ";
	cin >> b;
	_asm
	{
		mov  eax, a
		add  eax, b
		mov  res, eax
	}
	cout << "The rsult of sum: ";
	cout << res << endl;
}