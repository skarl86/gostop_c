OBJS = play.o calcurate.o main.o hwatoo_setting.o
TARGET = gostop

gostop : $(OBJS)
	gcc -o $(TARGET) $(OBJS)
main.o : setting.h
	gcc -c main.c
hwatoo_setting.o : setting.h
	gcc -c hwatoo_setting.c
calcurate.o : setting.h calcurate.h
	gcc -c calcurate.c
play.o : setting.h
	gcc -c play.c
clean:
	rm $(OBJS) $(TARGET)
