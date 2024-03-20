NAME		:= cub3D
CFLAGS		:= -g -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX		:= ./MLX42
LIBFT		:= ./libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
#LIBS	:= -L$(LIBFT) -lft $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -lglfw -framework Cocoa -framework OpenGL -framework IOKit
LIBS	:= -L$(LIBFT) -L$(LIBMLX)/build -lft -ldl -lglfw -pthread -lm -lmlx42

SRCS	:=	source/main.c \
			source/free.c \
			source/init.c \
			source/game.c \
			#src/init_and_copy.c	\
			src/pre_parsing.c	\
			src/parsing.c	\
			src/validate_map.c	\
			src/validation_checks.c	\
			src/rendering.c	\
			src/key_handling.c	\
			src/free_exit.c	\
			src/terminate_exit.c
OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

libft:
	@cd $(LIBFT) && make

libmlx:
	@if [ ! -d "./MLX42/" ]; then \
        git clone https://github.com/codam-coding-college/MLX42.git; \
    fi
	@if [ ! -d "./MLX42/build" ]; then \
        cd ./MLX42 && cmake -B build && cmake --build build -j4; \
    fi

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): libmlx libft $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
#	@norminette $(SRCS)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: clean all

.PHONY: all libft libmlx clean fclean re