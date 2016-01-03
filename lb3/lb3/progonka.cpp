#include "progonka.h"
#include <Windows.h>

progonka::progonka()
{
	//create an empty matrix
	cout << "Enter size matrix\n";
	cin >> NMax;
	Func = new float[NMax];
	Matrix = new float*[NMax];
	for (int i = 0; i < NMax; i++)
		Matrix[i] = new float[NMax];
	for (int i = 0; i < NMax; i++)
	{
		Func[i] = 0;
		for (int j = 0; j < NMax; j++)
			Matrix[i][j] = 0;
	}
	//it should fill us values
	float a, b, c, d;
	cout << "M[0][0], M[0][1], F[0]\n";
	cin >> b >> c >> d;
	Func[0] = d;
	Matrix[0][0] = b;
	Matrix[0][1] = c;
	for (int i = 1; i < NMax - 1; i++)
	{
		cout << "M[" << i << "][" << i - 1 << "], M[" << i << "][" << i << "], M[" << i << "][" << i + 1 << "], F[" << i << "]\n";
		cin >> a >> b >> c >> d;
		Func[i] = d;
		Matrix[i][i - 1] = a;
		Matrix[i][i] = b;
		Matrix[i][i + 1] = c;
	}
	cout << "M[" << NMax - 1 << "][" << NMax - 2 << "], M[" << NMax - 1 << "][" << NMax - 1 << "], F[" << NMax - 1 << "]\n";
	cin >> a >> b >> d;
	Func[NMax - 1] = d;
	Matrix[NMax - 1][NMax - 2] = a;
	Matrix[NMax - 1][NMax - 1] = b;
}


void progonka::calculate(rect R, float**  &matrix, float* &func, int max)
{
	bool flag1 = (R.start>0); 
	// move down 
	// in each line multiply all the elements on koef
	// that the first significant plot in a row = first significant in next line 
	// subtract from the previous next
	for (int i = R.start + 1; i < R.end; i++)
	{
		func[i] -= func[i - 1] * matrix[i][i - 1] / matrix[i - 1][i - 1];
		matrix[i][i] -= matrix[i - 1][i] * matrix[i][i - 1] / matrix[i - 1][i - 1];
		//special case when the start area does not match with the beginning of the matrix
		if (flag1) matrix[i][R.start - 1] -= matrix[i - 1][R.start - 1] * matrix[i][i - 1] / matrix[i - 1][i - 1];
		matrix[i][i - 1] = 0;
	}
	bool flag2 = (R.end < max);
	func[R.end - 1] /= matrix[R.end - 1][R.end - 1];
	//special cases when the start / end areas does not coincide with the start / end of the matrix
	if (flag1) matrix[R.end - 1][R.start - 1] /= matrix[R.end - 1][R.end - 1];
	if (flag2) matrix[R.end - 1][R.end] /= matrix[R.end - 1][R.end - 1];
	//move up
	//each line multiply all the elements on this koýf
	//which last significant in a row plot = last significant in the next line plot
	//subtract from the next previous
	matrix[R.end - 1][R.end - 1] = 1;
	for (int i = R.end - 2; i >= R.start; i--)
	{
		func[i] -= func[i + 1] * matrix[i][i + 1];
		func[i] /= matrix[i][i];
		//special cases when the start / end areas does not coincide with the start / end of the matrix
		if (flag1)
		{
			matrix[i][R.start - 1] -= matrix[i + 1][R.start - 1] * matrix[i][i + 1];
			matrix[i][R.start - 1] /= matrix[i][i];
		}
		if (flag2)
		{
			matrix[i][R.end] -= matrix[i + 1][R.end] * matrix[i][i + 1];
			matrix[i][R.end] /= matrix[i][i];
		}
		matrix[i][i] = 1;
		matrix[i][i + 1] = 0;
	}
}

void progonka::problematic_dots(rect R1, rect R2)//if the matrix is divided into sections
// arise as a result of computing column values beyond areas
{
	// solution is unnecessary values around the point of contact
	Matrix[R1.end - 1][R1.end - 1] -= Matrix[R1.end][R1.end - 1] * Matrix[R1.end - 1][R1.end] / Matrix[R1.end][R1.end];
	if (R2.end < NMax)
	{
		Matrix[R1.end - 1][R2.end] -= Matrix[R1.end][R2.end] * Matrix[R1.end - 1][R1.end] / Matrix[R1.end][R1.end];
		Matrix[R1.end - 1][R2.end] /= Matrix[R1.end - 1][R1.end - 1];
	}
	Func[R1.end - 1] -= Func[R1.end] * Matrix[R1.end - 1][R1.end] / Matrix[R1.end][R1.end];
	Func[R1.end - 1] /= Matrix[R1.end - 1][R1.end - 1];
	Matrix[R1.end - 1][R1.end - 1] = 1;
	Matrix[R1.end - 1][R1.end] = 0;
	Func[R1.end] -= Func[R1.end - 1] * Matrix[R1.end][R1.end - 1] / Matrix[R1.end - 1][R1.end - 1];
	Func[R1.end] /= Matrix[R1.end][R1.end];
	Matrix[R1.end][R2.end] -= Matrix[R1.end - 1][R2.end] * Matrix[R1.end][R1.end - 1] / Matrix[R1.end - 1][R1.end - 1];
	Matrix[R1.end][R2.end] /= Matrix[R1.end][R1.end];
	Matrix[R1.end][R1.end - 1] = 0;
	Matrix[R1.end][R1.end] = 1;
	// solution columns right and left sections (manipulation of strings)
	for (int i = 0; i < R1.end; i++)
	{
		Func[i] -= Func[R1.end] * Matrix[i][R1.end] / Matrix[R1.end][R1.end];
		Matrix[i][R2.end] -= Matrix[R1.end][R2.end] * Matrix[i][R1.end] / Matrix[R1.end][R1.end];
		Matrix[i][R1.end] = 0;
	}
	for (int i = R1.end + 1; i < R2.end; i++)
	{
		Func[i] -= Func[R1.end - 1] * Matrix[i][R1.end - 1] / Matrix[R1.end - 1][R1.end - 1];
		Matrix[i][R2.end] -= Matrix[R1.end - 1][R2.end] * Matrix[i][R1.end - 1] / Matrix[R1.end - 1][R1.end - 1];
		Matrix[i][R1.end - 1] = 0;
	}
}

DWORD __stdcall calc(void* arg)
{
	cell &a = *(cell*)arg;
	progonka::calculate(a.r, a.matrix, a.func, a.max);
	return 0;
}

// split into streams
void progonka::calculate()
{
	vector<cell> a;
	unsigned int threads = 3;
	// partitioning the matrix into rectangular plot
	for (unsigned i = 0; i < threads; i++)
	{
		rect R = { i*NMax / threads, (i + 1)*NMax / threads };
		float** &m = Matrix;
		float* &f = Func;
		a.push_back({ R, m, f, NMax });
	}
	// calculating flows of these sites tridiagonal matrix algorithm
	HANDLE hThreads[16] = { 0 };
	for (unsigned int i = 0; i < threads; i++)
	{
		DWORD threadId = 0;
		hThreads[i] = CreateThread(nullptr, 0, calc, (void*)&a[i], 0, &threadId);
	}
	WaitForMultipleObjects(threads, hThreads, true, INFINITE);
	// compute problematic points which were formed in places touching the broken rectangles
	for (unsigned int i = 1; i < threads; i++)
		problematic_dots(a[i - 1].r, a[i].r);
	for (int i = 0; i < NMax; i++)
		cout << Func[i] << ' ';
	cout << endl;
}

// output matrix
void progonka::print()
{
	for (int i = 0; i < NMax; i++)
	{
		for (int j = 0; j < NMax; j++)
		{
			cout.width(6);
			cout << Matrix[i][j] << ' ';
		}
		cout << Func[i] << endl;
	}
	cout << endl;
}