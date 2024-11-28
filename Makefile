CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRCS = main.cc gamemanager.cc board.cc tile.cc vertex.cc edge.cc dice.cc geese.cc boardsetup.cc randomboardsetup.cc fileboardsetup.cc
OBJS = $(SRCS:.cc=.o)

HEADERS = gamemanager.h board.h tile.h vertex.h edge.h dice.h geese.h boardsetup.h randomboardsetup.h fileboardsetup.h

TARGET = game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
