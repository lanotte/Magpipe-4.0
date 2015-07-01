CC := gcc
Target := chat_room_client
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += welcome getpasswd menu main set_disp_mode thread_read thread_write block_write block_read
AllObjs := $(addsuffix /src/*.o,$(Modules))

