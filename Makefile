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
	number_of_bits \
	remove_duplicates \
	remove_duplicates_2 \
	single_number \
	single_number_2 \
	palindrome_partitioning \
	move_zeroes \
	longest_palindrome \
	longest_valid_parens \
	array_product_except_self \
	arranging_coins \
	peak_element \
	sort_colors \
	rotate_array \
	reverse_words \
	palindrome_pairs \
	min_depth_binary_tree \
	perfect_squares \
	partition_list \
	majority_element \
	majority_element2 \
	group_anagrams \
	min_window_substring \
	remove_duplicates_list \
	remove_duplicates_list_2 \
	clone_graph \
	interleaving_string \
	reverse_integer \
	two_sum \
	candy \
	contains_duplicate_2 \
	n_queens \
	equal_partitions \
	binary_tree_levels \
	reorder_list \
	delete_bst_node \
	first_missing_positive \
	rotate_function \
	lexicographical_numbers \
	merge_k_sorted_lists \
	decode_ways \
	reverse_vowels \
	increasing_triplet \
	brick_wall \
	continuous_subarray_sum \
	array_duplicates\
	sliding_window_max \
	lru_cache \
	surrounded_regions \
	path_sum \
	path_sum_2 \
	range_sum \
	repeated_substring \
	longest_harmonious \
	next_greater \
	no_consecutive_ones \
	concatenated_words \
	container_most_water \
	h_index \
	generate_parentheses \
	longest_repeating_char_replacement \
	binary_tree_zigzag \
	search_rotated_array \
	in_order_iterative \
	01_matrix \
	swap_nodes_in_pairs \
	maximum_path_sum \
	permutations \
	permutations_2 \
	sliding_window_median \
	max_word_lengths



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
