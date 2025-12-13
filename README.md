

Maze Solver

**Project Goal:** To programmatically create a random, solvable maze and then automatically find the path from the Start point (`S`) to the End point (`E`).

**Course:** CSE115

## Project Core Concepts

This project successfully incorporates all the required C elements:

  * **Variables:** Used for dimensions (`ROWS`, `COLS`), coordinates (`r`, `c`), and counters.
  * **Loops:** Essential for initialization (`initializeMaze`), saving the file (`saveMaze`), and printing the output (`printMaze`).
  * **Arrays:** The entire maze is stored as a global **2D character array** (`maze[ROWS][COLS]`).
  * **Structures:** The `struct Point` is used for cleaner handling of coordinates.
  * **Pointers:** Used heavily in the `shuffle` function to swap array elements efficiently.
  * **File I/O:** The `saveMaze` function **writes** the unique, generated maze to `generated_maze.txt`.

## The Dual Algorithms

The project is executed in two powerful stages, each using a distinct algorithm:

### Stage 1: Maze Generation

We use the **Recursive Backtracker** algorithm to guarantee a perfectly valid maze every time.

1.  **Start:** The grid starts as a solid block of walls (`#`).
2.  **Recursion & Backtracking:** The function `generateMaze` begins at `(1, 1)` and calls itself recursively. It randomly chooses a direction (via the `shuffle` function), moves **two steps**, and "carves" the wall in between, creating a path (`     `).
3.  **Randomness:** Because the directions are shuffled before each move, the resulting maze is unique every time the program runs.

### Stage 2: Maze Solver

We use **Recursive Depth-First Search (DFS)** to find the path from the set Start (`S`) at $(1, 1)$ to the End (`E`) at $(ROWS-2, COLS-2)$.

1.  **Search:** The `solve` function recursively explores one path as deep as possible.
2.  **Path Marking:** Valid cells on the current path are marked with a yellow asterisk (`*`).
3.  **The Key: Backtracking:** If the search hits a dead end, the function returns `false`, and the line `maze[r][c] = ' '` **erases the path marks**. This ensures that only the final, successful route remains marked at the end.

## How to Compile and Run

1.  **Save:** Save the entire source code as `main.c`.
2.  **Compile:** Use a C compiler (like GCC) in your terminal:
    ```bash
    gcc main.c -o maze_solver
    ```
3.  **Run:** Execute the compiled program:
    ```bash
    ./maze_solver
    ```

### Output Files

Upon execution, the program will:

1.  Print the initial random maze.
2.  Print the final solved maze with the path marked in **yellow**.
3.  **Create a file** named `generated_maze.txt` in the same directory, which contains a plain-text version of the unique maze the program just created.

## Visualization

The `printMaze` function uses **ANSI Color Codes** to color-code the output, making it easy to distinguish the wall and path.

  * **White:** Walls (`#`)
  * **Green:** Start (`S`) and End (`E`)
  * **Yellow:** The Solved Path (`*`)
