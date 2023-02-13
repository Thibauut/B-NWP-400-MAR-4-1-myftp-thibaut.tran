##
## EPITECH PROJECT, 2023
## B-PDG-300-MAR-3-1-PDGD04am-thibaut.tran
## File description:
## Makefile
##

SRC	=	myftp.c

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
