# ---- Ce que tu adaptes à chaque exercice ----
NAME    = megaphone
SRCS    = megaphone.cpp
# ---------------------------------------------

CXX     = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

OBJS    = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
