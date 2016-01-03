#include "matrix.h"

int main()
{
	matrix M(5, 5); // initilize empty 5*5 array 
	M[3][2] = 2; //change one value
	cout << M[-1][2] << ' ' << M[3][3] << ' ' << M[0][0] << endl;//check different value
	system("pause");
	return 0;
}