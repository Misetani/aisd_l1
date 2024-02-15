#include "stdio.h"

#include "../functions.h"

using namespace std;

int main() {
    int number = 9;
    double number2 = 9.0;
    
    printf("The square of %-3d is %-d\n", number, square(number));
    printf("The square of %-.1f is %-.1f\n", number2, square(number2));

    return 0;
}