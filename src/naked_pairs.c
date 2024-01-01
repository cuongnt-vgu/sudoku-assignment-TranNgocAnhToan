#include "naked_pairs.h"

// check if two cells have the same two candidates (naked pair)
static int areNakedPair(Cell *cell1, Cell *cell2) {
    int count = 0;

    for (int value = 1; value <= BOARD_SIZE; ++value) {
        if (cell1->candidates[value - 1] != 0 && cell2->candidates[value - 1] != 0) {
            ++count;
        }
    }

    return count == 2; // Naked pair found
}

// find naked pairs in a unit (row, column, or box)
static int findNakedPairsInUnit(Cell **unit) {
    int pairCount = 0;

    // Iterate through all pairs of cells in the unit
    for (int i = 0; i < BOARD_SIZE - 1; ++i) {
        for (int j = i + 1; j < BOARD_SIZE; ++j) {
            if (areNakedPair(unit[i], unit[j])) {
                // Process the naked pair
                for (int value = 1; value <= BOARD_SIZE; ++value) {
                    if (unit[i]->candidates[value - 1] != 0) {
                        unset_candidate(unit[i], value);
                    }
                }

                // Set the pair values as the final values for the naked pair
                set_candidate(unit[i], unit[i]->candidates[0]);
                set_candidate(unit[i], unit[j]->candidates[0]);
                
                ++pairCount;
            }
        }
    }

    return pairCount;
}

// find naked pairs in rows, columns, and boxes of the Sudoku board
int naked_pairs(SudokuBoard *p_board) {
    int totalPairCount = 0;

    // Iterate through rows
    for (int i = 0; i < BOARD_SIZE; ++i) {
        totalPairCount += findNakedPairsInUnit(p_board->p_rows[i]);
    }

    // Iterate through columns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        totalPairCount += findNakedPairsInUnit(p_board->p_cols[i]);
    }

    // Iterate through boxes
    for (int i = 0; i < BOARD_SIZE; ++i) {
        totalPairCount += findNakedPairsInUnit(p_board->p_boxes[i]);
    }

    return totalPairCount;
}
