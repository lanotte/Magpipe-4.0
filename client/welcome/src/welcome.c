#include "../../include/myhead.h"

/****************************************
Function:        void welcome()
Description:     注册与登录界面
Calls:           no
Call By:         1.void *thread_write(void *arg) 
                 2.void *thread_read(void *arg) 
Input:           no
Output:          no
return:          NULL
Others:          no
****************************************/

void welcome()                    //登录界面
{
	printf("\n\n\n\n\n");
    printf("                               宫廷专用聊天器                    \n");
	printf("                       ._____________________________.           \n");
    printf("                       | ___________________________ |           \n");
    printf("                       | I                         I |           \n");
    printf("                       | I         后宫版     1.0  I |           \n");
    printf("                       | I                         I |           \n");
	printf("                       | I     1.  录(log)         I |           \n");
    printf("                       | I     2.  注(reg)         I |           \n");
    printf("                       | I     3.  退(quit)        I |           \n");
    printf("                       | I________________________ I |           \n");
    printf("                       !_____________________________!           \n");
    printf("                               ._[_________]_.                   \n");
    printf("                           .___|_____________|___.               \n");
    printf("                           |::: ____             |               \n");
    printf("                           |    ~~~~   [CD-ROM]  |               \n");
    printf("                           !_____________________!               \n");
    printf("\n                                                                 \n");
	printf("请输君之择：");
}
