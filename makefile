OBJS = game.o util.o file.o play.o calcurate.o main.o hwatoo_setting.o
TARGET = gostop
SOURCES = game.c util.c file.c play.c calcurate.c main.c hwatoo_setting.c

all : clean gostop

clean: 
	rm -rf $(OBJS) $(TARGET)
gostop : $(OBJS)
	gcc -g -o $(TARGET) $(OBJS)
main.o : setting.h
	gcc -c main.c
hwatoo_setting.o : setting.h
	gcc -c hwatoo_setting.c
calcurate.o : setting.h calcurate.h
	gcc -c calcurate.c
play.o : setting.h
	gcc -c play.c
file.o : setting.h file.h
	gcc -c file.c
util.o : setting.h util.h
	gcc -c util.c
game.o : setting.h game.h
	gcc -c game.c
debug: clean
	gcc -g -o $(TARGET) $(SOURCES) 
