NAME = pipex
LIBFT = ./Libft/libft.a
CFLAGS = -Wall -Wextra -Werror -g3 -O0

OBJECTS_FOLDER = ./obj/

MANDATORY_FOLDER = ./mandatory/
MANDATORY_SOURCES = $(addprefix $(MANDATORY_FOLDER), main.c helpers.c fork_exec.c error_handler.c)
MANDATORY_OBJECTS = $(subst $(MANDATORY_FOLDER),$(OBJECTS_FOLDER),$(MANDATORY_SOURCES:.c=.o))

all: $(OBJECTS_FOLDER) $(NAME)

$(OBJECTS_FOLDER):
	mkdir $(OBJECTS_FOLDER)

$(NAME): $(LIBFT) $(MANDATORY_OBJECTS)
	cc $(CFLAGS) $(MANDATORY_OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C Libft

$(OBJECTS_FOLDER)%.o: $(MANDATORY_FOLDER)%.c $(MANDATORY_FOLDER)pipex.h
	cc $(CFLAGS) -c $< -o $@

valgrind: all
	valgrind --leak-check=full --trace-children=yes --trace-children-skip=/usr/bin/tr,/usr/bin/ls \
	./pipex .gitignore "tr a-z A-Z" "ls -l" outfile

clean:
	rm -rf $(OBJECTS_FOLDER)*

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all valgrind
