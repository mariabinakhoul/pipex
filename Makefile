SRC = main.c path_utils.c

SRCS = $(addprefix src/, $(SRC))

OBJS = ${SRCS:.c=.o}

NAME = pipex

LIBFT = libft/libft.a

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
NO_COLOR    = \033[m

CC = cc

C_FLAGS = -Wall -Wextra -Werror -g -I

RM = rm -f

all : $(NAME)

.c.o :
		${CC} ${C_FLAGS} -c $< -o ${<:.c=.o}


$(NAME) : 	${LIBFT} ${OBJS}
		  	${CC} ${C_FLAGS} ${OBJS} ${LIBFT} -o ${NAME}
			@printf "%-53b%b" "$(COM_COLOR)Project Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"
			@printf "%-53b%b" "$(COM_COLOR)LIBFT Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

$(LIBFT) :
		  @make -C ./Libft

clean :	
		@make clean -C ./Libft
		${RM} ${OBJS}
		@printf "%-53b%b" "$(COM_COLOR)OBJECT FILES DELETED:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"


fclean : clean
		${RM} ${NAME} ${LIBFT}
		@printf "%-53b%b" "$(COM_COLOR)ALL CLEAN:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"


re : fclean all

.PHONY : all clean fclean re