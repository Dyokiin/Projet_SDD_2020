#include <stdio.h>
#include <time.h>


int main(int argc, char  *argv[]) {
    long int t = time(NULL);
    printf("%ld\n", t);
    char buffer[25];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y - %X", localtime(&t));
    printf("%s\n",buffer );

    return 0;
}
