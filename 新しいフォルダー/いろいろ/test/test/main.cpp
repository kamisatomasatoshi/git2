#include <stdio.h>

int main(void)
{
	double a, b;
	printf("aを記入してください。\n");
	scanf_s("%lf", &a);
	printf("a=%lf\n", a);
	printf("bを記入してください。\n");
	scanf_s("%lf", &b);
	printf("b=%lf\n", b);

	printf("aとbの和は%lfです\n", a + b);
	printf("平均は%lfです。\n", (a + b) / 2);
	printf("a=%lf\nb=%lf\n", a, b);

	return 0;
}