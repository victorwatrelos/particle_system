CC= g++
FLAGS=-Wall -Wextra -Wno-deprecated-declarations -std=c++11 -I./includes/ -I./includes/GLFW -O3
NAME=particle_system

SRC= main.cpp \
	 clUtil.cpp \
	 GLFWManager.cpp \
	 OpenGL.cpp \
	 Matrix.cpp \
	 OpenCL.cpp \
	 TaskInitParticles.cpp \
	 TaskApplyVel.cpp \
	 Timer.cpp \
	 Task.cpp

OBJ= $(SRC:.cpp=.o)

LIB=  -L./libs/ -lglad -lglfw3

FRWK=   -framework AGL \
		-framework Cocoa \
		-framework OpenGL \
		-framework IOKit \
		-framework CoreFoundation \
		-framework CoreVideo \
		-framework OpenCL

.PHONY: clean fclean re all
.SILENT:
all:$(NAME) 

$(NAME): $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LIB) $(FRWK) $(INC) $(FLAGS)
		echo "\t\xF0\x9F\x8F\x81   Compiling \033[35m$(NAME) \033[0mDONE!"

%.o: %.cpp
		echo "\t\xF0\x9F\x94\xA7   Building \033[34m $@ \033[0m" 
		$(CC) -c $(FLAGS) $(INC) -o $@ $<

clean:
		echo "\t\xF0\x9F\x92\xA3   Cleaning"
		rm -rf $(OBJ)

fclean: clean
		echo "\t\xF0\x9F\x9A\xBD   Full Clean"
		rm -rf $(NAME)

re: fclean all
