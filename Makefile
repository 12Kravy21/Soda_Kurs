COMPILEFLAGS=-Wall -Werror
FILESCPP = $(wildcard src/*.cpp)
OBJECTS = $(subst src/,build/,$(subst .cpp,.o,$(FILESCPP)))

all: bin/kurs format

bin/kurs: $(OBJECTS)
			$(CXX) $(COMPILEFLAGS) $^ -o $@ -std=c++11

build/%.o: src/%.cpp
			$(CXX) $(COMPILEFLAGS) -I include -I src -c $< -o $@

format:
			clang-format -i $(FILESCPP) $(wildcard include/*.h)

clean:
	rm -rf build/*.o bin/kurs

run:
	cd bin/ && ./kurs