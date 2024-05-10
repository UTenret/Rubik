NAME = cube

CC = @g++
CCFLAG = -c -Wall

LDFLAGS = -lGL -lGLU -lglut

RM = @rm
RMFLAG = -rf

SMAKE = @make --no-print-directory
DIR = objs

SRC	+= main.cpp
SRC	+= draw.cpp
SRC	+= moves.cpp
OBJ = $(addprefix $(DIR)/,$(SRC:.cpp=.o))

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
	@echo "\033[1;35m=======  compilation complete  =======\033[0m"

$(DIR)/%.o : %.cpp
	@mkdir -p objs
	$(CC) $(CCFLAG) -c $< -o $@

clean :
	$(RM) $(RMFLAG) $(OBJ) objs/
	@echo "\033[1;36m=======    cleaning complete   =======\033[0m"

fclean : clean
	$(RM) $(RMFLAG) $(NAME)
	@echo "\033[1;36m======= full cleaning complete =======\033[0m"

re : fclean all

.PHONY : all clean fclean re
