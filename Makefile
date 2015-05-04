all:
	$(CXX) -pthread -m64 -std=c++11 -O2 main.cpp -o algorithms22

test:
	 ./algorithms2 || exit 1

clean:
	rm algorithms2
