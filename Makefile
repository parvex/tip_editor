# -Wall == all warnings enabled
# -Werror == treat warnings as ERRORS!
CPPFLAGS = --std=c++11 -Wall -Werror -DBOOST_TEST_DYN_LINK
LINKFLAGS = --std=c++11 -lboost_unit_test_framework

lib_SOURCES = \
	tip.h \
	point.h \
	container.h

lib_OBJECTS=$(lib_SOURCES:.cpp=.o)

tests_SOURCES = \
	tests_main.cpp \
	recttest.cpp

tests_OBJECTS=$(tests_SOURCES:.cpp=.o)

app_SOURCES = \
	main.cpp

app_OBJECTS=$(app_SOURCES:.cpp=.o)

tests_EXECUTABLE = tests_bin

all: rect tests

%.o : %.c
	$(CXX) -c $(CPPFLAGS) $< -o $@

$(tests_EXECUTABLE): $(tests_OBJECTS) $(lib_OBJECTS)
	$(CXX) -o $@ $(tests_OBJECTS) $(lib_OBJECTS) $(LINKFLAGS)

tests: $(tests_EXECUTABLE)
	./$(tests_EXECUTABLE)

rect: $(lib_OBJECTS) $(app_OBJECTS)
	$(CXX) -o $@ $(app_OBJECTS) $(lib_OBJECTS) $(LINKFLAGS)

.PHONY: clean tests

clean:
	- rm *.o
	- rm tests_bin
	- rm rect