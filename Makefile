SRCS= $(wildcard *.cpp)
betazero: $(SRCS)
	g++ *.cpp -o $@

o3:
	g++ main.cpp -O3 -o betazero

run: betazero
	./betazero
