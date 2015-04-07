#include <stdio.h>  //标准输入输出函数
#include <stdlib.h>  //标准库函数
#include <string.h>  //字符串处理函数
#include <ctype.h>  //字符操作函数
#include <conio.h>  //getch()使用

void printMenu(void);
int checkPwd(int type);
int encryptFile(char *sourcefile, char *secretKey,char *targetFile);
char redo(void);

int  password=123456;  // 软件初始密码

int main()
{
    int newpwd, newpwda;  // 更改密码时，用户两次输入的新密码
    char sourcefile[30],  // 加密/解密的文件名
         targetFile[30],  // 解密/加密后要保存的文件名
         secretKey[21],  // 文件加密的密钥
         action; // 要进行的操作

    // 操作前先校验使用密码
    if(!checkPwd(1))
    {
        printf("Sorry,check failed!please press any key to quit...\n");
        getch();//吃掉按键不回显
        exit(1);
    }

    // 密码校验成功，进入程序
    while(1)
    {
        system("cls");  // 清屏
        printMenu();  // 显示菜单
        scanf("%c",&action);  // 输入要执行的操作
        fflush(stdin);  // 清空stdin缓冲区
        system("cls");

        switch(action)
        {
        case 'z':
            printf("Bye!");
            exit(0);
            break;
        case 'a':
            while(1)
            {
                printf("Enter the name of sourcefile(route):\n");
                scanf("%s", sourcefile);
                printf("Enter secretkey:\n");  //密钥是用户自己定义的，可以随意给需要加密的文件添加密钥
                scanf("%s", secretKey);
                printf("Enter the name of targetfile(route):\n");  //给加密后的文件命名，并保存
                scanf("%s",targetFile);
                if( encryptFile(sourcefile, secretKey, targetFile) )
                {
                    printf("Congratulation!,encrypt [%s] successfully,save in[%s].\n", sourcefile, targetFile);
                }
                if(redo() == 'a')   // 继续加密文件
                {
                    system("cls");
                }
                else    // 回到主菜单
                {
                    break;
                }
            }
            break;
        case 'b':
            while(1)
            {
                printf("Enter the name of sourcefile(route):\n");
                scanf("%s",sourcefile);
                printf("Enter secretkey:\n");
                scanf("%s",secretKey);
                printf("Enter the name of targetfile(route):\n");  //对解密的文件系统又可以提供保存路径
                scanf("%s", targetFile);
                if( encryptFile(sourcefile, secretKey, targetFile) )
                {
                    printf("Congratulation!,decrypt [%s] successfully,save in[%s].\n", sourcefile, targetFile);
                }
                if(redo() == 'a')   // 继续解密文件
                {
                    system("cls");
                }
                else
                {
                    break;  // 回到主菜单
                }
            }
            break;
        case 'c':
            while(1)
            {
                if(!checkPwd(2))
                {
                    printf("Sorry,check failed!please press any key to quit...\n");
                    getch();
                    exit(0);
                }
                printf("Please enter new password\n");
                scanf("%d",&newpwd);
                printf("Please enter new password again\n");
                scanf("%d",&newpwda);
                if(newpwd==newpwda)   // 两次输入密码相同才成功
                {
                    password = newpwd;
                    printf("Congrarulation!Change password successfully!\n");
                }
                else
                {
                    printf("Sorry,twice enter is not same,change failed!\n");
                }

                if(redo() == 'a')   // 继续修改密码
                {
                    system("cls");
                }
                else    // 回到主菜单
                {
                    break;
                }
            }
            break;

        default:
            printf("No such choice,please press any key back to menu...\n");
            getch();
        }
    }

    return 0;
}

/*显示程序菜单*/
void printMenu()
{
    printf("************Drunk Encryption***********\n");
    printf("*                                     *\n");
    printf("*    Please enter your choice:        *\n");
    printf("*     a. encrypt file                 *\n");
    printf("*     b. decrypt file                 *\n");
    printf("*     c. change password              *\n");
    printf("*     z. quit                         *\n");
    printf("*                                     *\n");
    printf("***************************************\n");
}

/*校验密码
    type    校验类型
    1：进入程序时使用密码
    2：修改密码时校验密码

    return  校验成功或失败的返回值
    0：失败
    1：成功
*/
int checkPwd(int type)
{
    int pwd;  //用户输入的密码
    int trytimes;  // 用户尝试输入密码的次数
    switch(type)
    {
    case 1:
        printf("Please enter the password for access:\n");
        break;
    case 2:
        printf("Please enter the old password to check\n");
        break;
    default:
        printf("It's not the system type!\n");
        return 0;
    }
    // 可以输入三次
    for(trytimes=1; trytimes<=3; trytimes++)
    {
        scanf("%d",&pwd);
        fflush(stdin);//吃掉空格
        if(pwd==password)
        {
            return 1;
            break;
        }
        else if(trytimes==3)
        {
            return 0;
        }
        else
        {
            printf("Sorry,wrong password!You only have %d chances:\n", 3-trytimes);
        }
    }
    return 0;
}

/*加密/解密文件
    sourcefile    要加密/解密的文件名
    secretKey     密钥
    targetFile    加密/解密后要保存的文件名

    加密成功或失败的返回值
    0：加密失败
    1：加密成功
*/
int encryptFile(char *sourcefile, char *secretKey, char *targetFile)
{
    FILE *fpSource, *fpTarget;  // 要打开的文件的指针
    char buffer[21];  // 缓冲区，用于存放从文件读取的数据
    int readCount,  // 每次从文件中读取的字节数
        keyLen = strlen(secretKey),  // 密钥的长度
        i;  // 循环次数

    // 以二进制方式读取/写入文件
    fpSource = fopen(sourcefile, "rb");
    if(fpSource==NULL)
    {
        printf("Sorry,[%s]open failed!\n", sourcefile);
        return 0;
    }
    fpTarget = fopen(targetFile, "wb");
    if(fpTarget==NULL)
    {
        printf("Sorry,[%s]open failed!\n", fpTarget);
        return 0;
    }

    // 不断地从文件中读取 keyLen 长度的数据，保存到buffer，直到文件结束
    while( (readCount=fread(buffer, 1, keyLen, fpSource)) > 0 )
    {
        // 对buffer中的数据逐字节进行异或运算
        for(i=0; i<readCount; i++)
        {
            buffer[i] ^= secretKey[i];
        }
        // 将buffer中的数据写入文件
        fwrite(buffer, 1, readCount, fpTarget);
    }
    fclose(fpSource);
    fclose(fpTarget);
    return 1;
}

/*当前操作完成，要进行的下一次操作（次要菜单）
    下一次操作的字母表示
    a：回到主菜单
    b：继续当前操作
*/
char redo()
{
    char action;
    printf("\nNext step:\n");
    printf("a.do it again\n");
    printf("b.back to menu\n");
    // 不停的等待用户输入，直到输入正确
    while(1)
    {
        fflush(stdin);
        scanf("%c", &action);
        fflush(stdin);
        if(action!='a' && action!='b')
        {
            printf("No such choice,please choose again!\n");
        }
        else
        {
            return action;
            break;
        }
    }
}
