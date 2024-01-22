NAME = philo
SRCS = philo.c philo_utils.c
HEADER = philo.h
CC = cc
CFLAGS = -Wall -Werror -Wextra -g 
LDFLAGS = -pthread #-fsanitize=thread
COMPILER = $(CC) $(CFLAGS)
RM = rm -f
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Complied chief"
	$(COMPILER) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c $(HEADER)
	$(COMPILER) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	@echo "Deleted Everything chief"
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
# .SILENT:
