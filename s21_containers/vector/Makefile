CC=gcc
CFL=-Wall -Werror -Wextra
SFL=-lstdc++ -std=c++17 -Wpedantic

run:
	$(CC) $(CFL) $(SFL) main.cc -o run
	./run
	rm run
.PHONY: run

debug:
	$(CC) $(CFL) $(SFL) -g main.cc -o debug
	lldb ./debug
.PHONY: debug

style-check:
	clang-format -style=google *.cc *.h -n
.PHONY: style-check

style-format:
	clang-format -style=google *.cc *.h -i
.PHONY: style-format
