#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_ERR 5
static char *p[] = { "",
" zle dane",
" otwarcie pliku",
" brak pamieci",
" Usage : ",
" nie ma ",
};

void error(int nr, char *str)
{
	int k;
	k = nr >= MAX_ERR ? MAX_ERR : nr;
	fprintf(stderr, "Blad(%d) -  %s %s\n", nr, p[k], str);
	system("pause");
	exit(nr);
}

double **DajMac(int n, int m)
{
	int i = 0;
	double **ma;
	if (!(ma = (double**)malloc((unsigned)n * sizeof(double*)))) error(2, "macierz");
	for (i = 0; i<n; i++)
		if (!(ma[i] = (double*)malloc((unsigned)m * sizeof(double)))) error(2, "macierz");
	return ma;

}

double *DajMac1(int m)
{
	int i;
	double *ma1;
	if (!(ma1 = (double*)malloc((unsigned)m * sizeof(double)))) error(2, "wektor x");
	return ma1;
}


void CzytMac(FILE *fd, double **ma, int n, int m)
{
	int i, j;

	for (i = 0; i<n; i++)
		for (j = 0; j < m; j++)
		{
			if(!(fscanf(fd, "%lf", &ma[i][j]))) error(1, "nie wprowadzono liczby");
			if (i == j)
			{
				if (ma[i][j] == 0) error(1, "elementy na glownej przekatnej nie moga byc 0");
			}
		}

}

void CzytMac1(FILE *fd, double*ma, int n)
{
	int i;
	for (i = 0; i<n; i++)
		if(!(fscanf(fd, "%lf", &ma[i]))) error(1, "nie wprowadzono liczby");
}

void PiszMac(FILE *fw, double **ma, int n, int m)
{
	int i, j;
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<m; j++)
			fprintf(fw, "%lf ", ma[i][j]);
		fprintf(fw, "\n");
	}

}

void PiszMac_1(FILE *fw, double *ma, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		//fprintf(fw, "x%d ", i);
		fprintf(fw, "%lf ", ma[i]);
		fprintf(fw, "\n");
	}
}

void ZwrocMac_1(double **a, int n)
{
	int i = 0;
	for (i = 0; i<n; i++)
		free(a[i]);
	free(a);
}


double zwroc_d(double **l, double **d, double**u, int i)
{
	int k;
	double suma = 0;
	for (k = 0; k <= i - 1; k++)
	{
		suma += l[i][k] * u[k][i] * d[k][k];
	}
	return suma;
}

double zwroc_l(double **l,double **d, double **u,int i, int j)
{
	int k;
	double suma = 0;
	for (k = 0; k <= j - 1; k++)
	{
		suma += l[i][k] * u[k][j] * d[k][k];
	}
	return suma;
}

double zwroc_u(double **l, double **d, double **u, int i, int  j)
{
	int k;
	double suma = 0;
	for (k = 0; k <= i - 1; k++)
	{
		suma += l[i][k] * u[k][j] * d[k][k];
	}
	return suma;
}

void diagonalna(double **d, double **l, double **u, double **a, int n, int m )
{
	int i, j;

	for (i = 0; i < n; i++)// macierz diagonalna
	{
		for (j = 0; j < m; j++)
		{
			if (i == 0 && j == 0)
			{
				d[i][j] = a[i][j];
			}
			else
				if (i == j && i != 0 && j != 0)
				{

					d[i][j] = a[i][j] - zwroc_d(l, d, u, i);
					if (d[i][j] == 0) error(5, "rozwiazania");
					
				}
				else
				{
					d[i][j] = 0;
				}
		}
	}
}



void macierze(FILE *fd, double **a, double **l, double **d, double**u, int n, int m)
{
	int i, j;
	double r;
	d[0][0] = a[0][0];

	for (i = 0; i < n; i++) // macierz trojkatna dolna
	{
		for (j = 0; j < m; j++)
		{
			if (j < i)
			{
				l[i][0] =  a[i][0] / d[0][0];
				
			}
			else
			if (i == j)
			{
				l[i][j] = 1;
			}
			else
			{
				l[i][j] = 0;
			}

		}
	}


	for (i = 0; i < n; i++) // macierz trojkatna gorna
	{
		for (j = 0; j < m; j++)
		{
			if (j > i)
			{
				u[0][j] = a[0][j] / d[0][0];

			}
			else
				if (i == j)
				{
					u[i][j] = 1;
				}
				else
				{
					u[i][j] = 0;
				}

		}
	}
	diagonalna(d,l,u, a, n, m);
	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (i > j && j > 0)
			{
				l[i][j] = (a[i][j] - zwroc_l(l, d, u, i,j))/ d[j][j];
			}
			if (i > 0 && j > i)
			{
				u[i][j] = (a[i][j] - zwroc_u(l, d, u, i, j)) / d[i][i];
			}
			if (i == j)
			{
				diagonalna(d, l, u, a, n, m);
			}
		}
	}
}

double zwroc_y(double **l, double *y, int i)
{
	int k;
	double suma = 0;
	for (k = 0; k <= i - 1; k++)
	{
		suma += l[i][k] * y[k];
	}
	return suma;
}

double zwroc_x(double **u, double *x, int i, int n)
{
	int k;
	double suma = 0;
	for (k = i + 1; k <= n; k++)
	{
		suma += u[i][k] * x[k];
	}
	return suma;
}

void rozwiazania(double **l, double **d, double **u,double *b, double *x, int m)
{
	double *y, *z;
	
	y = DajMac1(m);
	z = DajMac1(m);

	int i;
	y[0] = b[0];

	for (i = 1; i < m; i++)
	{
			y[i] = b[i] - zwroc_y(l, y, i);	
	}

	for (i = 0; i < m; i++)
	{
		z[i] = y[i] / d[i][i];
		x[m - 1] = z[m - 1];
	}

	for (i = m-2; i >= 0; i--)
	{
		x[i] = z[i] - zwroc_x(u, x, i, m);
	}


	free(y);
	free(z);

}

