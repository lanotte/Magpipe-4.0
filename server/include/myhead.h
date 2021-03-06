#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <sqlite3.h>
#include <time.h>

#define MSG_MAX_LEN 100               //最大消息长度
#define NAME_LEN 20                   //最大用户名长度 
#define PSWOD_LEN 20                  //最大密码长度
#define PORT 9010                     //端口号  
#define PID_NUM 2                     //线程id
#define CMD_SIZE 10                   //操作命令  
#define QUEUE_LEN 10                  //等候队列最大长度  
#define MAX_LINE 80                   //

enum{ 
    LOG         = 1,
    LOG_SUCC    = 2,
    LOG_FAIL    = 3,
    PSWD_ERR    = 4,
    RE_LOG      = 5,
    REGISTER    = 6,
    REG_SUCC    = 7,
    REG_FAIL    = 8,
    RE_REG      = 9,
    WHISPER     = 10,
    SEND_FAIL   = 11,
    USER_ERROR  = 12,
    OFFLINE   	= 13,
    CHAT      	= 14,
    SHOW_ONLINE = 15,
    SHOW_ERR    = 16,
    QUIT_SYSTEM = 17,
    QUIT_FAIL   = 18,
    PTH_CRET_ERR =19,
    OTHER        =20,
    YES          =21,
    NO           =22,
    SLIENCE      =23,
    SAY          =24,
    GETOUT       =25,
    SLIENCE_FAIL =26,
    SAY_FAIL     =27,
    REQUIRE      =28,
    REQUIRE_FAIL =29,
    GETOUT_FAIL  =30,
    WHISPER_SUCC =31,
    CHAT_SUCC    =32,
    TRAN_ASK     =33,
    TRAN_SUCC    =34,
    TRAN_FAIL    =35,
    SLIENCE_SUCC =36,
    SAY_SUCC     =37,
    GETOUT_SUCC  =38,
    TRAN_ACCEPT  =39,
    TRAN_REF     =40,
    TRAN_CANCLE  =41,
    TRAN_REC     =42,
    TRAN         =43,
    CH_PASSWD    =44,
    CHANGE_FAIL  =45,
    CH_NAME      =46,
    ERROR        =47,
    SUCC         =48,
    FACE         =49,
    FACE_SUCC    =50,
    UNONLINE_MSG = 51
};

typedef struct msg_tag
{
    int action;                      //指令类型
    int id;                          //id  
    char name[NAME_LEN];             //用户名
    char password[PSWOD_LEN];        //密码
    char target[NAME_LEN];           //接收方用户名
    char msg[MSG_MAX_LEN];           //消息内容
    char fname[NAME_LEN];            //文件名
    int flen;                        //文件大小
}msg_t;

