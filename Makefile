###########################################################
#### NAME

NAME            = RubiksCube

###########################################################
#### PATH TO SOURCES

PATH_SRCS       += srcs/
PATH_SRCS       += srcs/ThistlewaiteGroups/

###########################################################
#### SOURCES

SRCS            += main.cpp
SRCS            += RubiksCube.cpp
SRCS            += PruningTable.cpp
SRCS            += ThistlewaiteSolver.cpp
SRCS            += visualizer.cpp
SRCS            += moves.cpp
SRCS            += draw.cpp
SRCS            += ThistlewaiteGroups/Group0.cpp
SRCS            += ThistlewaiteGroups/Group1.cpp
SRCS            += ThistlewaiteGroups/Group2.cpp
SRCS            += ThistlewaiteGroups/Group3.cpp

vpath %.cpp $(PATH_SRCS)
vpath %.hpp $(PATH_SRCS)

###########################################################
#### OBJS

PATH_OBJS       = objs/
OBJS            = $(patsubst %.cpp, $(PATH_OBJS)/%.o, $(SRCS))

###########################################################
#### INCLUDES

HEADER          += RubiksCube.hpp
HEADER          += PruningTable.hpp
HEADER          += ThistlewaiteSolver.hpp
HEADER          += ThistlewaiteGroups/Group0.hpp
HEADER          += ThistlewaiteGroups/Group1.hpp
HEADER          += ThistlewaiteGroups/Group2.hpp
HEADER          += ThistlewaiteGroups/Group3.hpp
HEADER          += math.hpp
HEADER          += draw.hpp
HEADER          += moves.hpp
HEADER          += visualizer.hpp

###########################################################
#### COMPILATION

CC              = c++
CFLAGS          += -Wall
CFLAGS          += -Wextra
# CFLAGS         += -Werror
CFLAGS          += -std=c++17
CFLAGS          += -Isrcs
CFLAGS          += -Isrcs/ThistlewaiteGroups
SMAKE           = make --no-print-directory
LDFLAGS         = -lGL -lGLU -lglut

###########################################################
#### RULES

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	@echo "\033[1;35m=======  compilation complete  =======\033[0m"

$(OBJS): $(PATH_OBJS)/%.o: %.cpp $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -R $(PATH_OBJS)
	@echo "\033[1;36m=======    cleaning complete   =======\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[1;36m======= full cleaning complete =======\033[0m"

re: fclean all

.PHONY: all clean fclean re
