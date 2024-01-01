#include "hidden_pairs.h"


static int areHiddenPair(Cell *cell1, Cell *cell2) {
    // Check if the candidates of cell1 and cell2 are the same
    if (cell1->num_candidates == 2 && cell2->num_candidates == 2) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (cell1->candidates[i] != 0 && cell2->candidates[i] != 0) {
                return 1; // Hidden pair found
            }
        }
    }
    return 0; // Not a hidden pair
}

// Function to find hidden pairs in a unit (row, column, or box)
static int findHiddenPairsInUnit(Cell **unit) {
    int pairCount = 0;

    // Iterate through all pairs of cells in the unit
    for (int i = 0; i < BOARD_SIZE - 1; ++i) {
        for (int j = i + 1; j < BOARD_SIZE; ++j) {
            if (areHiddenPair(unit[i], unit[j])) {
                // Process the hidden pair
                for (int k = 0; k < BOARD_SIZE; ++k) {
                    if (unit[i]->candidates[k] != 0) {
                        // Set the candidates as the final values for the hidden pair
                        set_candidate(unit[j], k + 1);
                    }
                }

                // Increment pairCount and perform any other necessary actions
                ++pairCount;
            }
        }
    }

    return pairCount;
}

int hidden_pairs(SudokuBoard *p_board)
{
    int totalPairCount = 0;
    // Iterate through rows
    for (int i = 0; i < BOARD_SIZE; ++i) {
        totalPairCount += findHiddenPairsInUnit(p_board->p_rows[i]);
    }
    // Iterate through columns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        totalPairCount += findHiddenPairsInUnit(p_board->p_cols[i]);
    }
    // Iterate through boxes
    for (int i = 0; i < BOARD_SIZE; ++i) {
        totalPairCount += findHiddenPairsInUnit(p_board->p_boxes[i]);
    }

    return totalPairCount;
}
