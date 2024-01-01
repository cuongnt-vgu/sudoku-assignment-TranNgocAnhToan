// hidden_triples.c

#include "hidden_triples.h"

// Helper function to check if three cells have the same three candidates
static int areHiddenTriple(Cell *cell1, Cell *cell2, Cell *cell3) {
    for (int value = 1; value <= BOARD_SIZE; ++value) {
        if (cell1->candidates[value - 1] != 0 &&
            cell2->candidates[value - 1] != 0 &&
            cell3->candidates[value - 1] != 0) {
            return 1; // Hidden triple found
        }
    }
    return 0; // Not a hidden triple
}

// Helper function to find hidden triples in a unit (row, column, or box)
static int findHiddenTriplesInUnit(Cell **unit) {
    int tripleCount = 0;

    // Iterate through all triples of cells in the unit
    for (int i = 0; i < BOARD_SIZE - 2; ++i) {
        for (int j = i + 1; j < BOARD_SIZE - 1; ++j) {
            for (int k = j + 1; k < BOARD_SIZE; ++k) {
                if (areHiddenTriple(unit[i], unit[j], unit[k])) {
                    // Process the hidden triple
                    // Update the cells accordingly
                    for (int value = 1; value <= BOARD_SIZE; ++value) {
                        if (unit[i]->candidates[value - 1] != 0) {
                            unset_candidate(unit[i], value);
                        }
                        if (unit[j]->candidates[value - 1] != 0) {
                            unset_candidate(unit[j], value);
                        }
                        if (unit[k]->candidates[value - 1] != 0) {
                            unset_candidate(unit[k], value);
                        }
                    }

                    // Set the triple values as the final values for the hidden triple
                    set_candidate(unit[i], unit[j]->candidates[0]);
                    set_candidate(unit[j], unit[i]->candidates[0]);
                    set_candidate(unit[i], unit[k]->candidates[0]);
                    set_candidate(unit[k], unit[i]->candidates[0]);

                    ++tripleCount;
                }
            }
        }
    }

    return tripleCount;
}

// Function to find hidden triples in rows, columns, and boxes of the Sudoku board
int hidden_triples(SudokuBoard *p_board) {
    int totalTripleCount = 0;

    // Iterate through rows
    for (int i = 0; i < BOARD_SIZE; ++i) {
        totalTripleCount += findHiddenTriplesInUnit(p_board->p_rows[i]);
    }

    // Iterate through columns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        totalTripleCount += findHiddenTriplesInUnit(p_board->p_cols[i]);
    }

    // Iterate through boxes
    for (int i = 0; i < BOARD_SIZE; ++i) {
        totalTripleCount += findHiddenTriplesInUnit(p_board->p_boxes[i]);
    }

    return totalTripleCount;
}
