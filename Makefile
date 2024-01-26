NAME = philo
SRCS = srcs/1-main.c \
srcs/2-parse.c \
srcs/3-init.c \
srcs/4-dining.c \
srcs/5-error.c \
srcs/6-utils.c \
srcs/7-time_print.c\
srcs/8-observer.c
HEADER = inc/philo.h
CC = cc
CFLAGS = -Wall -Werror -Wextra -g 
 LDFLAGS = -pthread -fsanitize=thread
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
