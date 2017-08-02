default:
	g++ $(wildcard *.c) -ggdb -Wall -Werror -o hack
interface: 
	gcc com/com.c 
prod:
	g++ -O
interface-prod:
	gcc -c -O -fPIC com/stagearm.c -o stagearm.o
	gcc -shared -o libstagearm.so stagearm.o
	rm stagearm.o

install:
	