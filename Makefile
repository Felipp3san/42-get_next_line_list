CFLAGS = -Wall -Wextra -g

NAME = test
MAIN_FILE = test_get_next_line.c

#SRC_FILES = get_next_line \
			get_next_line_utils \

SRC_FILES = get_next_line_bonus \
			get_next_line_utils_bonus \

SRCS = $(addsuffix .c, $(SRC_FILES))
OBJS = $(addsuffix .o, $(SRC_FILES))

$(NAME): $(MAIN_FILE) $(OBJS)
	cc $(CFLAGS) -o $@ $^
	@make clean

*.o: *.c
	cc $(CFLAGS) -o $@ -c $^

clean: 
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
