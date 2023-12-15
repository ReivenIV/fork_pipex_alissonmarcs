NAME = pipex
NAME_BONUS = pipex_bonus
LIBFT = ./Libft/libft.a
CFLAGS = -Wall -Wextra -Werror -g3 -O0

OBJECTS_FOLDER = ./obj/

MANDATORY_FOLDER = ./mandatory/
MANDATORY_SOURCES = $(addprefix $(MANDATORY_FOLDER), main.c helpers.c childs.c error_handler.c)
MANDATORY_OBJECTS = $(subst $(MANDATORY_FOLDER),$(OBJECTS_FOLDER),$(MANDATORY_SOURCES:.c=.o))

BONUS_FOLDER = ./bonus/
BONUS_SOURCES = $(addprefix $(BONUS_FOLDER), main_bonus.c helpers_bonus.c \
	childs_bonus.c error_handler_bonus.c)
BONUS_OBJECTS = $(subst $(BONUS_FOLDER),$(OBJECTS_FOLDER),$(BONUS_SOURCES:.c=.o))

all: $(OBJECTS_FOLDER) $(NAME)

$(OBJECTS_FOLDER):
	mkdir $(OBJECTS_FOLDER)

$(NAME): $(LIBFT) $(MANDATORY_OBJECTS)
	cc $(CFLAGS) $(MANDATORY_OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C Libft

$(OBJECTS_FOLDER)%.o: $(MANDATORY_FOLDER)%.c $(MANDATORY_FOLDER)pipex.h
	cc $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(BONUS_OBJECTS)
	cc $(CFLAGS) $(BONUS_OBJECTS) $(LIBFT) -o $(NAME_BONUS)

$(OBJECTS_FOLDER)%.o: $(BONUS_FOLDER)%.c $(BONUS_FOLDER)pipex_bonus.h
	cc $(CFLAGS) -c $< -o $@

valgrind: all
	valgrind --leak-check=full --trace-children=yes --trace-children-skip=/usr/bin/tr,/usr/bin/ls \
	./pipex .gitignore "tr a-z A-Z" "ls -l" outfile

clean:
	rm -rf $(OBJECTS_FOLDER)*

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: clean fclean re all valgrind
