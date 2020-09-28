COMPILEFLAGS=-Wall -Werror

all: bin/kurs format

bin/kurs: build/main.o build/handler.o build/menu.o
			$(CXX) $(COMPILEFLAGS) build/main.o build/handler.o build/menu.o -o $@ -std=c++11

build/main.o: src/main.cpp  
			$(CXX) $(COMPILEFLAGS) -I include -I src -c $< -o $@ -std=c++11

build/handler.o: src/handler.cpp include/handler.h
			$(CXX) $(COMPILEFLAGS) -I include -I src -c $< -o $@ -std=c++11

build/menu.o: src/menu.cpp include/menu.h
			$(CXX) $(COMPILEFLAGS) -I include -I src -c $< -o $@ -std=c++11

format: src/main.cpp
			clang-format -i src/main.cpp  src/handler.cpp  include/handler.h

clean:
	rm -rf build/*.o bin/kurs

run:
	cd bin/ && ./kurs