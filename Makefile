# Variables
NAME = minishell
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libft
READLINE := -lreadline
LIBFT = $(LIBFT_DIR)/libft.a
SRCS = builtins_handler.c \
       cmd_env.c \
       cmd_unset.c \
       exec_builtin.c \
       initialization.c \
       minishell.c \
       paths.c \
       rd_output_handler.c \
       rd_input_handler.c \
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
       cmd_echo.c \
       cmd_pwd.c \
       errors_handling/errors_handling.c \
       errors/error_handler.c \
       errors/errors_main.c \
       exit/exit.c \
       test_main.c \
       syntax.c \
       parsing/expand.c \
       parsing/heredoc.c \
       parsing/parsing.c \
       parsing/parsing_helpers.c \
       parsing/quotes_parse.c \
       parsing/redirs_parse.c \
       parsing/space_parsing.c \
       parsing/parse_cmd_args.c \
       free.c \
       redir.c \

       

OBJS = $(SRCS:.c=.o)

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(READLINE) $(LIBFT)

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
