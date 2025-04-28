
#include <stdio.h>
#include <stdlib.h>

#define ROW 5
#define COL 5

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point data[ROW * COL];
    int top;
} Stack;

void push(Stack *s, Point p) {
    if (s->top >= ROW * COL - 1) {
        printf("Stack Overflow!\n");
        exit(1);
    }
    s->data[++(s->top)] = p;
}

Point pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow!\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isValid(int maze[ROW][COL], int visited[ROW][COL], int x, int y) {
    return (x >= 0 && x < ROW && y >= 0 && y < COL &&
            maze[x][y] == 0 && visited[x][y] == 0);
}

void solveMaze(int maze[ROW][COL], Point start, Point end) {
    Stack stack;
    stack.top = -1;
    int visited[ROW][COL] = {0};

    push(&stack, start);
    visited[start.x][start.y] = 1;

    int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}}; // Up, Down, Left, Right

    while (!isEmpty(&stack)) {
        Point current = pop(&stack);

        printf("Visiting (%d, %d)\n", current.x, current.y);

        if (current.x == end.x && current.y == end.y) {
            printf("Reached destination (%d, %d)\n", end.x, end.y);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dirs[i][0];
            int ny = current.y + dirs[i][1];

            if (isValid(maze, visited, nx, ny)) {
                visited[nx][ny] = 1;
                Point next = {nx, ny};
                push(&stack, next);
            }
        }
    }

    printf("No path found.\n");
}

int main() {
    int maze[ROW][COL] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    Point start = {0, 0};
    Point end = {4, 4};

    solveMaze(maze, start, end);

    return 0;
}
