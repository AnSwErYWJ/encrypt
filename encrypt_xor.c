#include<stdio.h>
#include<stdlib.h>//itoa(),用来将数字转换为字符串
#define N 8
int main()
{
    char plaintext='a';//明文
    char secretkey='s';//密钥
    char ciphertext=plaintext ^ secretkey;//密文
    char decodetext=ciphertext ^ secretkey;//解密后的字符

    char buf[N];
    printf("           char    ASCII\n");
    /*采用二进制，将字符对应的ascii码转换为二进制*/
    printf("plaintext     %c    %s\n", plaintext, itoa(plaintext, buf, 2));
    printf("secretkey     %c    %s\n", secretkey, itoa(secretkey, buf, 2));
    printf("ciphertext    %c    %s\n", ciphertext, itoa(ciphertext, buf, 2));
    printf("decodetext    %c    %s\n", decodetext, itoa(decodetext, buf, 2));
    return 0;
}
