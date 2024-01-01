#include "naked_triples.h"
// check if three cells have the same three candidates (naked triple)
static int areNakedTriple(Cell *cell1, Cell *cell2, Cell *cell3) {
    int count = 0;

    for (int value = 1; value <= BOARD_SIZE; ++value) {
        if (cell1->candidates[value - 1] != 0 && cell2->candidates[value - 1] != 0 &&
            cell3->candidates[value - 1] != 0) {
            ++count;
        }
    }

    return count == 3; // Naked triple found
}

// find naked triples in a unit (row, column, or box)
static int findNakedTriplesInUnit(Cell **unit) {
    int tripleCount = 0;

    // Iterate through all triples of cells in the unit
    for (int i = 0; i < BOARD_SIZE - 2; ++i) {
        for (int j = i + 1; j < BOARD_SIZE - 1; ++j) {
            for (int k = j + 1; k < BOARD_SIZE; ++k) {
                if (areNakedTriple(unit[i], unit[j], unit[k])) {
                    // Process the naked triple
                    for (int value = 1; value <= BOARD_SIZE; ++value) {
                        if (unit[i]->candidates[value - 1] != 0) {
                            unset_candidate(unit[i], value);
                        }
                    }

                    // Set the triple values as the final values for the naked triple
                    set_candidate(unit[i], unit[i]->candidates[0]);
                    set_candidate(unit[i], unit[j]->candidates[0]);
                    set_candidate(unit[i], unit[k]->candidates[0]);

                    ++tripleCount;
                }
            }
        }
    }

    return tripleCount;
}

//  find naked triples in rows, columns, and boxes of the Sudoku board
int naked_triples(SudokuBoard *p_board) {
    int totalTripleCount = 0;

    // Iterate through rows
    for (int i = 0; i < BOARD_SIZE; ++i) {
        totalTripleCount += findNakedTriplesInUnit(p_board->p_rows[i]);
    }

    // Iterate through columns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        totalTripleCount += findNakedTriplesInUnit(p_board->p_cols[i]);
    }

    // Iterate through boxes
    for (int i = 0; i < BOARD_SIZE; ++i) {
        totalTripleCount += findNakedTriplesInUnit(p_board->p_boxes[i]);
    }

    return totalTripleCount;
}
