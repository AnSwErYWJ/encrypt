#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int encrypt_file(char *sourcefile,char *secretkey,char *targetfile);
int main()
{
    char sourcefile[30];//加密的文件名
    char targetfile[30];//加密后要保存的文件名
    char secretkey[20];//文件加密的密钥

    printf("输入要加密的文件名(路径):");
    scanf("%s",sourcefile);
    printf("输入密钥:");
    scanf("%s",secretkey);
    printf("加密后的文件名(路径):");
    scanf("%s",targetfile);
    if(encrypt_file(sourcefile,secretkey,targetfile))
        printf("文件%s加密成功，保存在%s。\n",sourcefile,targetfile);
}

int encrypt_file(char *sourcefile,char *secretkey,char *targetfile)
{
    FILE *sourcefp,*targetfp;//文件指针
    char buffer[20];//缓冲区
    int readcount,i,keylen=strlen(secretkey);
    sourcefp=fopen(sourcefile,"rb");
    if(sourcefp==NULL)
    {
        printf("%s打开失败!\n",sourcefile);
        return 0;
    }
    targetfp=fopen(targetfile,"wb");
    if(targetfp==NULL)
    {
        printf("%s打开失败!\n",targetfile);
        return 0;
    }

    while((readcount=fread(buffer,1,keylen,sourcefp))>0)
    {
        for(i=0; i<readcount; i++)
            buffer[i]^=secretkey[i];
        fwrite(buffer,1,readcount,targetfp);
    }
    fclose(sourcefp);
    fclose(targetfp);
    return 1;
}

