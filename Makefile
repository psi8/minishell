# Variables
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCS = builtins_handler.c \
       cmd_env.c \
       cmd_unset.c \
       exec_builtin.c \
       initialization.c \
       minishell.c \
       paths.c \
       rd_output_handler.c \
       validate_cmd.c \
       close_pipes.c \
       cmd_exit.c \
       env.c \
       env_partial.c \
       exec_child.c \
       exec_main.c \
       in_out_redirection.c \
       init_pipe_run_exec.c \
       pipe.c \
       rd_heredoc.c \
       redirection_handler.c \
       signal.c \
       utils.c \
       utils_free.c \
       cmd_cd.c \
       cmd_export.c \
       error_handler.c \
       ft_libft.c \
       cmd_echo.c \
       cmd_pwd.c \
       errors_handling/errors_handling.c \
       exit/exit.c \
       

#syntax.c \
#parsing/parsing.c \
#       parsing/quotes_parse.c \
#       parsing/space_parsing.c

OBJS = $(SRCS:.c=.o)

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
