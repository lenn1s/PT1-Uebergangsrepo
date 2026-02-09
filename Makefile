ARGS ?=

_CXX_CLANG := $(shell command -v clang++ 2>/dev/null)
_CXX_GCC   := $(shell command -v g++ 2>/dev/null)

ifeq ($(_CXX_CLANG),)
    ifeq ($(_CXX_GCC),)
        $(error "Neither clang++ nor g++ found in PATH. Please install one.")
    else
        COMPILER = g++
    endif
else
    COMPILER = clang++
endif

# --- flags / dirs -------------------------------------------------------------

OPTIONS      = -std=c++17 -Isrc -g -MMD -MP
TEST_OPTIONS = -std=c++17 -Isrc -Idoctest/doctest -Wall -Wextra -pedantic -g -MMD -MP

BUILD = out
TESTS = tests

EXE_SUFFIX =
ifeq ($(findstring MINGW,$(shell uname -s)),MINGW)
    EXE_SUFFIX = .exe
endif

COMPILE      = $(COMPILER) $(OPTIONS)
TEST_COMPILE = $(COMPILER) $(TEST_OPTIONS)

MAIN_EXECUTABLE = $(BUILD)/main$(EXE_SUFFIX)
TEST_EXECUTABLE = $(BUILD)/tests$(EXE_SUFFIX)

SRC_DIR = src
OBJ_DIR = $(BUILD)/obj
TEST_OBJ_DIR = $(OBJ_DIR)/tests

# --- project sources ----------------------------------------------------------
# main binary consists of main.cpp + the "library" sources in src/
SOURCES = $(SRC_DIR)/generator.cpp $(SRC_DIR)/sorting.cpp $(SRC_DIR)/main.cpp
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# tests binary should *not* link main.o (because doctest provides its own main)
LIB_OBJECTS = $(filter-out $(OBJ_DIR)/main.o,$(OBJECTS))

# tests/*.cpp (besides tests.cpp) are compiled and linked too (if they exist)
TEST_SOURCES = $(filter-out $(TESTS)/tests.cpp,$(wildcard $(TESTS)/*.cpp))
TEST_ALL_SOURCES = $(TESTS)/tests.cpp $(TEST_SOURCES)
TEST_ALL_OBJECTS = $(TEST_ALL_SOURCES:$(TESTS)/%.cpp=$(TEST_OBJ_DIR)/%.o)

# --- targets -----------------------------------------------------------------

main-compile: prep $(OBJECTS)
	$(COMPILER) -o $(MAIN_EXECUTABLE) $(OBJECTS)
ifeq ($(EXE_SUFFIX),)
	chmod +x $(MAIN_EXECUTABLE)
endif

main: main-compile
	$(MAIN_EXECUTABLE) $(ARGS)

test-compile: prep $(LIB_OBJECTS) $(TEST_ALL_OBJECTS)
	$(COMPILER) $(TEST_OPTIONS) $(TEST_ALL_OBJECTS) $(LIB_OBJECTS) -o $(TEST_EXECUTABLE)
ifeq ($(EXE_SUFFIX),)
	chmod +x $(TEST_EXECUTABLE)
endif

tests: test-compile
	$(TEST_EXECUTABLE)

# --- object rules ------------------------------------------------------------

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(COMPILE) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(TESTS)/%.cpp | $(TEST_OBJ_DIR)
	$(TEST_COMPILE) -c $< -o $@

# --- directories / housekeeping ---------------------------------------------

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

prep:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

.PHONY: clean prep main tests main-compile test-compile

-include $(OBJECTS:.o=.d) $(TEST_ALL_OBJECTS:.o=.d)