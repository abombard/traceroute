CC=clang
FLAGS42=-Wall -Wextra -Werror
FLAGS=$(FLAGS42)

NAME=ft_traceroute

LIBS_DIR=libs

LIBFT_DIR=$(LIBS_DIR)/libft
PRINTF_DIR=$(LIBS_DIR)/printf
LIST_DIR=$(LIBS_DIR)/list

LIBFT=$(LIBFT_DIR)/libft.a
PRINTF=$(PRINTF_DIR)/libprintf.a
LIST=$(LIST_DIR)/liblist.a

LIBS=-L $(PRINTF_DIR) -lprintf -L $(LIBFT_DIR) -lft -L $(LIST_DIR) -llist

SRC_DIR=srcs
INCLUDES=-I ./includes -I $(LIBFT_DIR) -I $(LIST_DIR) -I $(PRINTF_DIR)

BUILD_DIR=__build

SRC=\
	main.c\
	getopts.c\
	usage.c\
	init.c\
	gethostaddrstr.c\
	gethostnamestr.c\
	newsock.c\
	traceroute.c\
	checksum.c\
	tvsub.c\
	sock_ready.c\
	send_packet.c\
	recv_packet.c\
	round_triptime.c\
	ip_dump.c\

OBJ=$(addprefix $(BUILD_DIR)/,$(SRC:.c=.o))

all:$(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	@mkdir -p $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(PRINTF):
	@make -C $(PRINTF_DIR)

$(LIST):
	@make -C $(LIST_DIR)

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) $(FLAGS42) -c $< -o $@ $(INCLUDES)

$(NAME):$(LIBFT) $(PRINTF) $(LIST) $(OBJ)
	@$(CC) $(FLAGS42) $(OBJ) $(LIBS) -o $@
	@echo "$@ was created"

clean:
	@rm -rf $(BUILD_DIR)
	@make $@ -C $(LIBFT_DIR)
	@make $@ -C $(PRINTF_DIR)
	@make $@ -C $(LIST_DIR)

fclean: clean
	@rm -f $(NAME)
	@make $@ -C $(LIBFT_DIR)
	@make $@ -C $(PRINTF_DIR)
	@make $@ -C $(LIST_DIR)

re: fclean all

# Make a highlight file for types.  Requires Exuberant ctags and awk
types: types.vim
types.vim: srcs/*.[ch] $(LIBS_DIR)/*/*.[h]
		ctags --C-kinds=gstu -o- srcs/*.[ch] |\
				awk 'BEGIN{printf("syntax keyword Type\t")}\
						{printf("%s ", $$1)}END{print ""}' > $@
