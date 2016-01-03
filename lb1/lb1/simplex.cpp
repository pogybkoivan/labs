#include "simplex.h"

Simplex::Simplex()
{
	//usual constructor
	cout << "enter N (count variables)\n";
	cin >> N;
	cout << "enter M (count equations)\n";
	cin >> M;
	M++;
	cout << "enter main function\'s rates\n";
	for (int i = 0; i < N; i++)
	{
		otherx[i] = i + 1;//numbers array of basic variables
		cin >> matrix[0][i];
		matrix[0][i] = 0 - matrix[0][i];
	}
	cin >> matrix[0][N];
	otherx[N++] = 0;
	cout << "enter equations\'s rates in matrix\n";
	for (int i = 0; i < M; i++)
		basicx[i] = 0; //numbers basic array variables that do not = 0
	for (int i = 1; i < M; i++)
		for (int j = 0; j < N; j++)
			cin >> matrix[i][j];
}

void Simplex::ñhangeTheRules(point mainElem)//matrix rebuild regarding the selected item
{
	//Swap basic and 'other' variable relative to the selected item
	int c = basicx[mainElem.K];
	basicx[mainElem.K] = otherx[mainElem.L];
	otherx[mainElem.L] = c;
	//selected item change in reverse
	matrix[mainElem.K][mainElem.L] = 1 / matrix[mainElem.K][mainElem.L];

	//If the item does not have a common vertical or horizontal with the changes which take vidnostno
	//it is calculated by the formula M[i][j] = M[i][j] - (M[i][l] * M[k][j]) / M[k][l] where M[k][l] we selected element in the initial matrix 
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (i != mainElem.K && j != mainElem.L)
				matrix[i][j] = matrix[i][j] -
				(matrix[i][mainElem.L] * matrix[mainElem.K][j] * matrix[mainElem.K][mainElem.L]);

	//elements on one horizontal domnozhayutsya to the inverse of the element
	for (int i = 0; i < N; i++)
		if (i != mainElem.L)
			matrix[mainElem.K][i] *= matrix[mainElem.K][mainElem.L];
	//items not on one vertical domnozhayutsya negative inverse of
	for (int i = 0; i < M; i++)
		if (i != mainElem.K)
			matrix[i][mainElem.L] *= 0 - matrix[mainElem.K][mainElem.L];
}

point Simplex::checkAdmissibility()//check for connectivity conditions and search element against which the array rebuilt
{
	//Search smallest negative element matrix which is in a horizontal
	//with the least negative extreme right element
	point rez;
	rez.K = 0;
	rez.L = 0;
	for (int i = 1; i < M; i++)
		if (matrix[i][N - 1] - matrix[rez.K][N - 1] < -0.0001 && matrix[rez.K][N - 1] < 0) rez.K = i;
	if (!rez.K) return rez;
	for (int i = 0; i < N - 1; i++)
		if (matrix[rez.K][i] - matrix[rez.K][rez.L] < -0.0001) rez.L = i;
	if (matrix[rez.K][rez.L] > -0.0001) rez.L = 0;
	//if an item was not the result will be an element of M[0][0] 
	return rez;
}

point Simplex::checkOptimality()//check in optimal conditions and search element against which the array rebuilt
{
	//Search smallest negative attitude M[i][j] / M[i][N-1] which is one line
	//with the least negative extreme upper element
	point rez;
	rez.K = 1;
	rez.L = 0;
	for (int i = 1; i < N - 1; i++)
		if (matrix[0][i] - matrix[0][rez.L] < -0.0001 && matrix[0][rez.L] < 0) rez.L = i;
	if (matrix[0][rez.L]>-0.0001) return rez;
	float min = infim;
	for (int i = 1; i < M; i++)
		if (matrix[rez.K][i] > 0 && matrix[rez.K][N - 1] / matrix[rez.K][i] - min < -0.0001)
		{
			rez.K = i;
			min = matrix[rez.K][N - 1] / matrix[rez.K][i];
		}
	if (min - infim > -0.0001) rez.L = 0;
	//if an item was not the result will be an element of M[i][0]
	//if i = 0 then this solution
	return rez;
}

void Simplex::findSolution()
{
	//search solution
	bool flag = true; //whether to continue the search and rebuild matrix
	bool step = true; //which step search (find first solution) / (optimal solution)
	bool solution = false;//whether the solution
	point mainElem = { 0, 0 };
	while (flag)
	{
		if (step)//find first solution
		{
			mainElem = checkAdmissibility();// element against which the matrix rebuild
			if (!mainElem.K) step = false; //checking whether a given matrix is a solution and move to the next step if it's true
			else if (!mainElem.L)//check whether there is a solution at all
			{
				cout << "there is no solution\n";
				flag = false;
			}
		}
		if (!step)
		{
			mainElem = checkOptimality();//tunable element against which the matrix
			if (matrix[0][mainElem.L]>-0.0001) //checking whether a given matrix is the best solution and the search is completed if it's true
			{
				flag = false;
				solution = true;
			}
			else if (matrix[mainElem.K][mainElem.L]<-0.0001)//many solutions
			{
				cout << "function unlimited\n";
				flag = false;
			}
		}
		if (flag) ñhangeTheRules(mainElem);//whether to rebuild a matrix
	}
	if (solution) //if there is a solution to bring it
	{
		for (int i = 1; i < M; i++)
			if (basicx[i]) cout << "x" << basicx[i] << "=" << matrix[i][N - 1] << " ";
		cout << "\nother variables = 0\n";
		cout << "funcion = " << matrix[0][N - 1] << endl;
	}
}