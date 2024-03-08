
#Library Name ----------------------------

NAME = cub3d
NAME_BONUS = cub3d_bonus

#Dependencies -----------------------------

LIBFT = libft

#Command variables ------------------------

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c17 -fsanitize=address
MK = mkdir -p
RM = rm -rf
USER = $(shell whoami)
MLX42 = -framework Cocoa -framework OpenGL -framework IOKit MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib"

#Sources directories

INCDIR = inc
SRCDIR = src
LIBFT_A = libft.a
LIBFTDIR = libft
LIBFT = $(addprefix $(LIBFTDIR)/, $(LIBFT_A))
SRC = error.c \
	extract_info.c \
	free.c \
	init.c \
	main.c \
	parsing.c \
	utils.c \
	verify_data.c
SRCB = 
		
VPATH = ${SRCDIR}

#Object directories

OBJDIR = obj

OBJS = $(addprefix ${OBJDIR}/, ${SRC:%.c=%.o})
OBJSB = $(addprefix ${OBJDIR}/, ${SRCB:%.c=%.o})

all: $(NAME)

${OBJDIR}/%.o : %.c
	${CC} ${FLAGS} -I${INCDIR} -Ilibft/inc -Imlx42 -c $< -o $@ 
	
$(NAME): $(OBJDIR) $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) ${FLAGS} $(OBJS) -L$(dir $(LIBFT)) -lft -o $(NAME)

$(OBJDIR):
	$(MK) $(OBJDIR)

$(NAME_BONUS): $(OBJDIR) $(OBJSB)
	make -C $(LIBFTDIR)
	$(CC) ${FLAGS} $(OBJSB) -L$(dir $(LIBFT)) -lft -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

leaks:
	leaks --atExit -- ./cub3d map2.cub

valgrind:
	valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all ./cub3d map2.cub

clean:
	$(RM) $(OBJDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY:
	clean fclean re bonus all