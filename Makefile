NAME = avm

SRCS :=	main.cpp \
	 	VirtualMashine.cpp \
		Mutantstack.cpp \
		OperandFactory.cpp \
		OperandAbstract.cpp \
		OperandInt8.cpp \
		OperandInt16.cpp \
		OperandInt32.cpp \
		OperandFloat.cpp \
		OperandDouble.cpp \

DIR_SRC := $(CURDIR)/src
DIR_OBJ := $(CURDIR)/obj


OBJS := $(SRCS:.cpp=.o)

OBJS := $(addprefix $(DIR_OBJ)/, $(OBJS))
SRCS := $(addprefix $(DIR_SRC)/, $(SRCS))

FLAGS = -Wall -Wextra -Werror

CC = clang++

all: $(NAME)

$(LIBFT_A):
	@make -C libft/

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)


$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp | $(DIR_OBJ)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	/bin/rm -rf $(OBJS)
	/bin/rm -rf $(DIR_OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
