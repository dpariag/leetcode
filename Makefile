CPP_PROGS := \
	nth_digit

CFLAGS := -std=c99
CPPFLAGS := -std=c++1y -g -Werror -Wall -pedantic

.PHONY: all

all: $(CPP_PROGS) 

%: %.c
	@echo "Building $@..."
	@gcc $(CFLAGS) $*.c -o $@
	@rm -rf $@.dSYM

%: %.cpp
	@echo "Building $@..."
	@g++ $(CPPFLAGS) $*.cpp -o $@
	@rm -rf $@.dSYM


%: %.go
	@echo "Go build $@..."
	@go build $*.go

count:
	@ls -tr *.go *.cpp *.h *.c | xargs wc -l | nl

clean:
	@echo "Cleaning..."
	@rm -f *.o $(CPP_PROGS) $(C_PROGS) $(GO_PROGS)
	@rm -rf *.dSYM
	@rm -f  *.aux *.dvi *.ps *.log *.pdf
