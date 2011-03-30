#---
# サンプルゲーム
#---

CC = gcc
SRCS = cpu_func.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -g
LDFLAGS = -L/opt/local/lib -L.. -Llib -lSDLmain -lSDL -lSDL_image -lSDL_ttf	\
		-Wl,-framework,Cocoa -ltest -lpthread -lpuyogame
TARGET = puyo

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $< -I. -I../include

clean:
	-rm -f $(TARGET) *.o

$(OBJS): puyogame.h

