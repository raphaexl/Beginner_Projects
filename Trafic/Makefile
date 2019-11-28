# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/27 21:58:43 by ebatchas          #+#    #+#              #
#    Updated: 2019/11/28 16:02:36 by ebatchas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc

BINDIR=.
SRCDIR=src
HEADDIR=include
LIBDIR=lib
CFLAGS=-Wall -Wextra -Werror -I$(HEADDIR)
LDFLAGS= $(CFLAGS) -lm

UNAME_S := $(shell uname -s)

DONE_COLOR=\x1b[34;03m
EOC=\033[0m

ifeq	($(UNAME_S),Linux)
	CFLAGS += -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
	LDFLAGS += -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
endif

ifeq	($(UNAME_S),Darwin)
	SDL2 = ./frameworks/SDL2.framework/Versions/A/SDL2
	SDL2_image = ./frameworks/SDL2_image.framework/Versions/A/SDL2_image
	SDL2_ttf = ./frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf
	SDL2_mixer = ./frameworks/SDL2_mixer.framework/Versions/A/SDL2_mixer
	LDFLAGS += -F ./frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer
	CFLAGS += -F ./frameworks
endif

SRC=$(SRCDIR)/main.c\
	$(SRCDIR)/input.c\
	$(SRCDIR)/utils.c\
	$(SRCDIR)/draw.c\
	$(SRCDIR)/init.c
OBJ=$(LIBDIR)/main.o\
	$(LIBDIR)/input.o\
	$(LIBDIR)/utils.o\
	$(LIBDIR)/draw.o\
	$(LIBDIR)/init.o

NAME=game

all: $(NAME)

$(NAME): $(OBJ)

ifeq ($(UNAME_S),Darwin)
	@$(CC) $(LDFLAGS) -o $@ $^
endif

ifeq ($(UNAME_S),Linux)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
endif

	@echo "$(DONE_COLOR) $(BINDIR)/$(NAME) compiled successfully !$(EOC)"

ifeq ($(UNAME_S),Darwin)
	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 $(SDL2) $(NAME)
	@install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image $(SDL2_image) $(NAME)
	@install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf $(SDL2_ttf) $(NAME)
	@install_name_tool -change @rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer $(SDL2_mixer) $(NAME)
endif

$(LIBDIR)/%.o:$(HEADDIR)/%.h

$(LIBDIR)/%.o:$(SRCDIR)/%.c

ifeq ($(UNAME_S),Darwin)
	@$(CC) $(CFLAGS) -o $@ -c $<
endif

ifeq ($(UNAME_S),Linux)
	@$(CC) -c $< -o $@ $(CFLAGS)
endif

.PHONY:clean fclean

clean:
	@rm -rf $(LIBDIR)/*.o
	@echo "$(DONE_COLOR) $(BINDIR)/$(NAME) objs successfully removed !$(EOC)"

fclean:clean
	@rm -rf $(NAME)
	@echo "$(DONE_COLOR) $(BINDIR)/$(NAME) files successfully removed !$(EOC)"

re : fclean all
