#include <iostream>

using namespace std;

//structure cell of line array
struct simpleCell
{
	simpleCell* leftLink;
	simpleCell* rightLink;
	int data;
	int index;
};

class line
{
public:
	// constructors
	line();
	line(int n);
	line(int n, int m);
	
	~line();
	int& operator[](int n);
private:
	//our line array
	simpleCell* deque;
	//pointer, which helps move the array
	simpleCell* pointer;
	//dimension
	int NMax;
};

//structure line of array
struct simpleLine
{
	simpleLine* topLink;
	simpleLine* bottomLink;
	line *data;
	int index;
};

class matrix
{
public:
	//constructors
	matrix();
	matrix(int n, int m);
	matrix(int n, int m, int k);
	
	line& operator[](int n);
	~matrix();
private:
	//our array
	simpleLine* sqeare;
	//pointer, which helps move the array
	simpleLine* pointer;
	//dimension
	int NMax;
	int MMax;
};