#pragma once

int hailstone(int n) {
	int length = 1;
	while (1 < n)
	{
		(n % 2) ? n = 3 * n + 1 : n /= 2;
		length++;
	}
	return length;
}	
