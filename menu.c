#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
void print_menu();//打印主菜单
void action_menu(char *msg);
int main()
{
    char choice;
    while(1)
    {
        system("cls");//清屏
        print_menu();
        scanf("%c",&choice);
        fflush(stdin);//清空缓冲区，吃掉缓冲区中的'\n'
        system("cls");
        switch(choice)
        {
        case 'a':
        case 'A':
            action_menu("文件加密成功!");
            break;
        case 'b':
        case 'B':
            action_menu("文件解密成功!");
            break;
        case 'c':
        case 'C':
            action_menu("更改密码成功!");
            break;
        case 'd':
        case 'D':
            printf("再见!");
            exit(0);
            break;
        default:
            action_menu("没有相应的选项");
        }
    }
    return 0;
}

/*打印主菜单*/
void print_menu()
{
    printf("*************** 文本加密解密软件 ************\n");
    printf("*                                           *\n");
    printf("*    请输入您的选择：                       *\n");
    printf("*     a. 文件加密                           *\n");
    printf("*     b. 文件解密                           *\n");
    printf("*     c. 更改密码                           *\n");
    printf("*     d. 退出系统                           *\n");
    printf("*                                           *\n");
    printf("*********************************************\n");
}

/*选项菜单*/
void action_menu(char *msg)
{
    printf("%s\n",msg);
    printf("请输入任意键返回!\n");
    getch();//非缓冲IO
}
