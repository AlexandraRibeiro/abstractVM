# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/11 16:36:10 by aribeiro          #+#    #+#              #
#    Updated: 2017/03/15 20:24:14 by aribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	parser_test

#SRC		=	$(wildcard *.cpp)

SRC		=	parser_test.cpp Class_Parser.cpp


FLAGS	=	-Wall -Wextra -Werror 
LFLAGS	=

RM		=	rm -rf

OBJ	=	$(SRC:.cpp=.o)


#variables for colors to highlight the make results
yellow	= \033[33;1m
blue	= \033[36;1m
magenta = \033[35;1m
green	= \033[32;1m
normal	= \033[0m

SRC_DIR = .
INC_DIR = .
OBJ_DIR = obj_d


OBJ_F	= $(addprefix $(OBJ_DIR)/,$(OBJ))

DEP_F	= $(OBJ_F:.o=.d)

ifeq ($(shell echo "_"),"_")
	NAME_EXE	= $(NAME).exe
	LFLAGS	+=	-s -static
	CC		=	g++
else
	NAME_EXE	= ./$(NAME)
	CC		=	clang++
endif

all:  newdir $(NAME_EXE) done

newdir: 
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	
$(NAME_EXE): $(OBJ_F)
	@printf "\n$(yellow) Linking ...  $@$(normal)\n\n"
	$(CC) -o $@ $^ -I$(INC_DIR) $(LFLAGS)
	@printf "\n$(green) Executable created... $@ $(normal)\n\n"
	
	
$(OBJ_F): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp Makefile
	@printf "$(blue)$ Compiling ...  $(normal)\n"
	$(CC) -c -MMD -MP $(FLAGS) -o $@ $< -I$(INC_DIR)
	
-include $(DEP_F)


done:
	@printf "\n\n$(yellow) Ready to launch $(NAME_EXE)... $(normal)\n"	

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME_EXE)

re: fclean all

.PHONY : re fclean clean all newdir done