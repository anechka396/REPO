#include <iostream>
using namespace std;

int main()
{
	int n = 0;
	double x = 0;

	cout << "Enter the n: ";
	cin >> n;
	cout << "Enter the x: ";
	cin >> x;

	double one = 1;
	double two = 2;
	double null = 0.5;

	double res=0;

	_asm
	{		
		mov eax, -1
		fld1      // st(6) - count
		fldz      // st(5) - temp
		fld1      // st(4) - i!
		fld1      // st(3) - 2i!
		fld1      // st(2) - x^(2i)
		fld null  // st(1) - sum
		fldz      // st(0)
		
	start:
		fadd st(1), st(0)
		fsub st(0), st(0)
		fadd one
		inc eax

		// i!
		fmul st(0), st(6)
		fmul st(4), st(0) 
		fdiv st(0), st(0) 
		
		// (2*i)!
		fmul two
		fmul st(3), st(0)
		fsub one
		fmul st(3), st(0)
		fdiv st(0), st(0)
		
		// 2^(2*i)
		fmul x
		fmul st(2), st(0)
		fmul st(2), st(0)
		fsub st(0), st(0)
		
		// (i! + (2*i)!)
		fadd st(0), st(4)
		fadd st(0), st(3)
		fxch st(5)

		// 2^(2*i) /  (i! + (2*i)!)
		fsub st(0), st(0)
		fadd st(0), st(2)
		fdiv st(0), st(5)
		
		cmp eax, n
		jne start

		fsub st(0), st(0)
		fadd st(0), st(1)
		fst res;
	}

	cout << "Result: " << res << endl;
	return 0;
}