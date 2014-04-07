// лаб.раб 2.cpp: определяет точку входа для консольного приложения.
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


// Условие окончания
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

	//---вычисление невязки
	for (int i = 0; i < n; i++)
	{
		nevazka[i] = 0;
		for (int j = 0; j < n; j++)
			nevazka[i] = nevazka[i] + A[i][j] * x[i];
		nevazka[i] = nevazka[i] - b[i];
	}

	//---------------------Создание переменых для норм вектора х2 и невязки
	double norma_nev = 0.0;
	for (int i = 0; i < n; i++)
	{
		norma_nev = norma_nev + fabs(nevazka[i]);
	}

	int k = 0; //количество итераций
	/*
	Ход метода, где:
	a[n][n] - Матрица коэффициентов
	x[n], p[n] - Текущее и предыдущее решения
	b[n] - Столбец правых частей
	Все перечисленные массивы вещественные и
	должны быть определены в основной программе,
	также в массив x[n] следует поместить начальное
	приближение столбца решений (например, все нули)
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

		//---вычисление невязки
		for (int i = 0; i < n; i++)
		{
			nevazka[i] = 0;
			for (int j = 0; j < n; j++)
				nevazka[i] = nevazka[i] + A[i][j] * x[i];
			nevazka[i] = nevazka[i] - b[i];
		}

		//---------------------Создание переменых для норм вектора х2 и невязки
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
	cout << "ЪДДДДДДДДДДДДДДДДВДДДДДДДДДДДДДДДДДї\n";
	cout << "і      alpha     і    iterations   і\n";
	cout << "ГДДДДДДДДДДДДДДДДЕДДДДДДДДДДДДДДДДДґ\n";
	for (int i = 0; i < step; i++)
	{
		cout << "і" << setw(15) << alpha[i] << " і " << setw(15) << iterations[i] << " і " << endl;
		if (i < step - 1)
		{
			cout << "ГДДДДДДДДДДДДДДДДЕДДДДДДДДДДДДДДДДДґ\n";
		}
		else
		{
			cout << "АДДДДДДДДДДДДДДДДБДДДДДДДДДДДДДДДДДЩ\n";
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
	//вывод результатов
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

