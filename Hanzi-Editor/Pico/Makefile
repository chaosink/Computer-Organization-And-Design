GLFW = `pkg-config --cflags glfw3` `pkg-config --libs --static glfw3`

all: pico

pico: main.cpp pico.cpp pinyin2code.cpp key.cpp error.cpp pico.hpp 
	clang++ main.cpp pico.cpp pinyin2code.cpp key.cpp error.cpp -o pico $(GLFW) -std=c++11
