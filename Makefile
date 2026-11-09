CPP 	=	c++
WFLAGS	=	-Wall -Wextra -Werror
C98		=	-std=c++98

NAME	=	main

SRCS	=	main.cpp

OBJS	= 	$(SRCS:.cpp=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CPP) $(WFLAGS) $(C98) $(OBJS) -o $(NAME)

%.o		: %.cpp
	$(CPP) $(WFLAGS) $(C98) -c $< -o $@

clean	:
		rm -f $(OBJS)

fclean	:	clean
		rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
#.SILENT	:
