CC				= gcc 
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I./includes
SERVER_NAME 	= server
CLIENT_NAME		= client 
SERVER_SRCS		= ./srcs/server.c ./srcs/utils/server_utils.c
CLIENT_SRCS		= ./srcs/client.c ./srcs/utils/client_utils.c
SERVER_OBJS 	= $(SERVER_SRCS:.c=.o)
CLIENT_OBJS		= $(CLIENT_SRCS:.c=.o)


all:				$(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME):		$(SERVER_OBJS)
					$(CC) -o $(SERVER_NAME) $(SERVER_SRCS) $(CFLAGS) 

$(CLIENT_NAME):		$(CLIENT_OBJS) 
					$(CC) -o $(CLIENT_NAME) $(CLIENT_SRCS) $(CFLAGS)  

clean:
				$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)
				 
fclean:	 		clean
				$(RM) $(SERVER_NAME) $(CLIENT_NAME)
	
re:				fclean all

.PHONY:			all clean fclean re