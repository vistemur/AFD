NAME = AFD
F = ./srcs/*.c

all:
	gcc -o $(NAME) $F -I./includes
clean:
	rm -f $(NAME)
generator:
	gcc AFDexamplesGenerator.c -o ex
random:
	./ex > a
	./AFD --f a
	rm a
re: clean all
