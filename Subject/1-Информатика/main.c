#include <stdio.h>
#include <stdlib.h>

int main(void){
    unsigned int num;
    //scanf("%u", &num);

    srand(0);
    num = rand();

    for(int i = 31; i >= 0; i--)
        printf("%d", (num & (1 << i))>>i);
    puts("");

    int n1, n2, n3, n4;
    n1 = (((num<<0 )>>28) - ((num<<4 )>>28));
    n2 = (((num<<8 )>>28) - ((num<<12)>>28));
    n3 = (((num<<16)>>28) - ((num<<20)>>28));
    n4 = (((num<<24)>>28) - ((num<<28)>>28));

    unsigned int w1, w2, w3, w4;
    w1 = (num << 0 )>>24;
    w2 = (num << 8 )>>24;
    w3 = (num << 16)>>24;
    w4 = (num << 24)>>24;

    int i1=0, i2=0, i3=0, i4=0;
    if(n1 >= n2)i1+=1;else i2+=1;
    if(n1 >= n3)i1+=1;else i3+=1;
    if(n1 >= n4)i1+=1;else i4+=1;
    if(n2 >= n3)i2+=1;else i3+=1;
    if(n2 >= n4)i2+=1;else i4+=1;
    if(n3 >= n4)i3+=1;else i4+=1;

    unsigned int result = (w1<<i1*8) + (w2<<i2*8) + (w3<<i3*8) + (w4<<i4*8);
    for(int i = 31; i >= 0; i--)
        printf("%d", (result & (1 << i))>>i);
    puts("");
}