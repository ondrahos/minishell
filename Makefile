# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 15:51:42 by ohosnedl          #+#    #+#              #
#    Updated: 2024/03/05 13:59:28 by ohosnedl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
CFLAGS := -Wextra -Wall -Werror -g
LIBFLAGS := -L./includes/libft -lft -lreadline
SRCS := $(shell find ./srcs -iname "*.c")
OBJS := ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LIBFLAGS)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
