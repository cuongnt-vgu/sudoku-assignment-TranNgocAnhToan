
#include "hidden_singles.h"
#include <stddef.h>

// function to find hidden single values in a row, column, or box
int find_hidden_single_values(Cell **p_cells, int *hidden_single_values) {
    int count = 0;

    // Iterate through possible values (candidates)
    for (int value = 1; value <= BOARD_SIZE; ++value) {
        int candidate_count = 0;
        Cell *hidden_single_cell = NULL;

        // Iterate through cells
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (p_cells[i]->candidates[value - 1] != 0) {
                ++candidate_count;
                hidden_single_cell = p_cells[i];
            }
        }

        // If only one candidate is found, it's a hidden single
        if (candidate_count == 1) {
            hidden_single_values[count++] = value;
            hidden_single_cell->value = value;
            hidden_single_cell->num_candidates = 1; // The cell is now solved
        }
    }

    return count;
}

// find hidden single cells in a row, column, or box
void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles, int *p_counter) {
    // Iterate through cells
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (p_cells[i]->num_candidates > 1) {
            int hidden_single_values[BOARD_SIZE];
            int count = find_hidden_single_values(p_cells, hidden_single_values);

            // If hidden single values are found, add them to the array
            for (int j = 0; j < count; ++j) {
                p_hidden_singles[*p_counter].p_cell = p_cells[i];
                p_hidden_singles[*p_counter].value = hidden_single_values[j];
                ++(*p_counter);
            }
        }
    }
}

// Function to find hidden single cells in a board, return the number of hidden single cells
int hidden_singles(SudokuBoard *p_board) {
    HiddenSingle hidden_singles_array[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;

    // Iterate through rows
    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_hidden_single(p_board->p_rows[i], hidden_singles_array, &counter);
    }

    // Iterate through columns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_hidden_single(p_board->p_cols[i], hidden_singles_array, &counter);
    }

    // Iterate through boxes
    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_hidden_single(p_board->p_boxes[i], hidden_singles_array, &counter);
    }

    return counter;
}
