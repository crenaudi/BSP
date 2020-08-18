# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/13 14:13:30 by crenaudi          #+#    #+#              #
#    Updated: 2020/05/10 00:42:24 by padelord         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test
LIBFT_FOLDER = ../Libbfx/libft/
LIBGFX_FOLDER = ../Libbfx/libgfx/

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS += -I./include/

SRCS = 	bsp_init.c				\
		bsp_build.c				\
		bsp_close.c				\
		bsp_math.c				\
		bsp_split.c				\
		bsp_renderer.c			\
		bsp_precompute.c		\
		doom_init.c				\
		doom_update.c			\
		doom_close.c			\
		doom_error.c			\
		doom_key.c				\
		doom_move.c				\
		doom_draw.c				\
		doom_sector.c			\
		need_visibility.c		\
		ray_renderer.c			\
		main.c

LDFLAGS = -lm
LDFLAGS += -L./$(LIBGFX_FOLDER) -lgfx
LDFLAGS += -L./$(LIBFT_FOLDER) -lft
CFLAGS += -I./../Libbfx/libgfx/includes/

SYS		:=	$(shell uname)
ifeq ($(SYS), Darwin)
MLX_FOLDER = "mlx_macos"
CFLAGS += -I./../Libbfx/libgfx/includes/MacOs
LDFLAGS += -framework OpenGl -framework AppKit
LDFLAGS += -I /usr/local/include/mlx.h -L /usr/local/lib/ -lmlx
else
CFLAGS += -I./../Libbfx/libgfx/includes/Linux -I./mlx_linux
MLX_FOLDER = "mlx_linux"
LDFLAGS += -lXext -lX11 -lbsd
LDFLAGS += -L./mlx_linux -lmlx
endif

RM = rm -f

SRC	=	$(addprefix src/, $(SRCS))

OBJ = $(SRC:.c=.o)

%.o: %.c include/bsp.h Makefile
	@echo -n "\033[0;33m Compiling :\033[0m $@"
	@$(CC) -o $@ -c $< -I./include/ $(CFLAGS)
	@echo "\033[0;32m [OK] \033[0m"

.PHONY: all fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@make -sC ../Libbfx/libft/
ifneq ($(SYS), Darwin)
	@make -sC mlx_linux
endif
	@make -sC ../Libbfx/libgfx/
	@echo -n "\033[0;33m Compiling :\033[0m $(NAME)"
	@$(CC) -o $(NAME) -g3 $(OBJ) $(LDFLAGS)
	@echo "\033[0;32m [OK] \033[0m\n\033[0;33m [BSP]\033[0;32m[SUCCESS] \033[0m"

clean:
	@$(RM) $(OBJ)
	@make -sC $(LIBFT_FOLDER) clean
ifneq ($(SYS), Darwin)
	@make -sC mlx_linux clean
endif
	@make -sC $(LIBGFX_FOLDER) clean
	@echo		"\033[0;34m [CLEAN][SUCCESS] \033[0m"

fclean: clean
	@$(RM) $(NAME)
	@make -sC $(LIBFT_FOLDER) fclean
	@make -sC $(LIBGFX_FOLDER) fclean
	@echo		"\033[0;34m [FCLEAN][SUCCESS] \033[0m"

re: fclean all
