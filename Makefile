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
	max_word_lengths \
	burst_balloons \
	contiguous_array \
	duplicate_subtrees \
	max_tree_width \
	bitwise_and_range \
	number_islands \
	largest_divisible_subset \
	distinct_subsequences \
	edit_distance \
	russian_doll_envelopes \
	reverse_list \
	distinct_subsequences \
	trapping_rain_water \
	remove_k_digits \
	total_hamming_distance \
	valid_square \
	non_overlapping_intervals \
	smallest_range \
	is_subsequence \
	remove_invalid_parens \
	k_diff_pairs \
	valid_palindrome_2 \
	find_k_closest \
	power_of_four \
	right_side_view \
	range_sum_2d_immutable \
	array_partition_1 \
	find_right_interval \
	integer_replacement \
	palindrome_list \
	lca_bst \
	add_strings \
	longest_word_in_dict \
	binary_tree_levels_2 \
	4sum \
	remove_nth_from_end \
	min_rotated_array \
	next_greater_3 \
	diameter_binary_tree \
	gas_station \
	valid_parenthesis_string \
	course_schedule_2 \
	guess_number_2 \
	redundant_connection \
	linked_list_cycle2 \
	can_i_win \
	elimination_game \
	decode_string \
	delete_op_two_strings \
	4sum_2 \
	matchsticks_to_square \
	buy_sell_cooldown \
	target_sum \
	palindrome_number \
	maximum_swap \
	subsets \
	range_addition_2 \
	predict_the_winner \
	sort_char_frequency \
	pacific_atlantic \
	min_moves_equal \
	min_moves_equal2 \
	flatten_binary_tree \
	find_all_anagrams \
	find_celebrity \
	plus_one \
	subarray_product \
	excel_column_title \
	non_decreasing_array \
	multiply_strings \
	rectangle_area \
	valid_palindrome \
	queue_reconstruct \
	android_unlock \
	island_perimeter \
	longest_substring_k_distinct \
	moving_average \
	letter_combos_phone \
	diagonal_traverse \
	flip_game \
	flip_game2 \
	meeting_rooms \
	meeting_rooms2 \
	one_edit_distance \
	task_scheduler \
	max_subarray_sum_k \
	license_key_formatting \
	wiggle_sort \
	repeated_string_match \
	paint_fence \
	binary_tree_vertical_traversal \
	range_sum_2d_mutable \
	longest_substring_2_distinct \
	word_squares \
	linked_list_random_node \
	in_order_succ_bst \
	lca_binary_tree \
	simplify_path \
	evaluate_division \
	valid_word_square \
	consecutive_subseq \
	accounts_merge \
	walls_and_gates \
	missing_ranges \
	shortest_distance_buildings \
	sort_transformed_array \
	sparse_matrix \
	k_empty_slots \
	basic_calculator2 \
	odd_even_list \
	add_two_numbers \
	nim_game \
	median_two_sorted_arrays \
	buy_sell_fee \
	sum_of_left_leaves \
	regex_matching \
	single_elem_sorted \
	contains_duplicate_3 \
	invert_binary_tree \
	copy_list_random_ptr \
	circular_array_loop \
	add_digits \
	reverse_polish_notation \
	triangle \
	sorted_array_to_bst \
	largest_rectangle_histogram \
	integer_break \
	combinations \
	longest_abs_file_path \
	ransom_note \
	rotate_image \
	single_number \
	word_pattern \
	frog_jump \
	single_number_3 \
	best_meeting_point \
	insert_delete_random \
	combinations_3 \
	flatten_nested_list \
	binary_tree_sequence \
	add_bold_tag \
	min_stack

CFLAGS := -std=c99
CPPFLAGS := -std=c++1y -g -Werror -Wall -pedantic  -Wno-sign-compare

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
