CC = cc
CFLAGS = -Wall -Wextra -Werror

# Static library
NAME = libft.a
ARFLAGS = rcs
SRCS = ft_isalpha.c ft_bzero.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strlen.c ft_memcpy.c \
       ft_memset.c ft_strlcat.c ft_strlcpy.c ft_strchr.c ft_toupper.c ft_tolower.c ft_strrchr.c ft_strncmp.c \
       ft_memchr.c ft_memcmp.c ft_memmove.c ft_strnstr.c ft_atoi.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c \
			 ft_itoa.c ft_strtrim.c ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_strmapi.c ft_striteri.c ft_split.c \
			 get_next_line.c ft_strcpy.c


OBJS = $(SRCS:.c=.o)

# making the library = all rule
all: $(NAME)

# Rule to create static library
$(NAME): $(OBJS)
	ar $(ARFLAGS) $@ $^

# Rule to build test executable this is for testing, if u wanna make a main.c file and test the linking;


# Clean up object files
clean:
	rm -f $(OBJS)

# Clean up everything
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re

