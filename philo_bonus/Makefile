# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 14:58:32 by afadlane          #+#    #+#              #
#    Updated: 2023/03/31 13:54:50 by afadlane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CFLAGS = -Wall -Werror -Wextra  #-fsanitize=thread -g

SRC = philo_utils.c main.c  philo.c
	
cc = gcc
OBJ = ${SRC:.c=.o}

all :${NAME}


${NAME}: ${OBJ} 
	 	${cc} ${CFLAGS} ${OBJ} -o ${NAME}


clean :
		rm -f ${OBJ} 

fclean : clean
		rm -f ${NAME} 

nor:
	norminette

re : fclean all 

