#include <iostream>
#include <vector>

using namespace std;

struct rect
{
	int start;
	int end;
};

struct cell
{
	rect r;
	float**  &matrix;
	float*  &func;
	int max;
};

class progonka
{
public:
	static void calculate(rect R, float**  &matrix, float*  &func, int max);//прогонка ділянки матриці
	progonka();
	~progonka(){}
	void calculate();//parallel prohonka entire matrix
private:
	int NMax;
	float** Matrix;//matrix
	float*  Func;//Vector mentioned lines
	void problematic_dots(rect R1, rect R2); //extra cleaning line ( rezult parallel prohonka)
	void print();
};