# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 13:03:39 by ohosnedl          #+#    #+#              #
#    Updated: 2023/09/05 17:30:02 by ohosnedl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c\
			ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c\
			ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
			ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c\
			ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c\
			ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c\
			ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c\
			ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c\
			ft_tolower.c ft_toupper.c\

OBJECTS = $(SOURCES:.c=.o)

BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c\
			ft_lstdelone.c ft_lstiter.c ft_lstlast.c\
			ft_lstmap.c ft_lstnew.c ft_lstsize.c\

BONUS_OBJS = $(BONUS:.c=.o)

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

all:			$(NAME)

$(NAME):		$(OBJECTS)
				ar rcs $(NAME) $(OBJECTS)

clean:
				rm -rf $(OBJECTS) $(BONUS_OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

bonus:			$(OBJECTS)  $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJECTS) $(BONUS_OBJS)

.PHONY:			all clean fclean re bonus