#include "Brezenhem.h"

void Brezenhem::sortPoint(POINT &firstP, POINT &secondP) //����� ����� �� � ���������
{														 //��� ���� ��� �������� ������ ���� �������
	if (firstP.x > secondP.x)
	{
		POINT temp = secondP;
		secondP = firstP;
		firstP = temp;
	}
}

vector<POINT> Brezenhem::genereteVec(POINT firstP, POINT secondP)
{
	sortPoint(firstP, secondP); //���������� �� � ���������
	int dX = secondP.x - firstP.x; //������ � �
	int dY = secondP.y - firstP.y; //������ � �
	int b = secondP.y*firstP.x - secondP.x*firstP.y; //����� �������� ����������
	int i = 0;
	if (dX > dY && dX + dY > 0) // ���� � ��� ������� ����� ��������� ���� ����
// ���� �� �
	{
		vector<POINT> vec(dX + 1); // ������ ����� ���� �����
		vec[i] = firstP;
		while (i < dX)
		{
			vec[i + 1] = vec[i];
			vec[i + 1].x++;
			if (dY > 0) // ���� ���� ���������� ���� �� ����
	//�����
				if (2 * (dY * vec[i + 1].x - dX * vec[i].y - b) - dX > 0) vec[i + 1].y++; //��������� ���������� � ��������� �������� �����
				else;
			else
	//����
				if (2 * (dY * vec[i + 1].x - dX * vec[i].y - b) - dX < 0) vec[i + 1].y--; //��������� ���������� � ��������� �������� �����
			i++;
		}
		return vec;
	}
//���� �� �
	else
	{
		if (dY > 0) //������� ��� ��������� ������� ������� ����� ��
			i = dY + 1;
		else
			i = 1 - dY;
		vector<POINT> vec(i + 1); // ������ ����� ���� �����
		i = 0;
		vec[i] = firstP;
		while (dY + i < 0 || i < dY)
		{
			vec[i + 1] = vec[i];
			if (dY > 0) // ���� ���� ���������� ���� �� ���� + calculate x
			{
				vec[i + 1].y++;
				if (2 * (dX * vec[i + 1].y - dY * vec[i].x + b) - dY > 0) vec[i + 1].x++;
			}
			else
			{
				vec[i + 1].y--;
				if (2 * (dX * vec[i + 1].y - dY * vec[i].x + b) - dY < 0) vec[i + 1].x++;
			}
			i++;
		}
		return vec;
	}
}