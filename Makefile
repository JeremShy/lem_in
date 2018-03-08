SRC_NAME = main.c \
			parsing.c \
			utils.c \
			parse_states.c \
			ft_is_x.c

OBJ_PATH = ./obj/

LIB_SRC_DIR = ./libsrcs/

INC_PATH = ./includes ./$(LIB_SRC_DIR)libft/includes ./$(LIB_SRC_DIR)ft_printf/includes

SRC_PATH = ./srcs/

NAME = lem_in

CC = gcc
CFLAGS =  -Wextra -Wall -g
#CFLAGS =  -Wextra -Wall -Werror -g
LFLAGS = -lft -lftprintf
LIB_DIR=./lib/


OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
OBJ_NAME = $(SRC_NAME:.c=.o)

INC = $(addprefix -I,$(INC_PATH))

all : $(NAME) $(NAME_CH)

$(NAME) : $(OBJ)
	mkdir -p $(LIB_DIR)
	make -C $(LIB_SRC_DIR)libft
	make -C $(LIB_SRC_DIR)ft_printf
	$(CC) $(CFLAGS) $(OBJ) -L $(LIB_DIR) $(LFLAGS) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -fv $(OBJ)
	@rmdir -p $(OBJ_PATH) 2> /dev/null || true
	@make -C $(LIB_SRC_DIR)libft clean
	@make -C $(LIB_SRC_DIR)ft_printf clean

fclean: clean
	@rm -fv $(NAME)
	@make -C $(LIB_SRC_DIR)libft fclean
	@make -C $(LIB_SRC_DIR)ft_printf fclean
	@rmdir lib 2> /dev/null || true

re: fclean all

.PHONY : all clean fclean re
