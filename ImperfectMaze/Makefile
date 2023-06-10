NAME = exec

SRCS = main.c \
	ft_split.c\
	get_url.c\

OBJS = ${SRCS:.c=.o}

DIR_INCLUDES = ./includes/

DIR_SRCS = ./srcs/

SRC_FILES = ${addprefix ${DIR_SRCS}, ${SRCS}}

OBJ_FILES = ${addprefix ${DIR_SRCS}, ${OBJS}}

CFLAGS = -Wall -Wextra -Werror -g

CC = cc

RM = rm -f

%.o: %.c
	${CC} ${CFLAGS} -I ${DIR_INCLUDES} -lcurl $< -c -o $@

${NAME}: ${OBJ_FILES}
	${CC} ${CFLAGS} -I${DIR_INCLUDES}  ${OBJ_FILES} -lcurl -o ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJ_FILES}

fclean: clean
	${RM} ${NAME}

re : fclean all