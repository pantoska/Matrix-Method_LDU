// projekt3.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#pragma warning (disable: 4996)
#pragma warning (disable: 4244)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *fd;
FILE *fw;

void argumenty(int, char **);
extern void error(int nr, char *str);
extern double **DajMac(int n, int m);
extern void CzytMac(FILE *fd, double **ma, int n, int m);
extern void CzytMac1(FILE *fd, double*ma, int n);
extern void PiszMac(FILE *fw, double **ma, int n, int m);
extern void macierze(FILE *fd, double **a, double **l, double **d, double**u, int n, int m);
extern void ZwrocMac_1(double **, int);
extern double *DajMac1(int);
extern void rozwiazania(double **l, double **d, double **u, double *b, double *x, int m);
extern void PiszMac_1(FILE *fw, double *ma, int n);


int main(int argc, char *argv[])
{
	double **a, **l, **d, **u, *b, *x;
	int i, j, k, n, m;

	argumenty(argc, argv);

	if (!(fd = fopen(argv[1], "r"))) error(2, "dane.txt");
	if (!(fw = fopen(argv[2], "w"))) error(2, "wyniki.txt");

	//printf("podaj wymiary macierzy\n");
	//scanf("%d %d", &n, &m);
	if(!(fscanf(fd, "%d %d", &n, &m))) error(1, "nie wprowadzono liczby");
	
	if (n != m) error(1, "wymiary");

	a = DajMac(n, m);
	l = DajMac(n, m);
	d = DajMac(n, m);
	u = DajMac(n, m);

	b = DajMac1(m);
	x = DajMac1(m);

	CzytMac(fd, a, n, m);

	CzytMac1(fd, b, n);
	
	macierze(fd, a, l, d, u, n, m);
	
	fprintf(fw,"macierz wejsciowa\n");
	PiszMac(fw, a, n, m);
	fprintf(fw, "macierz dolna\n");
	PiszMac(fw, l,n, m);
	fprintf(fw, "macierz gorna\n");
	PiszMac(fw, u, n, m);
	fprintf(fw, "macierz diagonalna\n");
	PiszMac(fw, d, n, m);

	rozwiazania(l, d, u, b, x, m);
	
	fprintf(fw, "rozwiazania\n");
	PiszMac_1(fw, x, n);
	

	ZwrocMac_1(a, n);


	free(b);
	free(x);

	system("pause");
	return 0;
}

void argumenty(int argc, char *argv[])
{
	int len;
	char *usage;
	if (argc != 3)
	{
		len = strlen(argv[0]) + 19;
		if (!(usage = (char*)malloc((unsigned)len * sizeof(char)))) error(3, "tablica usage");
		strcpy(usage, argv[0]);
		strcat(usage, " file_in file_out");
		error(4, usage);
	}
}