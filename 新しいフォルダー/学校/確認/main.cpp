#include <stdio.h>

typedef struct _KEIHIN
{
    int kamata = 17;
    int yokohama = 12;
}KEIHIN;

void output(KEIHIN* keihin)
{
    printf("%d\n", keihin->kamata);
    printf("%d\n", keihin->yokohama);
}

int main()
{
    KEIHIN* keihin1 = new KEIHIN;
    KEIHIN* keihin2 = new KEIHIN;

    output(keihin1);
    output(keihin2);

    delete keihin1;
    delete keihin2;

    output(keihin1);
    output(keihin2);

    return 0;
}