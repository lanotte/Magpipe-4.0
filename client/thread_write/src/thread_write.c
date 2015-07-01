#include "../../include/myhead.h"

/****************************************
Function:        void *thread_write(void *arg)
Description:     向服务器发送消息,指令
Calls:           void welcome()
                 void menu()
       
Call By:         int main() 
Input:           void *arg
Output:          no
return:          NULL
Others:          no
****************************************/

extern int is_log;
extern int is_slience;
extern char present_user[NAME_LEN];
extern int id;
extern int is_tran;
extern char tran_target[NAME_LEN];
extern char file_name[NAME_LEN];

void *thread_write(void *arg)                  //向服务器发送命令 
{
	char *p;                               
	int sockfd = *((int *)arg);                //连接描述符
	char cmd[CMD_SIZE] = {0};                  // 操作命令
	char target[NAME_LEN] = {0};               //消息发送对象
	char message[MSG_MAX_LEN] = {0};           //消息内容
	char password[PSWOD_LEN] = {0};            //密码
	char passwd[PSWOD_LEN] = {0};              //确认密码
	msg_t msg;                                 //结构体
	time_t ptime;                              //获取时间 
	
	system("clear");
	welcome();                         //登录页面
	
	while(1)
	{
		sleep(1);
		setbuf(stdin,0);

        gets(cmd);

		if(strcmp(cmd,"log") == 0)             //登录
		{
			if(is_log == NO)                   //未登录
			{	
                int id = 0;
				printf("请输入id:");
                scanf("%d",&(msg.id));
				getchar();
                printf("请输入密码:");
				
				set_disp_mode(STDIN_FILENO,0);                 //取消密码回显
				getpasswd(password,sizeof(password));
				p = password;
				
				while(*p != '\n')
				{
				    p++;	
				}	
				*p = '\0';
				
				set_disp_mode(STDIN_FILENO,1);
				
				msg.action = LOG;
				strcpy(msg.password,password);
				write(sockfd,&msg,sizeof(msg));
		    }
			
			else
			{
			    printf("\n您已登录!\n");	
			}	
			
			continue;
		}

		else if(strcmp(cmd,"reg") == 0)                 //注册
		{
			printf("请输入芳名:");
			//scanf("%s",msg.name);
			gets(msg.name);
            
            int i = 0;                                   
            while(*(msg.name + i) != 0)          //用户名是否有空格
            {
                if(*(msg.name + i) == ' ')
                {
                    break;
                }    
                i++;
            }
            
            if(*(msg.name + i) == ' ')           //有空格不能注册
            {
                printf("\n后宫聊天第一律：注册不得有空格\n");    
                continue;
            }

			printf("请输入密码:");
			set_disp_mode(STDIN_FILENO,0);                   //取消密码回显
			getpasswd(password,sizeof(password));
			p = password;
			
			while(*p != '\n')
			{
				p++;	
			}	
			*p = '\0';
			
			printf("\n请再次输入确认:");
			getpasswd(passwd,sizeof(passwd));
			p = passwd;
			while(*p != '\n')
			{
			    p++;	
			}	
			*p = '\0';
			
			set_disp_mode(STDIN_FILENO,1);
			
			if(strcmp(password,passwd) != 0)                   //密码不一致        
			{
				printf("\n两次密码不一致！\n");
				continue;
			}	
			
			msg.action = REGISTER;
			strcpy(msg.password,passwd);
			write(sockfd,&msg,sizeof(msg));
			continue;
		}

        else if(strcmp(cmd,"chpswd") == 0)             //修改密码
        {
            printf("\n请输入新密码:");
            gets(password);
            printf("请再次输入新密码:");
            gets(msg.password);
            if(strcmp(password,msg.password) != 0)     //两次输入确认
            {
                printf("\n卿务必查验先后之密码一致否\n");
                continue;
            }

			msg.action = CH_PASSWD;
			strcpy(msg.name,present_user);               
            msg.id = id;
            write(sockfd,&msg,sizeof(msg));            //发送修改密码指令
            
            continue;
        }    
		
        else if(strcmp(cmd,"chname") == 0)       //修改用户名
        {
            char name_new[NAME_LEN] = {0};      
            printf("\n请输入新用户名:");
            gets(name_new);
            printf("请再次输入新用户名:");
            gets(msg.name);
 
            if(strcmp(name_new,msg.name) != 0)   //两次输入确认
            {
                printf("\n卿务必查验先后之姓名一致否\n\n");
                continue;
            }

            int i = 0;                                   
            while(*(msg.name + i) != 0)          //用户名是否有空格
            {
                if(*(msg.name + i) == ' ')
                {
                    break;
                }    
                i++;
            }
            
            if(*(msg.name + i) == ' ')           //有空格不能注册
            {
                printf("\n后宫聊天第一律：注册不得有空格\n");    
                continue;
            }
			
            msg.action = CH_NAME;
            msg.id = id;
            write(sockfd,&msg,sizeof(msg));      //发送修改用户名指令
            
            continue;
        }    
		
        else if(strcmp(cmd,"whsp") == 0)                       //私聊
		{
            char *buffer = (char *)malloc(sizeof(char)* 1024);
            if(is_log == YES && is_slience == NO)
			{	
				printf("请输入接收的御妻:");
				gets(msg.target);
                printf("\n请输入密令:");
				
            //    gets(msg.msg);
                
                scanf("%s",buffer);

                while(strlen(buffer) > 100)
                {
                    printf("话太多，最长100字节");
                    printf("请输入密令：");
                    printf("输入D取消\n");

                    scanf("%s",buffer);

                    if(strcmp(buffer,"D") == 0)
                    {
                        return ;
                    }
                }
                
                strcpy(msg.msg,buffer);    
                     
			
                if(strcmp(msg.msg,"smile") == 0)
                {
                    strcpy(msg.msg,"Smile");
                }

                else if(strcmp(msg.msg,"sad") == 0)
                {
                    strcpy(msg.msg,"Sad");
                }
                
                else if(strcmp(msg.msg,"disdain") == 0)
                {
                    strcpy(msg.msg,"Disdain");
                }


                else if(strcmp(msg.msg,"sweat") == 0)
                {
                    strcpy(msg.msg,"Sweat");
                }

                else if(strcmp(msg.msg,"cold") == 0)
                {
                    strcpy(msg.msg,"Cold");
                }

                else if(strcmp(msg.msg,"hungry") == 0)
                {
                    strcpy(msg.msg,"Hungry");
                }

                else if(strcmp(msg.msg,"cry") == 0)
                {
                    strcpy(msg.msg,"Cry");
                }

                else if(strcmp(msg.msg,"angry") == 0)
                {
                    strcpy(msg.msg,"Angry");
                }

                else if(strcmp(msg.msg,"what") == 0)
                {
                    strcpy(msg.msg,"What");
                }

				msg.id = id;
                msg.action = WHISPER;
				strcpy(msg.name,present_user);
				write(sockfd,&msg,sizeof(msg));
			}
			
			else if(is_log == NO)
			{
			    printf("\n请先登录!\n");	
			}
			
			else if(is_log == YES && is_slience == YES)              //被禁言无法发送
			{
			    printf("\n大胆，你以被罚居上阳宫静思己过，还敢出来兴风作浪！\n");	
				printf("若当真悔改，可输入require向帝后请罪！\n");
			}	
			
			continue;
		}

		else if(strcmp(cmd,"chat") == 0)
		{
			if(is_log == YES && is_slience == NO)             //已登录且未被禁言
			{	
				strcpy(msg.name,present_user);
				printf("请宣懿旨:");
				//getchar();
				gets(msg.msg);
				
                msg.id =id;
				msg.action = CHAT;
				write(sockfd,&msg,sizeof(msg));
			}
			
			else if(is_log == NO)                          //未登录
			{
				printf("\n请先登录!\n");	
			}
			
			else if(is_log == YES && is_slience == YES)    //被禁言
			{
			    printf("\n你已被禁言!\n");	
				printf("你可以输入require请求管理员解禁!\n");
			}	
			continue;
		}

		else if(strcmp(cmd,"show") == 0)                   //查询在线用户
		{
			if(is_log == YES)
			{	
				msg.id = id;
                msg.action = SHOW_ONLINE;
				write(sockfd,&msg,sizeof(msg));
	    	}
			
			else
			{
				printf("\n请先登录!\n");                   //未登录
			}
		}

		else if(strcmp(cmd,"quit") == 0)                   //请求退出系统
		{
			msg.id = id;
            msg.action = QUIT_SYSTEM;
            strcpy(msg.name,present_user);
			write(sockfd,&msg,sizeof(msg));
			close(sockfd);
			return NULL;
		}
		
		else if(strcmp(cmd,"table") == 0)                  //返回页面 
		{
			system("reset");
			menu();
			continue;
		}
		
		else if(strcmp(cmd,"slience") == 0)                //禁言
		{
			if(strcmp(present_user,"admin") == 0)
			{	
				msg.id = id;
                msg.action = SLIENCE;
				printf("您想罚哪位御妻静思己过？");
				//scanf("%s",msg.target);
				gets(msg.target);

				if(strcmp(msg.target,"admin") == 0)        //不能禁言自己
				{
				    printf("\n帝后不必刑罚自己\n");	
				}	
				
				else 
				{	
					write(sockfd,&msg,sizeof(msg));
			    }
			}
			
			else                                           //非管理员 
			{
				printf("\n大胆，此项权利乃帝后所有，汝等岂敢觊觎！\n");
		    }
			continue;
		}

		else if(strcmp(cmd,"require") == 0)                //请求解禁
		{
			if(is_slience == YES && is_log == YES)
			{	
				msg.id = id;
                msg.action = REQUIRE;
				strcpy(msg.target,"admin");
				write(sockfd,&msg,sizeof(msg));
				printf("\n帝后，臣妾真心悔改，请赦免\n");
			}
			
			else if(is_slience == NO)                      //没有被禁言
			{
				printf("\n表现良好，未被刑罚\n");
			}
			
			else if(is_log == NO)                          //未登录
			{
			    printf("\n亲,你还没有登录哦!\n");	
			}	
			continue;
		}
		
		else if(strcmp(cmd,"say") == 0)                     //解禁
		{
			if(strcmp(present_user,"admin") == 0)
			{	
				msg.id = id;
                msg.action = SAY;
				printf("帝后，请输入需要赦免御妻");
				//scanf("%s",msg.target);
				gets(msg.target);
                write(sockfd,&msg,sizeof(msg));
			}
			
			else                                            //非管理员
			{
				printf("\n大胆，此项权利乃帝后所有，汝等岂敢觊觎！\n");
		    }
			continue;
		}
		
		else if(strcmp(cmd,"getout") == 0)                  //踢出聊天室
		{
			if(strcmp(present_user,"admin") == 0)
			{	
				printf("请将犯上之人废出：");
				//scanf("%s",msg.target);
				gets(msg.target);
                msg.id = id;
                msg.action = GETOUT;
				write(sockfd,&msg,sizeof(msg));
			}
			
			else                                            //非管理员  
			{
				printf("\n大胆，此项权利乃帝后所有，汝等岂敢觊觎！\n");
		    }
			continue;
		}
		else if(strcmp(cmd,"tran") == 0)                    //发送文件
		{
			if(is_log == YES)
			{	
				printf("请输入文件传输的对象:");                      //接受方  
				//scanf("%s",msg.target);
				gets(msg.target);
                printf("请输入要传输的文件:");                        //文件名
				//scanf("%s",msg.fname);
				gets(msg.fname);
                int fd = open(msg.fname,O_RDONLY);
				
				if(fd < 0)
				{
					printf("\n文件打开失败,请检查文件是否正常!\n");	  //打开文件失败
				}	
                
                else
                {
                    msg.flen = lseek(fd,0,SEEK_END);                  //文件大小 
                    lseek(fd,0,SEEK_SET);

                    strcpy(file_name,msg.fname);                      //文件名,方便写线程读取
                    msg.id = id;
                    msg.action = TRAN;
                    memset(&msg.name,0,sizeof(msg.name));             
                    memset(&msg.msg,0,sizeof(msg.msg));
                    strcpy(msg.name,present_user);
                    strcpy(msg.msg,"wanttotran");
				    write(sockfd,&msg,sizeof(msg));                   //等待对方是否接收
                    
                    printf("\n请等待对方确认...\n");
                    is_tran == YES;                                   //有文件传输指令
                    close(fd);
                }
			}
			
			else if(is_log == NO)
			{
				printf("\n你还没登录哦亲!\n");                       //未登录
		    }
			
			continue;
		}
        
        else if(is_tran == YES && (strcmp(cmd,"yes") == 0))          //有文件传输,指令有效
        {
            if(is_log == NO)                                         //未登录
            {
                printf("\n亲,你还没有登录哦!\n");
                continue;
            }    

            msg.action = TRAN;
            strcpy(msg.msg,"accept");
            strcpy(msg.name,present_user);
            strcpy(msg.target,tran_target);
            write(sockfd,&msg,sizeof(msg_t));                        //同意接收文件  
            
            continue;
        }    
        
        else if(is_tran == YES && (strcmp(cmd,"no") == 0))           //指令no是否可用
        {
            if(is_log == NO)                                         //未登录
            {
                printf("\n亲,你还没有登录哦!\n");
                continue;
            }   

            msg.action = TRAN;
            strcpy(msg.msg,"refuse");
            strcpy(msg.name,present_user);
            strcpy(msg.target,tran_target);
            write(sockfd,&msg,sizeof(msg_t));
            printf("\n你已拒绝接收该文件!\n");                       //拒绝接收文件
            is_tran = NO;            
            continue;
        }     
		else
		{
			printf("\n未知命令!请检查后再输入!\n");             
		}
	}

	return NULL;
}
