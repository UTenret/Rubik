###########################################################
#### NAME

NAME			= RubiksCube

###########################################################
#### PATH TO SOURCES

PATH_SRCS		+= srcs/

###########################################################
#### SOURCES

SRCS			+= main.cpp
SRCS			+= RubiksCube.cpp
SRCS			+= PruningTable.cpp
SRCS			+= Solver.cpp

vpath %.cpp $(PATH_SRCS)
vpath %.hpp $(PATH_SRCS)

###########################################################
#### OBJS

PATH_OBJS		= objs/
OBJS			= $(patsubst %.cpp, $(PATH_OBJS)/%.o, $(SRCS))

###########################################################
#### INCLUDES

HEADER			+= RubiksCube.hpp
HEADER			+= PruningTable.hpp
HEADER			+= Solver.hpp
HEADER			+= math.hpp

###########################################################
#### COMPILATION

CC				= c++
CFLAGS			+= -Wall
CFLAGS			+= -Wextra
# CFLAGS			+= -Werror
CFLAGS			+= -std=c++17
SMAKE		= make --no-print-directory

###########################################################
#### RULES

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ 
	@echo "\033[1;35m=======  compilation complete  =======\033[0m"

$(OBJS): $(PATH_OBJS)/%.o: %.cpp $(HEADER)
	@mkdir -p $(PATH_OBJS)
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@$(RM) -R $(PATH_OBJS)
	@echo "\033[1;36m=======    cleaning complete   =======\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[1;36m======= full cleaning complete =======\033[0m"

re: fclean all

.PHONY: all clean fclean re
