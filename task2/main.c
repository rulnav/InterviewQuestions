#include <stdio.h>

int i = 0;
int main( ){
    ++i;
    i <= 100 && (
    (i % 3 == 0 && i % 5 == 0 && printf("AB ")) ||
    (i % 3 == 0 && printf("A ")) ||
    (i % 5 == 0 && printf("B ")) ||
    printf("%d ", i)) && 
    main();
    return 0;
}
