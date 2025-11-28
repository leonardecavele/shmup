# structure
NAME = ft_shmup
CC = cc
INCDIR = includes
SRCDIR = srcs
BUILD = .build

# flags
CFLAGS = -MMD -MP -Wall -Wextra -Werror -I $(INCDIR)
MAKEFLAGS+= -j $$(nproc)

# files
SRCS =\
	main.c\
	frame.c

OBJS = $(SRCS:%.c=$(BUILD)/%.o)
DEPS = $(OBJS:.o=.d)

# rules
all: $(NAME)

$(NAME):
	@mkdir -p $(BUILD)
	@$(MAKE) build --no-print-directory

build: $(OBJS)
	$(CC) $(CLFAGS) $(OBJS) -o $(NAME)

$(BUILD)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean
	@$(MAKE) all --no-print-directory

# miscellaneous
.PHONY: all bonus clean fclean re
-include $(DEPS)
