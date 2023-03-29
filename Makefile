SRCS	= srcs/dev.cpp srcs/main.cpp srcs/handleRequest.cpp srcs/parsingRequest.cpp srcs/sendResponse.cpp srcs/errorResponses.cpp srcs/manageSockets.cpp srcs/args.cpp
NAME 	= webserv
COMP 	= c++
CXXFLAGS 	= -Wall -Wextra -Werror -std=c++98

OBJS	= ${SRCS:.cpp=.o}

$(NAME):	$(OBJS)
	$(COMP) $(CXXFLAGS) $(OBJS) -o $(NAME)

all:	$(NAME)

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f $(NAME)

re:		fclean all

cheaks:
		leaks --atExit -- ./${NAME}

.PHONY: all clean fclean re cheaks