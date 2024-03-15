
#Library Name ----------------------------

NAME = cub3d
NAME_BONUS = cub3d_bonus

#Dependencies -----------------------------

LIBFT = libft

#Command variables ------------------------

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
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
	verify_data.c\
	background.c\
	camera.c
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
	$(CC) ${FLAGS} $(MLX42) $(OBJS) -L$(dir $(LIBFT)) -lft -o $(NAME)

$(OBJDIR):
	$(MK) $(OBJDIR)

$(NAME_BONUS): $(OBJDIR) $(OBJSB)
	make -C $(LIBFTDIR)
	$(CC) ${FLAGS} $(MLX42) $(OBJSB) -L$(dir $(LIBFT)) -lft -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

clean:
	$(RM) $(OBJDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY:
	clean fclean re bonus all