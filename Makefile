COMPILEFLAGS=-Wall -Werror

all: bin/kurs format

bin/kurs: build/main.o build/handler.o
			$(CXX) $(COMPILEFLAGS) build/main.o build/handler.o -o $@

build/main.o: src/main.cpp  
			$(CXX) $(COMPILEFLAGS) -I include -I src -c $< -o $@

build/handler.o: src/handler.cpp include/handler.h
			$(CXX) $(COMPILEFLAGS) -I include -I src -c $< -o $@

format: src/main.cpp
			clang-format -i src/main.cpp  src/handler.cpp  include/handler.h

clean:
	rm -rf build/*.o bin/kurs

run:
	cd bin/ && ./kurs