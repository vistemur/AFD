NAME = AFD
F = ./srcs/*.c

all:
	gcc -o $(NAME) $F -I./includes
clean:
	rm -f $(NAME)
re: clean all
