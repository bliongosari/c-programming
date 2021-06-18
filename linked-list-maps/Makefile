#Makefile

map1: main1.o function.o tree.o nn_search.o
	gcc -o map1 main.o function.o tree.o nn_search.o -lm
map2: main2.o function.o tree.o rad_search.o
	gcc -o map2 main2.o function.o tree.o rad_search.o -lm


main1.o: main.c function.h tree.h nn_search.h
	gcc -c -Wall main.c
main2.o: main2.c function.h tree.h nn_search.h
	gcc -c -Wall main2.c
function.o: function.c function.h
	gcc -c -Wall function.c
tree.o: tree.c tree.h
	gcc -c -Wall tree.c
nn_search.o: nn_search.c nn_search.h
	gcc -c -Wall nn_search.c
rad_search.o: rad_search.c rad_search.h
	gcc -c -Wall rad_search.c
