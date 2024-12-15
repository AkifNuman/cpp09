CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11

NAME = RPN

SRCS = main.cpp RPN.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
    rm -f $(OBJS)

fclean: clean
    rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re