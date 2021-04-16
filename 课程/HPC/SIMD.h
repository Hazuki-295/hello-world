#include "stdio.h"
#include <xmmintrin.h> // Need this for SSE compiler intrinsics
#include <math.h> // Needed for sqrt in CPU-only version
#include <time.h>
void Division();
void Fast();

int SIMD_Test()
{

	Division();
	printf("\n");
	Fast();	
	return 0;

}

void division()
{
	printf("Starting calculation...\n");
	const int length = 64000;
	// We will be calculating Y = SQRT(x) / x, for x = 1->64000
	// If you do not properly align your data for SSE instructions, you may take a huge performance hit.
	float *pResult = (float *)_aligned_malloc(length * sizeof(float), 16); // align to 16-byte for SSE
	__m128 x;
	__m128 xDelta = _mm_set1_ps(4.0f); // Set the xDelta to (4,4,4,4) 步长
	__m128 *pResultSSE = (__m128 *) pResult;
	const int SSELength = length / 4;


#define TIME_SSE // Define this if you want to run with SSE
#ifdef TIME_SSE
	clock_t clock1 = clock();
	// lots of stress loops so we can easily use a stopwatch
	for (int stress = 0; stress < 1000; stress++)//重复一千次
	{
		// Set the initial values of x to (4,3,2,1)
		x = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);//初始值
		for (int i = 0; i < SSELength; i++)//做64000/4次运算
		{
			__m128 xSqrt = _mm_sqrt_ps(x);
			// Note! Division is slow. It's actually faster to take the reciprocal of a number and multiply
			// Also note that Division is more accurate than taking the reciprocal and multiplying
			//注意！除法运算是很慢的。事实上把数转换成倒数再相乘会更快。还要注意，除法比取倒数再乘更精确。
			#define USE_DIVISION_METHOD
			//#define USE_FAST_METHOD
			//#ifdef USE_FAST_METHOD//如果使用快速的方法，此处未使用
			//			__m128 xRecip = _mm_rcp_ps(x);
			//			pResultSSE[i] = _mm_mul_ps(xRecip, xSqrt);//乘法指令
			//#endif USE_FAST_METHOD
			#ifdef USE_DIVISION_METHOD//使用除法
						pResultSSE[i] = _mm_div_ps(xSqrt, x);//除法指令
			#endif  USE_DIVISION_METHOD
						// Advance x to the next set of numbers
						x = _mm_add_ps(x, xDelta);//加法指令，x += xDelta;
		}
	}
	clock_t clock2 = clock();
	printf("Division:\n");
	printf("SIMDtime:%d ms\n", 1000 * (clock2 - clock1) / CLOCKS_PER_SEC);
#endif // TIME_SSE

#define TIME_NoSSE
#ifdef TIME_NoSSE
	clock_t clock3 = clock();
	// lots of stress loops so we can easily use a stopwatch
	for (int stress = 0; stress < 1000; stress++)
	{
		float xFloat = 1.0f;
		for (int i = 0; i < length; i++)
		{
			/* Even though division is slow, there are no intrinsic functions//尽管除法是缓慢的，这里没有像SSE一样有内部函数。
			like there are in SSE */
				pResult[i] = sqrt(xFloat) / xFloat;
			xFloat += 1.0f;
		}
	}
	clock_t clock4 = clock();
	printf("noSIMDtime:%d ms\n", 1000 * (clock4 - clock3) / CLOCKS_PER_SEC);
#endif // TIME_noSSE
	return;
}

void Fast()
{
	printf("Starting calculation...\n");
	const int length = 64000;
	// We will be calculating Y = SQRT(x) / x, for x = 1->64000
	// If you do not properly align your data for SSE instructions, you may take a huge performance hit.
	float *pResult = (float *)_aligned_malloc(length * sizeof(float), 16); // align to 16-byte for SSE
	__m128 x;
	__m128 xDelta = _mm_set1_ps(4.0f); // Set the xDelta to (4,4,4,4) 步长
	__m128 *pResultSSE = (__m128 *) pResult;
	const int SSELength = length / 4;

#define TIME_SSE // Define this if you want to run with SSE
#ifdef TIME_SSE
	clock_t clock1 = clock();
	// lots of stress loops so we can easily use a stopwatch
	for (int stress = 0; stress < 1000; stress++)//重复一千次
	{
		// Set the initial values of x to (4,3,2,1)
		x = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);//初始值
		for (int i = 0; i < SSELength; i++)//做64000/4次运算
		{
			__m128 xSqrt = _mm_sqrt_ps(x);
			// Note! Division is slow. It's actually faster to take the reciprocal of a number and multiply
			// Also note that Division is more accurate than taking the reciprocal and multiplying
			//注意！除法运算是很慢的。事实上把数转换成倒数再相乘会更快。还要注意，除法比取倒数再乘更精确。
			//#define USE_DIVISION_METHOD
			#define USE_FAST_METHOD
			#ifdef USE_FAST_METHOD//如果使用快速的方法
						__m128 xRecip = _mm_rcp_ps(x);
						pResultSSE[i] = _mm_mul_ps(xRecip, xSqrt);//乘法指令
			#endif USE_FAST_METHOD
			//#ifdef USE_DIVISION_METHOD//使用除法 
			//			pResultSSE[i] = _mm_div_ps(xSqrt, x);//除法指令
			//#endif  USE_DIVISION_METHOD
			// Advance x to the next set of numbers
			x = _mm_add_ps(x, xDelta);//加法指令，x += xDelta;
		}
	}
	clock_t clock2 = clock();
	printf("Fast:\n");
	printf("SIMDtime:%d ms\n", 1000 * (clock2 - clock1) / CLOCKS_PER_SEC);
#endif // TIME_SSE

#define TIME_NoSSE
#ifdef TIME_NoSSE
	clock_t clock3 = clock();
	// lots of stress loops so we can easily use a stopwatch
	for (int stress = 0; stress < 1000; stress++)
	{
		float xFloat = 1.0f;
		for (int i = 0; i < length; i++)
		{
			/* Even though division is slow, there are no intrinsic functions//尽管除法是缓慢的，这里没有像SSE一样有内部函数。
			like there are in SSE */
			pResult[i] = sqrt(xFloat) / xFloat;
			xFloat += 1.0f;
		}
	}
	clock_t clock4 = clock();
	printf("noSIMDtime:%d ms\n", 1000 * (clock4 - clock3) / CLOCKS_PER_SEC);
#endif // TIME_noSSE
	return;
}