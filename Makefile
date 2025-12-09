# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nimatura <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/07 20:35:18 by nimatura          #+#    #+#              #
#    Updated: 2025/12/07 20:37:00 by nimatura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MAKEFILE now presumes codamMLX is at root of project dir

NAME = cub3D

CC = cc
FLAGS = -Wall -Wextra -Werror -g -Iinclude -ldl -lglw -pthread -lm
SRC := main.cpp
OBJ := $(SRC:.cpp=.o)
DEPS := $(SRC:.cpp=.d)
MLX_H := MLX42/build/libmlx42.a

# To add: codamMLX42 compilation:
# git clone https://github.com/codam-coding-college/MLX42.git
# cd MLX42
# cmake -B build # build here refers to the outputfolder.
# cmake --build build -j4 # or do make -C build -j4

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
