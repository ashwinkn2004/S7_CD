#include <stdio.h>
#include <math.h>

int main() {
    int a = 10, b = 20;
    float c = a + b * 2.5;

    if (c >= 40)
        printf("Large\n");
    else
        printf("Small\n");

    return 0;
}
