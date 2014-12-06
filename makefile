gostop : main.o hwatoo_setting.o calcurate.o
	gcc -o gostop main.o hwatoo_setting.o
main.o : setting.h
	gcc -c main.c
hwatoo_setting.o : setting.h
	gcc -c hwatoo_setting.c
calcurate.o : setting.h calcurate.h
	gcc -c calcurate.c
