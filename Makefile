CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
TESTFLAGS = -lgtest -lgtest_main -pthread
CHECKFLAGS = $(shell pkg-config --flags --libs check)
CFLAGS_COVERAGE = -fprofile-arcs -ftest-coverage
# Пути к исходным файлам
FUNC_SOURCES = $(wildcard ./function/*.cpp)

# Пути к объектным файлам
FUNC_OBJECTS = $(patsubst ./function/%.cpp, OBJ/%.o, $(FUNC_SOURCES))


# Пути к исходным файлам тестов
TEST_SOURCES = $(wildcard ./test/*.cpp)

# Пути к объектным файлам тестов
TEST_OBJECTS = $(patsubst ./test/%.cpp, OBJ/%.o, $(TEST_SOURCES))

# Имя библиотеки
LIBRARY = s21_matrix_oop.a

# Правило для сборки библиотеки
all: $(LIBRARY)

$(LIBRARY): $(FUNC_OBJECTS)
	ar rcs $@ $^

# Цель для сборки тестов
test: $(LIBRARY) $(TEST_OBJECTS)
	$(CC) -o test_executable $(TEST_OBJECTS) -L. -l:$(LIBRARY) $(TESTFLAGS)
	./test_executable

val: clean test
	valgrind --leak-check=full --show-leak-kinds=all ./test_executable

OBJ/%.o: ./function/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -lm

OBJ/%.o: ./test/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -L. -l$(LIBRARY) $(TESTFLAGS)

clean: clean_gcov
	rm -rf OBJ/ $(LIBRARY) *.log *.o test_executable

gcov_report: CFLAGS += $(CFLAGS_COVERAGE)
gcov_report: clean $(LIBRARY) $(TEST_OBJECTS) $(FUNC_OBJECTS)
	$(CC) $(CFLAGS) $(CHECKFLAGS) -o test_executable $(TEST_OBJECTS) $(FUNC_OBJECTS) -lgtest -lgtest_main
	./test_executable
	rm -rf ./OBJ/*_test*
	gcov -o OBJ/ $(FUNC_OBJECTS)
	gcovr -r . --html-details -o coverage_report.html
	@mkdir -p OBJ_gcov
	@mv *.gcov *.html *.css OBJ_gcov

gcov_show:
	xdg-open ./OBJ_gcov/coverage_report.html
 
peer: gcov_report gcov_show
 
clean_gcov:
	rm -rf *.gcno *.gcda *.gcov coverage_report.html *.html *.css OBJ_gcov
