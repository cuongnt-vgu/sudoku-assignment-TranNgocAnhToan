#include "hidden_pairs.h"

int hidden_pairs(SudokuBoard* p_board) {

  int i, j, k;
  int found = 0;
  
  // Loop through each row
  for (i = 0; i < BOARD_SIZE; i++) {

    // Track pairs in row
    int pairs[BOARD_SIZE][2];
    int num_pairs = 0;

    // Loop through each cell in row
    for (j = 0; j < BOARD_SIZE; j++) {
    
      Cell* cell = p_board->p_rows[i][j];
      
      // Skip solved cells
      if (cell->num_candidates != 2) continue;

      // Add pair
      pairs[num_pairs][0] = cell->candidates[0];
      pairs[num_pairs][1] = cell->candidates[1];
      num_pairs++;
    }

    // Check for duplicate pairs
    for (j = 0; j < num_pairs; j++) {
      for (k = j + 1; k < num_pairs; k++) {
      
        // Found duplicate pair
        if (pairs[j][0] == pairs[k][0] && 
            pairs[j][1] == pairs[k][1]) {
            
          int val1 = pairs[j][0];
          int val2 = pairs[j][1];
          
          // Remove this pair from all other cells in row
          for (int m = 0; m < BOARD_SIZE; m++) {
            Cell* cell = p_board->p_rows[i][m];
            if (cell->num_candidates > 2) {
              unset_candidate(cell, val1);
              unset_candidate(cell, val2);
            }
          }
          
          found++;
        }
      }
    }
  }

  // Repeat for columns and boxes

  return found;
}
