NAME = philo
SRCS = philo.c
HEADER = philo.h
CC = cc
CFLAGS = -Wall -Werror -Wextra
COMPILER = $(CC) $(CFLAGS)
RM = rm -f
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Complied chief"
	$(COMPILER) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(COMPILER) -c $< -o $@

clean:
	@echo "Deleted chief"
	$(RM) $(OBJS)

fclean: clean
	@echo "Deleted Everything chief"
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
# .SILENT:
