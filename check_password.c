#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
const int password=123456;//设置密码
int check_pwd();//校验密码
void to_exit(char *msg);//退出函数
int main()
{
if(check_pwd())
to_exit("恭喜！密码校验成功！\n");
else
to_exit("对不起！三次输入密码错误！\n");
return 0;
}

int check_pwd()
{
    int trytimes,pwd;//尝试次数和密码
    printf("请输入密码进行校验：");
    for(trytimes=1;trytimes<4;trytimes++)
    {
        scanf("%d",&pwd);
        fflush(stdin);
        if(pwd==password)
        {
            return 1;//返回1成功
            break;
        }
        else
        {
            if(trytimes==3)
                return 0;//返回0失败
            else
            {
                printf("对不起，您还有%d次机会！",3-trytimes);
                printf("请重新输入密码：");
            }
        }
    }
}

void to_exit(char * msg)
{
    printf("%s",msg);
    printf("按任意键退出程序...");
    getch();//实现按任意键退出的功能
}
