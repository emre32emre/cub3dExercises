CC = gcc
NAME = fdf
LIBFT = ./lib/libft
LIBMATRIX = ./lib/libmatrix
LIBMLX = ./lib/libmlx
DIR_SRC = src
DIR_OBJ = temp
HEADERS = incl
FLAGS = #-Wall -Wextra -Werror -O2
LIBMLXFLAGS = -I$(LIBMLX) -L$(LIBMLX) -lmlx -framework OpenGL -framework Appkit
LIBMATRIXFLAGS = -L$(LIBMATRIX) -lmatrix
LIBFTFLAGS = -L$(LIBFT) -lft
SOURCES = main.c \
			scene.c \
			draw.c \
			loop.c \
			events/exit.c \
			events/keys.c \
			ui/ui.c 
SRCS = $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@make -C $(LIBMATRIX)
	@make -C $(LIBMLX)
	$(CC) $(FLAGS) $(LIBFTFLAGS) $(LIBMATRIXFLAGS) $(LIBMLXFLAGS) -o $@ $^

$(DIR_OBJ):
	@mkdir -p temp
	@mkdir -p temp/map
	@mkdir -p temp/camera
	@mkdir -p temp/draw
	@mkdir -p temp/ui
	@mkdir -p temp/events

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HEADERS)/$(NAME).h
	@$(CC) $(FLAGS) -I $(HEADERS) -c -o $@ $<

clean:
	@/bin/rm -f $(OBJS)
	@make -C $(LIBFT) clean
	@make -C $(LIBMATRIX) clean
	@make -C $(LIBMLX) clean
	@/bin/rm -rf $(DIR_OBJ)
	
fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@make -C $(LIBMATRIX) fclean
	@make -C $(LIBMLX) fclean

norm:
	norminette $(HEADERS) $(LIBFT) $(LIBMATRIX) $(DIR_SRC)

re: fclean all

.PHONY: all, $(DIR_OBJ), clean, fclean, norm
