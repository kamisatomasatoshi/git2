#include <stdio.h>

int main(void)
{
	double a, b;
	printf("a���L�����Ă��������B\n");
	scanf_s("%lf", &a);
	printf("a=%lf\n", a);
	printf("b���L�����Ă��������B\n");
	scanf_s("%lf", &b);
	printf("b=%lf\n", b);

	printf("a��b�̘a��%lf�ł�\n", a + b);
	printf("���ς�%lf�ł��B\n", (a + b) / 2);
	printf("a=%lf\nb=%lf\n", a, b);

	return 0;
}