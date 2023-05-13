CYN = \033[36m
YEL = \033[33m
GRN = \033[32m
RST = \033[0m
PRP = \033[35m
RED = \033[91m
BPRP = \033[135m

SRCS	= 	srcs/dev.cpp \
			srcs/main.cpp \
			srcs/handleRequest.cpp \
			srcs/parsingRequest.cpp \
			srcs/sendResponse.cpp \
			srcs/errorResponses.cpp \
			srcs/manageSockets.cpp \
			srcs/args.cpp \
			srcs/Webserv.cpp \
			srcs/cgi.cpp \
			srcs/postRequest.cpp \
			srcs/receive.cpp \
			srcs/directoryListing.cpp \
			srcs/deleteRequest.cpp

NAME 	= webserv
COMP 	= c++
CXXFLAGS 	= -Wall -Wextra -Werror -std=c++98 -I include/

OBJS	= ${SRCS:.cpp=.o}

$(NAME):	$(OBJS)
			@echo "${PRP}-----compilation-----${RST}"
			@echo "[WEBSERV]	${CYN}Compilating... 🔨${RST}"
			@$(COMP) $(CXXFLAGS) $(OBJS) -o $(NAME)
			@echo "[WEBSERV]	${GRN}OK ${RST}"
			@echo "${GRN}Ready to execute ✅${RST}"

all:	$(NAME)

clean:
		@echo "${RED}-----destroying------${RST}"
		@echo "[WEBSERV]	${YEL}Deleting...${RST}"
		@rm -f ${OBJS}
		@echo "[WEBSERV]	${GRN}Cleaned 🧽${RST}"

fclean: clean
		@rm -f $(NAME)
		@echo "${GRN}Cleaning complete. 🗑${RST}"

re:		fclean all

cheaks:
		leaks --atExit -- ./${NAME}

.PHONY: all clean fclean re cheaks