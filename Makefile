SRCS= $(wildcard *.cpp)
betazero: $(SRCS)
	g++ *.cpp -o $@

run: betazero
	./betazero