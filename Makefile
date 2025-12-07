# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nimatura <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/07 20:35:18 by nimatura          #+#    #+#              #
#    Updated: 2025/12/07 20:35:21 by nimatura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
FLAGS = -Wall -Wextra -Werror -g -Iinclude -ldl -lglw -pthread -lm
SRC := main.cpp
OBJ := $(SRC:.cpp=.o)
DEPS := $(SRC:.cpp=.d)
MLX_H := MLX42/build/libmlx42.a

all: $(NAME)

-include $(DEPS)
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(SRC) -o $@

%.o: %.cpp Makefile $(INCLUDES)
	$(CC) $(FLAGS) $(SRC) -c $<

clean:
	@rm -rf *.o *.d

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
