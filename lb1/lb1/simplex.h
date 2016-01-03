#include <iostream>

using namespace std;

const int nMax = 10;
const float infim = 2000000000;

struct point
{
	int L;
	int K;
};

class Simplex
{
	int N;
	int M;
	int basicx[nMax];//numbers array of basic variables
	int otherx[nMax];//numbers array of other variables
	float matrix[nMax][nMax];
public:
	Simplex();
	~Simplex(){}
	void findSolution();
private:
	//rebuilding matrix
	void ñhangeTheRules(point mainElem);
	//Find items in respect of which rebuilding
	point checkAdmissibility();
	point checkOptimality();
};
