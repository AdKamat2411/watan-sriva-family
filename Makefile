CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g


SRCS = main.cc gamemanager.cc board.cc dice.cc player.cc randomboardsetup.cc \
       tile.cc edge.cc vertex.cc subject.cc observer.cc fileboardsetup.cc \
       savemanager.cc geese.cc


OBJS = $(SRCS:.cc=.o)

HEADERS = gamemanager.h board.h dice.h player.h randomboardsetup.h \
          tile.h edge.h vertex.h subject.h observer.h fileboardsetup.h \
          savemanager.h geese.h

TARGET = watan

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
