app: main.o clients.o vehicles.o managers.o menuFuncs.o
	gcc -o app main.o clients.o vehicles.o managers.o menuFuncs.o -fno-exceptions

main.o : main.c vehicles.h clients.h managers.h menuFuncs.h
	gcc -c main.c

clients.o: clients.c clients.h
	gcc -c clients.c

vehicles.o: vehicles.c vehicles.h
	gcc -c vehicles.c

managers.o: managers.c managers.h
	gcc -c managers.c

menuFuncs.o: menuFuncs.c menuFuncs.h
	gcc -c menuFuncs.c
