NAME = libft.a

HEADERS := -I libft.h

CFLAGS := -Wall -Wextra -Werror -g

OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c))

RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

all: $(NAME)

$(NAME): $(OBJECTS)
		@ar -rcs $@ $^
		@echo "$(GREEN)$(BOLD)LIBFT Done$(RESET)"

$./%.o: $./%.c
		@echo "$(GREEN)$(BOLD)LIBFT Compiling:$(RESET) $(notdir $<)"
		@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
		@rm -f $(OBJECTS)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean