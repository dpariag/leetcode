CPP_PROGS := \
	nth_digit \
	search_range \
	rotate_list \
	first_missing_positive \
	dna_sequences \
	jump_game \
	jump_game_2 \
	isomorphic_strings \
	sum_root_leaf_numbers \
	find_kth_largest \
	3sum \
	divide_two_integers \
	maximum_subarray \
	word_break \
	3sum_closest \
	array_intersection \
	word_break_2 \
	third_maximum_number \
	maximal_xor \
	number_of_bits

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
