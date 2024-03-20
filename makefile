CXXFLAGS = -Ofast -fno-signed-zeros -fno-trapping-math -flto -funroll-loops -Wall -Wextra -pedantic -std=c++23 -march=native -I inc
CPPFLAGS += -isystem $(GTEST_DIR)/include

FILES = utils Planete
TEST_FILES = testUtils
TARGET = simulation

SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests

SOURCES = $(foreach src,$(FILES),$(addprefix $(SRC_DIR)/,$(addsuffix .cpp,$(src))))
OBJECTS = $(subst $(SRC_DIR),$(OBJ_DIR),$(subst .cpp,.o,$(SOURCES)))
TESTS = $(foreach test,$(TEST_FILES),$(addprefix $(TEST_DIR)/,$(test)))
TESTS_SRC = $(foreach test,$(TEST_FILES),$(addprefix $(TEST_DIR)/src/,$(addsuffix .cpp,$(test))))
TESTS_OBJ = $(foreach test,$(TEST_FILES),$(addprefix $(TEST_DIR)/obj/,$(addsuffix .o,$(test))))

GTEST_DIR = /usr/src/googletest/googletest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)


$(TARGET): $(OBJECTS) src/$(TARGET).cpp
	g++ $(CXXFLAGS) $^ -o $(TARGET)

all: $(TARGET) $(TESTS)

tests: $(TESTS)

clean:
	rm -fv $(TARGET) $(OBJECTS) $(TESTS_OBJ) obj/gtest-all.o obj/gtest_main.o

$(OBJECTS): obj/%.o: src/%.cpp
	g++ $(CXXFLAGS) $^ -c -o $@

obj/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc -o obj/gtest-all.o

obj/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc -o obj/gtest_main.o

gtest.a : ./obj/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : ./obj/gtest-all.o ./obj/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

$(TESTS): tests/%: tests/obj/%.o gtest_main.a $(OBJECTS)
	g++ $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

$(TESTS_OBJ): tests/obj/%.o: tests/src/%.cpp $(GTEST_HEADERS)
	g++ $(CPPFLAGS) $(CXXFLAGS) $(subst obj,src,$(subst .o,.cpp,$@)) -c -o $@
