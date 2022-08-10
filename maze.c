/////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT (v3)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement:
// https://student.cs.uwaterloo.ca/~cs136/current/assignments/integrity.shtml
/////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with:

// None
// 
// Name: Raj Saragadam
// login ID: rsaragad
/////////////////////////////////////////////////////////////////////////////

#include "maze.h"
#include "cs136-trace.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Your global constants go here.

struct maze {
  char *maze;
  int width;
  int height;
  // Additional fields go here.
  int maxlen;
  int len;
  int start_x;
  int start_y;
  int end_x;
  int end_y;
};

// See maze.h for documentation.
struct maze *maze_read(void) {
  struct maze *m1 = malloc(sizeof(struct maze));
  char wall = ' ';
  bool coldone = false;
  m1->height = 0;
  m1->width = 0;
  m1->len = 0;
  m1->maxlen = 1;
  int x = 0;
  m1->maze = malloc(m1->maxlen * sizeof(struct maze));
  while(1) {
    int n = scanf("%c", &wall);
    if (n == EOF) {
      break;
    } if (m1->len == m1->maxlen) {
      m1->maxlen *= 2;
      m1->maze = realloc(m1->maze, m1->maxlen * sizeof(struct 
                                                       maze));
    } if (wall != '\n' && wall != '\0') {
      if (!coldone) {
        m1->width++;
      } if (wall == 'S') {
        m1->start_x = x-1;
        m1->start_y = m1->height;
      } else if (wall == 'E') {
        m1->end_x = x-1;
        m1->end_y = m1->height;
      }
      m1->maze[m1->len] = wall;
      //trace_char(m1->maze[m1->len]);
      m1->len++;
    } else if (wall == '\n') {
      x = 0;
      coldone = true;
      m1->height++;
    }
    x++;
    //m1->maze[m1->len] = wall;
    //m1->len++;
  }
  //trace_int(m1->width);
  //trace_int(m1->height);
  trace_int(m1->start_x);
  trace_int(m1->start_y);
  trace_int(m1->end_x);
  trace_int(m1->end_y);
  //trace_string(m1->maze);
  return m1;
}

// See maze.h for documentation.
void maze_destroy(struct maze *maze) {
  assert(maze->maze);
  assert(maze);
  free(maze->maze);
  free(maze);
}
// coord(x, y) returns the char for a given (x, y) coordinate
// time:    O(n)
char coord(struct maze *m, int x, int y) {
  int pos = 0;
  for (int a = 0; a < x; a++) {
      //trace_char(m->maze[pos]);
      pos++;
      //trace_int(pos);
    }
  for (int i = 0; i < y; i++) {
    pos+=m->width;
    //trace_int(pos);
  }
  //trace_int(pos);
  return m->maze[pos];
}

/*
XXXXX
X   X
X X X
XSXEX
XXXXX
*/
// UURRDU   LLDURRDULL
// See maze.h for documentation.
// time: ???
void maze_solve(struct maze *maze) {
  int x = maze->start_x; // 1
  int y = maze->start_y; // 3
  //char n = coord(maze, 2, 3);
  //trace_char(n);
  bool up = true;
  bool down = false;
  bool left = false;
  bool right = false;
  
  while(1) {
    char pos = coord(maze, x, y);
    if (pos == 'E') {
      break;
    } else if (up) {
      //trace_char(coord(maze, x+1, y));
      if (coord(maze, x+1, y) == ' ' ||
          coord(maze, x+1, y) == 'E' ) {
        //trace_int(x);
        //trace_int(y);
        printf("R");
        //printf("R: Coord(%d, %d)\n", x, y);
        x = x+1;
        up = false;
        right = true;
      } else if (coord(maze, x, y-1) == ' ' || 
                 coord(maze, x, y-1) == 'E') {
        printf("U");
        y = y-1;
        up = true;
      } else if (coord(maze, x-1, y) == ' ' || 
                 coord(maze, x-1, y) == 'E') {
        printf("L");
        x = x-1;
        up = false;
        left = true;
      } else {
        printf("D");
        y = y+1;
        up = false;
        down = true;
      }
    } else if (down) {
      trace_int(x);
      trace_int(y);
      if (coord(maze, x-1, y) == ' ' ||
          coord(maze, x-1, y) == 'E') {
        printf("L");
        x = x-1;
        down = false;
        left = true;
      } else if (coord(maze, x, y+1) == ' ' || 
                 coord(maze, x, y+1) == 'E') {
        printf("D");
        y = y+1;
        down = true;
      } else if (coord(maze, x+1, y) == ' ' || 
                 coord(maze, x+1, y) == 'E') {
        printf("R");
        x = x+1;
        down = false;
        right = true;
      } else {
        printf("U");
        y = y -1;
        down = false;
        up = true;
      }
    } else if (left) {
      if (coord(maze, x, y-1) == ' ' || 
          coord(maze, x, y-1) == 'E') {
        printf("U");
        y = y-1;
        left = false; 
        up = true;
      } else if (coord(maze, x-1, y) == ' ' || 
                 coord(maze, x-1, y) == 'E') {
        printf("L");
        x = x-1;
        left = true; 
      } else if (coord(maze, x, y+1) == ' ' || 
                 coord(maze, x, y+1) == 'E') {
        printf("D");
        y = y+1;
        left = false;
        down = true; 
      } else {
        printf("R");
        x = x + 1;
        left = false;
        right = true;
      }
    } else if (right) {
      if (coord(maze, x, y+1) == ' ' || 
          coord(maze, x, y+1) == 'E') {
        printf("D");
        y = y+1;
        right = false;
        down = true;
      } else if (coord(maze, x+1, y) == ' ' || 
                 coord(maze, x+1, y) == 'E') {
        printf("R");
        x = x+1;
        right = true;
      } else if (coord(maze, x, y-1) == ' ' || 
                 coord(maze, x, y-1) == 'E') {
        printf("U");
        y = y-1;
        right = false;
        up = true;
      } else {
        printf("L");
        x = x-1;
        right = false;
        left = true;
      }
    }
  }
  printf("\n");
  // Your implementation goes here.
}