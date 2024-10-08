#include <stdio.h>
int main(int argc, char** argv) {
    int a=10;
    int b=20;
    int c=30;
    int d=40;
    printf("a=%d, b=%d, c=%d d=%d\n", a, b, c, d);
    __asm__ volatile (  
    "movl $100, %%eax\n"     // eax = 100
    "movl $200, %%ebx\n"     // ebx = 200
    "addl %%ebx, %%eax\n"    // eax += rbx
    "movl %%eax, %0\n"       // b = rax
    : "=g" (b)              //output, b的代號是"%0"
    : "g" (a), "g" (d)      //input, a代號是"%1", da代號是"%2"
    : "ebx", "eax"          //搞髒掉的暫存器，gcc會幫我們還原
    );
    printf("b = 100 + 200\n");
    printf("a=%d, b=%d, c=%d d=%d\n", a, b, c, d);
}