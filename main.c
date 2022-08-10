#include "maze.h"

int main(void) {
  struct maze *maze = maze_read();
  maze_solve(maze);
  maze_destroy(maze);
}