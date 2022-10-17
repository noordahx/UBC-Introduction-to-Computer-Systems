CFLAGS += -std=gnu11 -g
EXES    = namelist

all:  $(EXES)
clean:
	-rm -f $(EXES)

namelist: BinaryTree.c
# don't treat all and clean as file targets
.PHONY: all clean
