OBJS = util.o file.o play.o calcurate.o main.o hwatoo_setting.o
TARGET = gostop
SOURCES = util.c file.c play.c calcurate.c main.c hwatoo_setting.c

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

clean:
	rm $(OBJS) $(TARGET)
debug:
	gcc -g -o $(TARGET) $(SOURCES) 
