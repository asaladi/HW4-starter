/**
 * Assignment: life
 * Name :Annapurna Saladi :)
 * PID: A17417895
 * Class: UCSD CSE30-SP21
 *
 */
#include "cse30life.h"
#include "board.h"


/**
 * create a new board
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB 
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - close the file
 * - return the boards pointer if successfull or NULL ptr otherwise
 */
boards_t * createBoard(char *initFileName){
  boards_t * board = (boards_t *) malloc(sizeof(boards_t *));
  board->gen = 0;

  unsigned int len = 0;
  char *readbuffer = NULL;
  int row = 0;
  int col = 0;
  int numLine = 0;
  int numRows = 0;
  int numCols = 0;

  while (getline(&readbuffer, &len, *initFileName) != -1){
    char* ptr = readbuffer;
    if(numLine==0){
      numRows = atoi(ptr);
      board->numRows = (size_t)numRows;      
    }
    else if(numLine==1){
      numCols = atoi(ptr);
      board->numCols = (size_t)numCols;
      board->bufferA = calloc((numRows*numCols),sizeof(belem));
      board->bufferB = calloc((numRows*numCols),sizeof(belem));
    }
    else{
      row = atoi(ptr);
      col = atoi(ptr+2);
      *(board->bufferA+(row*numCols+col)) = 1;
      *(board->bufferB+(row*numCols+col)) = 1;
    }
    numLine++;
  }
  board->currentBuffer = (board->bufferA);
  (board->nextBuffer) = (board->bufferB);
  return board;
}



/**
 * delete a board
 */
void deleteBoard(boards_t **bptrPtr){
  free((*bptrPtr)->bufferA);
  free((*bptrPtr)->bufferB);
  free((*bptrPtr)->currentBuffer);
  free((*bptrPtr)->nextBuffer);
  /*
  free((*bptrPtr)->numRows);
  free((*bptrPtr)->numCols);
  free((*bptrPtr)->gen);*/
  *bptrPtr=NULL;
}

/**
 * set all the belems in both buffers to 0
 */
void clearBoards(boards_t *self){
  for(int i = 0; (int)i<(int)((self->numCols)*(self->numCols)); i++){
    *(self->bufferA + i) = 0;
    *(self->bufferB + i) = 0;
  }
}

/**
 * swap the current and next buffers
 */
void swapBuffers(boards_t *self){
  self->currentBuffer = self->bufferB;
  self->nextBuffer = self->bufferA;
}


/**
 * get a cell index
 */
size_t getIndex(size_t numCols, size_t row, size_t col){
  return (size_t)row*numCols+col;
}
  
