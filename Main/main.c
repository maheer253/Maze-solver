#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ROWS 21
#define COLS 21

struct Point
{
    int r, c;
};

char maze[ROWS][COLS];

void initializeMaze()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
            maze[i][j] = '#';
    }
}
void shuffle(int *arr);

void generateMaze(int r, int c)
{
    maze[r][c] = ' ';

    int directions[] = {0, 1, 2, 3};
    shuffle(directions);

    for (int i = 0; i < 4; i++)
    {
        int d = directions[i];
        int nr = r, nc = c;

        if (d == 0) nr -= 2;
        if (d == 1) nr += 2;
        if (d == 2) nc -= 2;
        if (d == 3) nc += 2;

        if (nr > 0 && nr < ROWS - 1 && nc > 0 && nc < COLS - 1 && maze[nr][nc] == '#') {

            maze[(r + nr) / 2][(c + nc) / 2] = ' ';

            generateMaze(nr, nc);
        }
    }
}

void shuffle(int *arr)
{
    for (int i = 0; i < 4; i++)
    {
        int r = rand() % 4;
        int temp = arr[i];
        arr[i] = arr[r];
        arr[r] = temp;
    }
}

void saveMaze(const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("Error opening file to save.\n");
        return;
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fprintf(f, "%c", maze[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

bool solve(int r, int c) {
    if (r < 0 || c < 0 || r >= ROWS || c >= COLS)
        return false;
    if (maze[r][c] == '#' || maze[r][c] == '*')
        return false;
    if (maze[r][c] == 'E')
        return true;

    if (maze[r][c] != 'S') maze[r][c] = '*';

    if (solve(r - 1, c))
        return true;
    if (solve(r + 1, c))
        return true;
    if (solve(r, c - 1))
        return true;
    if (solve(r, c + 1))
        return true;

    if (maze[r][c] != 'S') maze[r][c] = ' ';
    return false;
}

void printMaze() {
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            char ch = maze[i][j];

            if (ch == '#')
                printf("\033[37m%c \033[0m", ch);     // white
            else if (ch == 'S'||ch=='E')
                printf("\033[32m%c \033[0m", ch);     // green
            else if (ch == '*')
                printf("\033[33m%c \033[0m", ch);     // yellow
            else
                printf("%c ", ch);
        }
        printf("\n");
    }
}

int main()
{
    srand(time(0));

    initializeMaze();

    printf("Generating Random Maze\n");
    generateMaze(1, 1);

    maze[1][1] = 'S';
    maze[ROWS - 2][COLS - 2] = 'E';

    saveMaze("generated_maze.txt");
    printf("Maze saved to 'generated_maze.txt'.\n\n");

    printf("The Random Maze\n");
    printMaze();

    printf("\nSolving...\n");
    struct Point start = {1, 1};

    if (solve(start.r, start.c))
    {
        printf("\nSolved!\n");
        printMaze();
    }
    else
        printf("No path found.\n");
    return 0;
}
