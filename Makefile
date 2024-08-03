# Имя целевого исполняемого файла
NAME = minishell

# Компилятор и флаги компиляции
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Путь к заголовочным файлам
INCLUDES = -I.

# Список исходных файлов
SRCS = main.c \
       builtins_handler.c \
       cmd_cd.c \
       cmd_echo.c \
       cmd_env.c \
       cmd_exit.c \
       cmd_export.c \
       cmd_pwd.c \
       cmd_unset.c

# Создание списка объектных файлов
OBJS = $(SRCS:.c=.o)

# Правило сборки целевого файла
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) -lreadline

# Правило для сборки объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Правило для очистки объектных файлов
clean:
	rm -f $(OBJS)

# Правило для полной очистки
fclean: clean
	rm -f $(NAME)

# Правило для пересборки
re: fclean all
