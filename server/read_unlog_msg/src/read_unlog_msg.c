#include "../../include/myhead.h"

/*读离线消息*/
int read_unlog_msg(char *my_name,int fd)  //传参：发送的对象和fd(为了在这里写给客户端)
{
    int i;
    int rc;
    int temp;
    int nrow;
    int ncloumn;

    msg_t s;

    char sql[1024];
    char **result;
    sqlite3 *db = NULL;
    char * err_msg;

    rc = sqlite3_open("chat_room.db",&db); //打开数据库
    
    if(rc)
    {
        printf("sqlite open error!");
	exit(1);
    }

    sqlite3_get_table(db,"select * from unlog_info",&result,&nrow,&ncloumn,&err_msg);
                                                        //显示表格中的所有信息

	        //printf("lllllllllllllllll%s\n",my_name);
    for(i = 1; i <= nrow; i++)
    {
        if(strcmp(my_name,result[i * ncloumn + 1]) == 0)       
	{
	        //printf("lllllllllllllllll%s\n",my_name);
		strcpy(s.name,result[i * ncloumn + 0]);  
		strcpy(s.msg,result[i * ncloumn + 2]);

                s.action = WHISPER;

		write(fd,&s,sizeof(s));		        //直到读完所有写给自己的所有信息后跳出
        }
    }
    
    sprintf(sql,"delete from unlog_msg where toname = '%s'",my_name);//读完后全部删除，为了新的信息
   
    sqlite3_exec(db,sql,NULL,NULL,&err_msg);  
    
    return -2;
}
