#include "../../include/myhead.h"

/****************************************
Function:        void menu()
Description:     登录后的页面
Calls:           no
Call By:         void *thread_read(void *arg)
Input:           no
Output:          no
return:          NULL
Others:          no
****************************************/

extern int is_log;
extern int is_slience;
extern char present_user[NAME_LEN];
extern int id;

void menu()             //登录后界面
{
	printf("\n\n\n");
	printf("     \t\t \n");
	printf("     \t\t                                                    \n");
	printf("     \t\t *                  欢迎使用后宫版聊天器            * \n");
	printf("     \t\t *  注      册 : reg           ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆      * \n");
	printf("     \t\t *  示以户在线 : show        ★★       ★       ★★    * \n");
	printf("     \t\t *  密      令 : whsp       ☆☆                 ☆☆   * \n");
	printf("     \t\t *  宣      旨 : chat        ★★               ★★    * \n");
	printf("     \t\t *  发      文 : tran         ☆☆             ☆☆     * \n");
	printf("     \t\t *  易      码 : chpswd        ★★           ★★      * \n");
	printf("     \t\t *  易      名 : chname          ☆☆        ☆☆       * \n");
	printf("     \t\t *  告      退 : quit              ★★    ★★         * \n");
	printf("     \t\t *  回      页 : table                ☆☆             * \n");      
	printf("     \t\t *                                                  * \n");              
	if(strcmp(present_user,"admin") == 0)          //是否是管理员            
	{
	printf("     \t\t *  您贵为帝后，掌管三宫六院各妃嫔生死大权          * \n");
	printf("     \t\t *         静思:   slience                          * \n");
	printf("     \t\t *         赦免:   say                              * \n");
	printf("     \t\t *         废出:   getout                           * \n");
	}	
	printf("     \t\t                                   当前用户: %s   \n",present_user);
	printf("     \t\t                                         id: %d  \n",id);
	printf("     \t\t **************************************************** \n");
    printf("     \t小提示： 共有9种表情可以通过密令发送哦！\n");
	printf("     \t1、smile ( ^_^ )   2、sad   ╮(╯﹏╰）╭      3、disdain  ╭∩╮（︶︿︶）╭∩╮\n");
	printf("     \t4、sweat  -_-|||   5、cold  {{{(>_<)}}}    6、hungry   咕~~(╯﹏╰)b     \n");
	printf("     \t7、cry   o(>﹏<)o  8、angry (╰_╯)#         9、what     ?_?             \n");
}
