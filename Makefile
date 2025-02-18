CC = cc

CFLAGS = -Wall -Wextra -Werror -g
MFLAGS= -lreadline -lncurses

SRC_DIR = srcs
OBJS_DIR = objs

LIBFT_DIR= libft

LIBFT_A= $(LIBFT_DIR)/libft.a

INCLUDE = includes

src = build_cmd.c main.c token_utils.c tokenizing.c lexing.c init.c token_handler.c build_cmd_utils.c
PRSR = parser/build_cmd.c parser/token_utils.c parser/lexing.c parser/init.c parser/tokenizing.c parser/build_cmd_utils.c
BLTNS = builtins/bltn_env.c builtins/pwd.c
src = debug_utils.c main.c $(PRSR) $(BLTNS)

SRCS = $(addprefix $(SRC_DIR)/, $(src))
OBJS = $(addprefix $(OBJS_DIR)/, $(src:.c=.o))

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) all
	@$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJS) $(LIBFT_A) -o $@ $(MFLAGS)


$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@rm -rf $(OBJS_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean : clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY: fclean all clean re
