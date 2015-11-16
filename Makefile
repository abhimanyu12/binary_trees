CC = gcc -Wall -g -Werror

all: tree aug
tree: bin_tree.c print_tree.c
	$(CC) -o tree bin_tree.c print_tree.c

aug: bin_tree_aug.o
	$(CC) -o aug bin_tree_aug.c
clean:
	rm -f tree aug *.o
