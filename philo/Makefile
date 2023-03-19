# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 14:58:32 by afadlane          #+#    #+#              #
#    Updated: 2023/03/18 16:59:10 by afadlane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
NAME2 = checker
CFLAGS = -Wall -Werror -Wextra  #-fsanitize=thread -g

SRC = libft_utils.c main.c  philo.c
	
cc = gcc
# OBJ = ${SRC:.c=.o}

all :${NAME}


${NAME}: ${SRC} 
	 	${cc} ${CFLAGS} ${SRC} -o ${NAME}


clean :
		rm -f ${OBJ} 

fclean : clean
		rm -f ${NAME} 

nor:
	norminette

re : fclean all 

