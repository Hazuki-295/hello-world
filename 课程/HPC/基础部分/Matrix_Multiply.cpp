#include "stdio.h"
#include "stdlib.h"
#include "time.h"
/* Use 32x32 tiles 32*32=1024 */
/* NxN matrix */
#define TILE 32
#define N 1024

/* ����ֿ�˷� */
void multiply_tiled(double *a, double *b, double *c) 
{
	/* Loop over all the tiles, stride by tile size */
	/* �����������еĿ飬����Ĵ�Сǰ�� */
	int i, j, k, x, y, z;
	double sum;
	for (i = 0; i < N; i += TILE)
		for (j = 0; j < N; j += TILE)
			for (k = 0; k < N; k += TILE)
				/* Regular multiply inside the tiles */
				/* ÿ���ֿ��ڽ��г���ľ���˷� */
				for (x = i; x < i + TILE; x++)
					for (y = j; y < j + TILE; y++) {
						sum = c[x * N + y];
						for (z = k; z < k + TILE; z++) 
						{
							sum += a[x * N + z] * b[z * N + y];
						}
						c[x * N + y] = sum;
					}
}

int Divided_Matrix_Multiply()
{
	double *a, *b, *c;
	double sum;
	a = (double *)malloc(N * N * sizeof(double));
	b = (double *)malloc(N * N * sizeof(double));
	c = (double *)malloc(N * N * sizeof(double));

	/* ��ʼ������ */
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			a[i * N + j] = 1.0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			b[i * N + j] = 1.0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			c[i * N + j] = 0;

	time_t plainstart = time(NULL);

	/* Regular multiply */
	/* ���淽���˷� */
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			sum = c[i * N + j];
			for (int k = 0; k < N; k++)
				sum += a[i * N + k] * b[k * N + j];
			c[i * N + j] = sum;
		}
	time_t plainend = time(NULL);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			// printf("c:%d",(int)c[i*N+j]);
			c[i * N + j] = 0;
		}
	time_t optstart = time(NULL);
	multiply_tiled(a, b, c);
	time_t optend = time(NULL);
	// printf("\n");
	//printf("opt C:\n");
	//for ( int i=0; i<N; i++ )
	// for ( int j=0; j<N; j++ )
	// printf("c:%d ",(int)c[i*N+j]);
	printf("optimal multiply : %d\n", optend - optstart); // optimal ���ŷ���
	printf("plain multiply : %d\n", plainend - plainstart); // plain ��ͨ����
	free(a);
	free(b);
	free(c);
	return 0;
}