all: clean build start

build:
	g++ *.cpp lab.h

start:
	./a.out

style:
	cppcheck --language=c++ *.cpp *.h
	clang-format -n *.cpp *.h

clean:
	rm -rf a.out *.gch
