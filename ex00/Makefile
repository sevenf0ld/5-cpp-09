# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 13:37:33 by maiman-m          #+#    #+#              #
#    Updated: 2024/07/21 13:07:05 by maiman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = btc

ARG="input_date_4.txt"

RESET = reset

SILENT_FCLEAN = make -s fclean

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -Wshadow -std=c++98 -g3 -pedantic

CPPFLAGS = -I include

SOURCE = main.cpp

SRC_DIR = src

SRCS = $(addprefix $(SRC_DIR)/,$(SOURCE))

OBJ_DIR = obj

OBJS = $(addprefix $(OBJ_DIR)/,$(SOURCE:%.cpp=%.o))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(CPPFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

run: re
	$(RESET) && ./$(NAME) $(ARG) && $(SILENT_FCLEAN)

leaks: re
	$(RESET) && leaks --atExit -- ./$(NAME) $(ARG) && $(SILENT_FCLEAN)

debug: re
	$(RESET) && lldb -- $(NAME) $(ARG) && $(SILENT_FCLEAN)

valgrind: re
	$(RESET) && valgrind --leak-check=full --tool=memcheck -s --track-origins=yes ./$(NAME) && $(SILENT_FCLEAN)

.PHONY: all clean fclean re
