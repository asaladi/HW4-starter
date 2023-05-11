/**
 * Assignment: life
 * Name: TODO
 * PID: TODO
 * Class: UCSD CSE30-SP21
 *
 */
#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, size_t, size_t, size_t);

/**
 * gets x mod N (works for negative numbers as well! Use this instead of %)
 */
size_t getModVal(int x, size_t N){
     size_t adj = x/N;

     return((x+adj*N)%N);
}

/**
 * process one row of the board
 */
static void doRow(belem *dest, belem *src, size_t row, size_t rows, size_t cols){
  int check_cell = 0;
  int neighbor_cell = 0;
  for(int i = 0; i< (int)cols; i++){
    check_cell = getIndex(cols,row,i);
    int alive_count = 0;
    
    for(int r = -1; r<=1; r++){
      for(int c = -1; c<=1; c++){
        neighbor_cell = getModVal(getModVal(check_cell+c,cols)+(r*cols),rows*cols);

        if (*(src+neighbor_cell)==1){
          alive_count++;
        }
      } 
    }

    if (*(src+check_cell)==1){
      if(alive_count!=2 && alive_count!=3){
        *(dest+check_cell)=0;
      }
    }
    else{
      if(alive_count==3){
        *(dest+check_cell)=1;
      }
    }
  }
}


/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void simLoop(boards_t *self, unsigned int steps){
  for(int i = 0; i<(int)steps; i++){
    for(int r = 0; r<(int)(self->numRows); r++){
      doRow(self->bufferA, self->bufferB, (size_t)r, self->numRows, self->numCols);
    }
    swapBuffers(self);
  }
}
