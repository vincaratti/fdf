NAME		=	fdf	
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -Imlx -I $(INCLUDE) #-ggdb3 -fsanitize=address
SRCDIR		=	./src/
OBJDIR		=	./obj/
INCLUDE		=	./include/

SRC			=	fdf.c					\
				draw_line.c				\
				parser.c				\
				str_map_atoi.c			\
				read_file.c
					
OBJ			=	${addprefix $(OBJDIR), $(SRC:%.c=%.o)}


# ===== #


all:			$(NAME)

$(NAME):		$(OBJDIR) $(OBJ)
				@make -C libft/
				$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx -framework OpenGl -framework AppKit -L libft -lft -o $(NAME)

clean:
				rm -rf $(OBJDIR)
				@make -C libft/ clean

fclean:			
				rm -rf $(NAME) $(OBJDIR)
				@make -C libft/ fclean

re:				fclean all

$(OBJDIR)%.o:	$(SRCDIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
				@mkdir -p $(OBJDIR)

.PHONY:			re clean fclean objs all
