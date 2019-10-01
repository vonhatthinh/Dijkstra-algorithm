#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string>
using namespace std;
#define MAX 10000
#define vocuc INT_MAX
int a[MAX][MAX];
int findsubstr(const char *str, char *sub);
void findEdges(char* Lines, int &Origin, int &Destin, int &Weight);
int CheckArray(int *a, int x);
void Doc_Dothi(char filename[], int a[MAX][MAX], int &n);
void Xuat_Matran(int a[][MAX], int n);
int Dijkstra(FILE *output, int a[][MAX], int n, int s, int e);
int findsubstr(const char *str, char *sub)
{
	const char *p = str;
	int len = strlen(sub);
	while (*p != NULL)
	{
		if (strlen(p) >= len)
		{
			if (strncmp(p, sub, strlen(sub)) == 0)
			{
				return (p - str);
			}
		}
		else
		{
			break;
		}
		p++;
	}
	return -1;
}
void findEdges(char* Lines, int &Origin, int &Destin, int &Weight)
{
	int Check, j = 0, Flag[3], x = 0;
	char temp1[7], temp2[7], temp3[7];
	if (findsubstr(Lines, "CREATE") != -1) Check = 1;
	if (findsubstr(Lines, "DELETE") != -1) Check = 2;
	if (findsubstr(Lines, "SP") != -1) Check = 3;
	for (int i = 0; i < strlen(Lines); i++)
	if (Lines[i] == ' ')
	{
		Flag[x] = i;	x++;
	}
	if (Check != 1) Flag[2] = strlen(Lines);
	for (int i = Flag[0] + 1; i < Flag[1]; i++)
		temp1[j++] = Lines[i];
	j = 0;
	Origin = atoi(temp1);
	for (int i = Flag[1] + 1; i < Flag[2]; i++)
		temp2[j++] = Lines[i];
	j = 0;
	Destin = atoi(temp2);
	if (Check == 1)
	{
		for (int i = Flag[2] + 1; i < strlen(Lines); i++)
			temp3[j++] = Lines[i];
	}
	Weight = atoi(temp3);
}
int CheckArray(int *a, int x)
{
	for (int i = 0; i < MAX; i++) if (a[i] == x) return 1;
	return 0;
}
void Doc_Dothi(char filename[], int a[MAX][MAX], int &n) {
	FILE *f;
	int Trash = 0;
	int x[MAX], Index = 0;
	FILE *output;
	output = fopen("output.txt", "w");
	char temp[20];
	n = 0;
	f = fopen(filename, "rt");
	if (f == NULL) {
		printf("Loi mo file !!!\n");
		printf("co the ban chon duong dan ko dung, vd: e:\\dothi.txt \n\n");
	}
	while (!feof(f))
	{
		int Origin, Destin, Weight;
		fgets(temp, 100, f);
		printf("%s", temp);
		if (findsubstr(temp, "CREATE") != -1)
		{
			findEdges(temp, Origin, Destin, Weight);
			if (a[Origin][Destin] == 0)
			{
				a[Origin][Destin] = Weight;
				fputs("1\n", output);
				x[Index++] = Origin;
				x[Index++] = Destin;
			}
			else fputs("0\n", output);
		}
		if (findsubstr(temp, "DELETE") != -1)
		{
			findEdges(temp, Origin, Destin, Weight);
			if (a[Origin][Destin] != 0)
			{
				a[Origin][Destin] = 0;
				fputs("1\n", output);
			}
			else	fputs("0\n", output);
		}
		if (findsubstr(temp, "SP") != -1)
		{
			findEdges(temp, Origin, Destin, Weight);
			if (Dijkstra(output, a, n, Origin, Destin) == 1)
			{
				Trash++;
			}
			else
				fputs("-1\n", output);
		}
	}
	fclose(f);
}
void Xuat_Matran(int a[][MAX], int n)
{
	int temp = 0;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
		{
			if (a[i][j] != 0)
			{
				printf("%d %d %d\n", i, j, a[i][j]);
				temp++;
			}
		}
	}
	printf("\n%d\n", temp);
	printf("\n");
}
int Dijkstra(FILE *output, int a[][MAX], int n, int s, int e) {
	int Mark[MAX], d[MAX], pr[MAX], min, dem, Trash = 0;
	n = MAX;
	for (int i = 0; i < n; i++)
	{
		d[i] = vocuc;
		Mark[i] = 0;
		pr[i] = s;
	}
	for (int j = 0; j<n; j++) {
		if (a[s][j])
			d[j] = a[s][j];
	}
	d[s] = 0;
	Mark[s] = 1;
	dem = n - 1;
	while (dem>0) {
		min = vocuc;
		int k = -1;
		for (int i = 0; i < n; i++)
		if ((Mark[i] == 0) && (d[i] < min))
		{
			min = d[i];
			k = i;
		}
		if (k == -1 || k == e)
			break;
		Mark[k] = 1;
		for (int j = 0; j < n; j++)
		if (Mark[j] == 0)
		if (d[k] + a[k][j]<d[j])
		if (a[k][j]>0)
		{
			d[j] = d[k] + a[k][j];
			pr[j] = k;
		}
		dem--;
	}
	int i = e;
	if (i != s)
	if (d[i] == vocuc)
	{
		Trash++; return 0;
	}
	else {
		int mang[MAX];
		dem = 0;
		int tam = pr[i];
		while (tam != s) {
			mang[dem] = tam;
			tam = pr[tam];
			dem++;
		}
		fprintf(output, "%d\n%d ", d[e], s);
		for (int j = dem; j > 0; j--)
		{
			fprintf(output, "%d\n", mang[j - 1]);
			fprintf(output, "%d ", mang[j - 1]);
		}
		fprintf(output, "%d\n", i);
	}
	fclose(output);
	return 1;
}
int main(int argc, const char * argv[])
{
	int n, s, e;
	char* duongdan, kt;
	duongdan = "test.txt";
	Doc_Dothi(duongdan, a, n);
	system("pause");
	return 0;
}



