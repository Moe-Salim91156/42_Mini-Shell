CC = cc

CFLAGS = -Wall -Wextra -Werror -g
MFLAGS= -lreadline -lncurses

src_dir = srcs
objs_dir = objs

LIBFT_DIR= libft

LIBFT_A= $(LIBFT_DIR)/libft.a

INCLUDE = includes

src = main.c

SRCS = $(addprefix $(src_dir)/, $(src))
OBJS = $(addprefix $(objs_dir)/, $(src:.c=.o))

NAME = minishell


all : $(NAME)

$(NAME) : $(OBJS)	
	@$(MAKE) all -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJS) $(LIBFT_A) -o $@ $(MFLAGS)


$(objs_dir)/%.o: $(src_dir)/%.c | $(objs_dir)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(objs_dir):
	@mkdir -p $(objs_dir)
	
clean:
	@rm -rf $(objs_dir)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean : clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY: fclean all clean re
