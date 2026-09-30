# ---- Ce que tu adaptes à chaque exercice ----
NAME    = a.out
SRCS    = main.cpp
# ---------------------------------------------

CXX     = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

HEADERS = Cat.hpp Dog.hpp

OBJS    = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
