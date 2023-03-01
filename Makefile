##
## EPITECH PROJECT, 2022
## myftp
## File description:
## Makefile
##

SRC	=	server/init_server.c		\
		server/server.c				\
		server/error.c				\
		server/handle_client.c		\
		server/commands.c			\
		utils/utils.c				\
		utils/utils_link_list.c		\
		utils/utils_link_list2.c	\
		commands/quit.c				\
		commands/noop.c				\
		commands/user.c				\
		commands/pass.c				\
		commands/pwd.c				\
		commands/pasv.c				\
		commands/help.c				\
		commands/retr.c				\
		commands/list.c				\
		commands/stor.c				\
		main.c

OBJ	=	$(SRC:.c=.o)

NAME	= myftp

all	:	$(NAME)	$(SRC)

$(NAME)	:
	@printf "\x1B[1;34m\r[Compiling]               %$(SPACES)c\x1B[1;0m" ' '
	@sleep 0.5
	@gcc	-o $(NAME) $(SRC) -g3 -std=gnu17
	@printf "\x1B[1;32m\r[Compilation terminated]%$(SPACES)c\n\x1B[1;0m" ' '
	@sleep 0.5

clean :
	@rm	-f	$(OBJ)

fclean :
	@printf "\x1B[1;31m\r[Cleaning]                %$(SPACES)c\x1B[1;0m" ' '
	@sleep 0.5
	@rm	-f	$(NAME)
	@printf "\x1B[1;32m\r[Clean terminated]%$(SPACES)c\n\x1B[1;0m" ' '
	@sleep 0.5

re :	fclean	clean
	@printf "\x1B[1;33m\r[Recompiling]             %$(SPACES)c\x1B[1;0m" ' '
	@sleep 0.5
	@gcc	-o $(NAME) $(SRC) -g3 -std=gnu11
	@printf "\x1B[1;32m\r[Recompilation terminated]%$(SPACES)c\n\x1B[1;0m" ' '
	@sleep 0.5
