// ���.��� 2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <math.h>
#define n 3
#define eps 0.01
#define step 19

using namespace std;


void output_matrix(double(&mas)[n][n])
{
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			cout << setw(14) << setprecision(11) << setfill(' ') << mas[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}//end;

void output_vector(double(&mas)[n])
{
	for (int i = 0; i < n; i++)
		cout << "[" << i + 1 << "] = " << mas[i] << endl;
	cout << endl;
}//end;


// ������� ���������
bool converge(double *xk, double *xkp)
{
	for (int i = 0; i < n; i++)
	{
		if (fabs(xk[i] - xkp[i]) >= eps)
			return false;
	}
	return true;
}



long int iteration(double alpha, double(&A)[n][n], double(&x)[n], double(&b)[n], double(&nevazka)[n])
{
	double p[n];

	for (int i = 0; i < n; i++)
	{
		x[i] = b[i];
	}

	//---���������� �������
	for (int i = 0; i < n; i++)
	{
		nevazka[i] = 0;
		for (int j = 0; j < n; j++)
			nevazka[i] = nevazka[i] + A[i][j] * x[i];
		nevazka[i] = nevazka[i] - b[i];
	}

	//---------------------�������� ��������� ��� ���� ������� �2 � �������
	double norma_nev = 0.0;
	for (int i = 0; i < n; i++)
	{
		norma_nev = norma_nev + fabs(nevazka[i]);
	}

	int k = 0; //���������� ��������
	/*
	��� ������, ���:
	a[n][n] - ������� �������������
	x[n], p[n] - ������� � ���������� �������
	b[n] - ������� ������ ������
	��� ������������� ������� ������������ �
	������ ���� ���������� � �������� ���������,
	����� � ������ x[n] ������� ��������� ���������
	����������� ������� ������� (��������, ��� ����)
	*/

	do
	{
		for (int i = 0; i < n; i++)
			p[i] = x[i];

		for (int i = 0; i < n; i++)
		{
			double var = 0;
			for (int j = 0; j < i-1; j++)
				var += (A[i][j] * x[j]);
			for (int j = i + 1; j < n; j++)
				var += (A[i][j] * p[j]);
			x[i] = (b[i] - var) / A[i][i];
		}

		//---���������� �������
		for (int i = 0; i < n; i++)
		{
			nevazka[i] = 0;
			for (int j = 0; j < n; j++)
				nevazka[i] = nevazka[i] + A[i][j] * x[i];
			nevazka[i] = nevazka[i] - b[i];
		}

		//---------------------�������� ��������� ��� ���� ������� �2 � �������
		double norma_nev = 0.0;
		for (int i = 0; i < n; i++)
		{
			norma_nev = norma_nev + fabs(nevazka[i]);
		}

		k++;
		cout << norma_nev << endl;
	} while (!converge(x,p));
	return k;
}

void display(double alpha[step], long int iterations[step])
{
	//system("cls");
	cout << "����������������������������������Ŀ\n";
	cout << "�      alpha     �    iterations   �\n";
	cout << "����������������������������������Ĵ\n";
	for (int i = 0; i < step; i++)
	{
		cout << "�" << setw(15) << alpha[i] << " � " << setw(15) << iterations[i] << " � " << endl;
		if (i < step - 1)
		{
			cout << "����������������������������������Ĵ\n";
		}
		else
		{
			cout << "������������������������������������\n";
		}

	}
}

void table(double(&A)[n][n], double(&x)[n], double(&b)[n], double(&nevazka)[n])
{
	double alpha[step];
	long int iterations[step];
	system("cls");
	alpha[0] = 0.1;
	for (int i = 1; i < step; i++)
	{
		alpha[i] = alpha[i - 1] + 0.1;
	}
	//����� �����������
	cout << setw(5) << "Results Iterations : \n";
	for (int i = 0; i < step; i++)
	{
		cout << " alpha  = " << alpha[i] << endl;
		iterations[i] = iteration(alpha[i], A, x, b, nevazka);
		cout << " x = " << endl;
		output_vector(x);
		cout << " nevazka = " << endl;
		output_vector(nevazka);
	}
	display(alpha, iterations);


}


int _tmain(int argc, _TCHAR* argv[])
{
	//double A[n][n] =
	//{
	//	{ 11, -6, 2, -2 },
	//	{ 3, 9, -1, -4 },
	//	{-1 , 2, -15, 4 },
	//	{ 7, 0, 3, 12 }
	//};

	//double x[n],
	//	nevazka[n] = { 0, 0, 0, 0 },
	//	b[n] =
	//		{-56, -22, 11, 82 };

	double A[n][n] =
	{
		{1,-0.2,0.1 },
		{ -0.1,1,0.1 },
		{ -0.3,0.2,1},
	};

	double x[n],
		nevazka[n] = { 0, 0, 0},
		b[n] =
	{ 0.4,0.8,0.2};


	output_matrix(A);

	cout  << endl << iteration(1, A, x, b, nevazka)<<endl;

	cout << " x = " << endl;
	output_vector(x);
	cout << " nevazka = " << endl;
	output_vector(nevazka);

	getchar();
	return 0;
}

