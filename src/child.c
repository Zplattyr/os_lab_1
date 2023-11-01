#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char c;
    float f;
    char num_buf[100];
    int i = 0;
    int k = 0;
    float sum = 0;
    while (read(0, &c, 1) == 1) {
        if ((c >= '0' && c <= '9') || c == '.' || c == '-') {
            num_buf[i] = c;
            i+=1;
        }
        else {
            num_buf[i] = '\0';
            i = 0;
            f = atof(num_buf);
            sum += f;
            k+=1;
            if (k == 3) {
                write(1, &sum, sizeof(sum));
                k = 0;
                sum = 0;
            }
        }
    };

}