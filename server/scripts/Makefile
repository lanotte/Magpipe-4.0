CC := gcc
Target := chat_room_server
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += msg_handle  main  block_read block_write  read_unlog_msg
AllObjs := $(addsuffix /src/*.o,$(Modules))

