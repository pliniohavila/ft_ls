CC 		= clang
FLAGS	= -Wall -Wextra -Werror
SANIT 	= -fsanitize=address
DBG   	= -g3


all:
	$(CC) $(FLAGS) -g3  main.c -o main

run:
	./main

%: %.c
	$(CC) $(FLAGS) $< -o $@ 

clean: 
	rm main