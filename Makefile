# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adouay <adouay@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 15:20:33 by adouay            #+#    #+#              #
#    Updated: 2023/10/10 15:47:01 by adouay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                   TARGETS                                    #
#==============================================================================#

NAME = ircserv

#==============================================================================#
#                                   COMMANDS                                   #
#==============================================================================#

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
DFLAGS = -MMD
MKDIR = mkdir -p
RM = rm -f
MAKE_SILENT = make --no-print-directory

#==============================================================================#
#                                    COLORS                                    #
#==============================================================================#

PURPLE = \033[35m
GREEN = \033[32m
YELLOW = \033[33m
END = \033[0m

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_DIR = src/
HEADER_DIR = include/
OBJ_DIR = obj/

#==============================================================================#
#                                   SOURCES                                    #
#==============================================================================#

SRC = main.cpp Server.cpp User.cpp Commands.cpp Channel.cpp \
	Commands/PASS.cpp \
	Commands/USER.cpp \
	Commands/NICK.cpp \
	Commands/JOIN.cpp

#==============================================================================#
#                                   HEADERS                                    #
#==============================================================================#

HEAD = $(addprefix $(HEADER_DIR), Server.hpp User.hpp Commands.hpp Channel.hpp) \

#==============================================================================#
#                                   OBJECTS                                    #
#==============================================================================#

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

#==============================================================================#
#                                   MAKEFILE                                   #
#==============================================================================#

all : $(OBJ_DIR) $(NAME)

$(NAME) : $(OBJ)
	echo "$(YELLOW)Making CPP Exercise$(END)"
	$(CXX) $(OBJ) -o $(NAME)
	echo "$(GREEN)Done$(END)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(HEAD) Makefile
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DFLAGS) -c $< -o $@

$(OBJ_DIR) :
	$(MKDIR) $(OBJ_DIR)

clean :
	echo "$(PURPLE)Cleaning CPP Exercise's objects...$(END)"
	$(RM)r $(OBJ_DIR)
	echo "$(GREEN)Done$(END)"

fclean : clean
	echo "$(PURPLE)Cleaning CPP Exercise...$(END)"
	$(RM) $(NAME)
	echo "$(GREEN)Done$(END)"

re : fclean
	$(MAKE_SILENT) all

.PHONY : all clean fclean re
.SILENT :
