#include <ctype.h>
#include <stdbool.h>

int calculate(char* s) {
    
    int values[512] = { 0 };
    bool signs[512] = { false };

    int i = 0;
    int n = 0;
    bool seek_operator = false;

    int value = 0;
    int sign = true;
    char c;
    while ( (c = s[i]) ) {

        if (isspace(c)) {}
        else if (c == '(') {
            values[n] = value;
            signs[n] = sign;
            sign = true;
            value = 0;
            n++;
            seek_operator = false;
        } else if (c == ')') {
            n--;
            if (!signs[n]) {
                value *= -1;
            }
            value += values[n];
            sign = true;
            seek_operator = true;
        } else if (seek_operator) {
            if (c == '-') {
                sign = false;
            }
            seek_operator = false;
        } else if (!isdigit(c)) {
            if (c == '-') {
                sign = !sign;
            }
        } else {
            int operand = 0;
            do {
                operand = operand * 10 + (c - '0');
                c = s[++i];
            } while ( isdigit(c) );
            i--;
            if (!sign) {
                operand *= -1;
            }
            value += operand;
            sign = true;
            seek_operator = true;
        }
        i++;
    }

    return value;
}
