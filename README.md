# Daedalus

> A MineSweeper Game built with Qt

[中文版](https://github.com/allenx/Daedalus/blob/master/README_zhcn.md)
## Build & Run

- Qt 5.7 or later
- C++ 11
- macOS Sierra (Build Target is currently macOS and if you want to run it on Windows or Linux, just modify the .pro file a little bit)



## About Daedalus

Daedalus is a MineSweeper game. People have been playing MineSweeper for ages. Most people believe that Microsoft created it while actually it dates back to the 1960s. After years of evolution, the MineSweeper in Windows 10 App Store has got a completely new look, however its rules remain the same:

- The game UI has a matrix of cells in it. The cells can be divided into two kinds: **mine** and **not mine**. If a cell is **not a mine**, its displaying content would be the number of its adjacent mines.
- Left click turns a cell over
- Right click flags or questions a cell
- If a **mine-cell** gets turned over, the player loses.
- If the player has turned all the cells that are not mines, the player wins.



## Implementing Daedalus

> Mine Laying, Cell Content Calculating, Turning Over, Recursive Turning Over

Here's how I designed the Game Logic for Daedalus:

- In most implementations of MineSweepers, players will **never** step on a cell on his **first click**. What Microsoft has done to implement this rule is easy. If the player steps on a mine on his first click, just lay the mines again and pretends the player didn't step on it. What I did is, lay mines after the player clicks on a cell so that when the AI tries to lay mines it'll avoid the cell that's been clicked.
- When the players clicks a **blank** cell, which means there's no adjacent mine around it, the cells around the cell get automatically turned over. My solution to it is T**urning Over and Recursive Turning Over**



### Algorithms

#### Storing Cells

> 2-dimensional array? 

So how do I store my cells? I tried to use a 2 dimensional array in C++ as I always did in Swift like: `[[Cells]]`, an array of arrays. Well there's no such syntactic sugar in C++. When I want to write a function that returns a 2-dimensional array, I gotta do like this, a pointer of a pointer:

```c++
//Returns a pointer of a pointer of a pointer :-(
//This is so not elegant. It's vulgar.
Cell *** AI::initCellsFoo(int rowCount, int columnCount) {
    Cell ***cells = new Cell **[rowCount];
    for (int i = 0; i < rowCount; ++i) {
        cells[i] = new Cell *[columnCount];
        for (int j = 0; j < columnCount; ++j) {
            Cell *foo = new Cell(i, j);
            cells[i][j] = foo;
        }
    }
    return cells;
}
```

The not-elegant implementation above brought me, a C++ Newbie, so many problems so I used QList of Qt to construct the 2D array instead:

```c++
#define CellMatrix QList<QList<Cell *> *>
CellMatrix *AI::initCells(int rowCount, int columnCount) {
  CellMatrix *cells = new CellMatrix;
  for (int i=0; i < rowCount+2; ++i) {
    cells->append((new FlatList));
    for (int j=0; j<columnCount+2; ++j) {
      Cell *foo = new Cell(i, j);
      cells->at(i)->append(foo);
    }
  }
  return cells;
}
```

Now it gets better.

#### Representing Relationships among Cells

I tried using only coordinates to reference a `Cell` and its adjacent `Cells` at the beginning. For example, this `Cell` at `(3, 5)` got turned over, and the AI needs to see the status of its adjacent `Cells` because they may need to be recursively turned over. So the AI did some calculations on the coordinates and it now knows where the other `Cells` are at: `(2, 4)`, `(2, 5)`, `(2, 6)`, `(3, 4)`, `(3, 6)`, `(4, 4)`, `(4, 5)`, `(4, 6)`. This is way too complex. I mean, it's just not easy for me to write the code because I get easily messed up with all the `+1`s and `-1`s, let alone if the clicked `Cell` is at places like `(0, 0)`, **BANG**, our AI would want to get a `Cell` at `(-1, -1)` from the `CellMatrix`. That's not good.

So I came up with referencing the adjacent `cells` around a `Cell` using 8 pointers. C++ likes pointers. (I hate it though). When constructing the matrix `AI::sharedInstance().cells`, I assign the pointers to the cells for good, by calculating the coordinates, which is inevitable. But I still got the problem when it comes to the cells that are at the edges — they still don't have 8 adjacent cells after all. My first thought is that, just assign the pointers. Like if I do like this: `cell->North = cells->at(-1)->at(-1)`, I won't have any problem at all because it'll just assign `NULL` to `cell->North`. But when I tested it, it's not Okay. Because `cells->at(-1)->at(-1)` won't return `NULL` at all. It crashes.

So we're done with `NULL`. I came up with another idea that is, to add an extra layer of cells outside the player's defined m * n matrix, like building fences around the 4 edges. Then when we are assigning pointers, we are not gonna encounter the problems above, because now every `Cell` we need to take care of has 8 adjacent cells.

![](http://ogbzxx07e.bkt.clouddn.com/UselessCells.png)

(These green cells are the fences, the "useless" cells which I added to solve the problem. We can see that now every "usesful" `Cell` now has 8 adjacent cells.)

So this means `AI:sharedInstance().cells` now has a layer of "useless" cells that the UI should be displaying. In other words, when displaying the `CellMatrix` we need to iterate the 2D array without iterating the "useless" cells.

When we didn't have the "useless" cells it's easy. For a matrix of m * n, the iterating is like this in a `for-loop`:

```c++
for (int i=0; i<m; ++i) {
  for (int j=0; j<n; ++j) {
    //cells.at(i).at(j) is the cell at (i, j)
  }
}
```

Clearly after adding those "useless" cells, we won't be able to do like that. When the player defined a matrix of m * n, we'll actually return a matrix of (m+2) * (n+2). In order to ignore those "useless" cells, we do iterating like this;

```c++
for (int i=1; i<m+1; ++i) {
  for (int j=1; j<n+1; ++j) {
    //cells.at(i).at(j) is the cell at (i, j)
  }
}
```

#### Turning Over and Recursive Turning Over

![](http://ogbzxx07e.bkt.clouddn.com/revealCellDiagram.png)

Below is my **Recursive Turning Over** pseudo code:

```c++
//Rough Pseudo Code
void revealACell(Cell *cell) {
  if cell is not initialized (cell->content == -2)
    layMines()
  if cell is already revealed and its content != 0
    if the number of flagged cells = cell->content
      for cell in cell->cellsAround() {
        revealACell(cell)
      }
}
```

You can see it above that when a `cell` gets revealed, we calculate the number of flagged cells around it. If the number is equal to the `cell`'s content, do recursive turning over on the adjacent cells.

I have a method called `FlatList *cellsAround()`. This method returns a list of a cell's adjacent cells. Why would I do so? Didn't the cell have 8 pointers pointed to the adjacent cells already? Yea it does. But some of the cells have "useless" cells as their adjacent cells. So I have this method to filter those "useless" cells.

```c++
//Iterate Pointers Around a Cell and save'em into a list
FlatList *Cell::cellsAround() {
  FlatList *foo = new FlatList;
  if (-2 == content) {
    return NULL;
  }
  
  //If a cell's content is -2, which means it's not initialized even after initialization, then this cell is useless and cannot be added to the list
  if (North->content != -2) foo->append(North);
  if (NorthWest->content != -2) foo->append(NorthWest);
  if (NorthEast->content != -2) foo->append(NorthEast);
  if (South->content != -2) foo->append(South);
  if (SouthWest->content != -2) foo->append(SouthWest);
  if (SouthEast->content != -2) foo->append(SouthEast);
  if (West->content != -2) foo->append(West);
  if (East->content != -2) foo->append(East);
  return foo;
}
```

#### Laying Mines

**Random**. That's the essence of it.



### User Interaction Handling

![](http://ogbzxx07e.bkt.clouddn.com/Interactions.png)







### References

**Pure Header** Files:

| HEADERS           | DESCRIPTION                              |
| :---------------- | :--------------------------------------- |
| `HeaderWrapper.h` | include header files to make including in other files simpler |
| `resourses.h`     | macro defines of file paths of game resourses like sounds and pics |

**Model** Classes:

| CLASS         | DESCRIPTION                              |
| ------------- | ---------------------------------------- |
| `AI`          | AI controls the logic of the game        |
| `Cell`        | Cell is the model of the cells in the game |
| `Preferences` | Preferences is the user's preferences    |

**Controller** Classes:

| CLASS                    | DESCRIPTION                              |
| ------------------------ | ---------------------------------------- |
| `UserInteractionHandler` | Handles and filters users' interactons with the interface and send them to the model AI. |
| `SoundHandler`           | Plays sound                              |

**View** Classes:

| CLASS            | DESCRIPTION                              |
| ---------------- | ---------------------------------------- |
| `Cell`           | Displays the UI of each cell in the game according to their content |
| `GameField`      | Displays a Grid of cells that allows users to interact with |
| `AboutPage`      | Displays the About Page. A simple one.   |
| `ADOBEOCRLabel`  | Custom Label Class with special font of Adobe OCR A STD |
| `DefeatedDialog` | Displays the Defeated Page               |
| `WinningDialog`  | Displays the Winning Page                |
| `Preferences`    | Displays the Settings page               |
| `StopWatch`      | A stopwatch                              |
| `MainWindow`     | The whole window of the game             |



For the `Cell` Class

| PROPERTIES                               | DESCRIPTION                              |
| ---------------------------------------- | ---------------------------------------- |
| `Coordinate coordinate`                  | A cell's coordinate in the grid          |
| `int content`                            | 0 - 8 means the numbers of mines around the cell. -1 means it's a mine itself and -2 means it hasn't been initialized by the AI yet. |
| `bool isMine`                            | Indicates if the cell is a mine          |
| `Status status`                          | Status is an enum type which has `virgin`, `flagged`, `questioned`, `revealed` |
| `Cell *North, *NorthWest, *NorthEast, *East, *SouthEast, *South, *SouthWest, *West` | Pointers pointed to the 8 cells around a cell |

| INSTANCE METHODS         | DESCRIPTION     |
| ------------------------ | --------------- |
| `void setStatus(Status)` | sets its status |

| CLASS METHODS                | DESCRIPTION     |
| ---------------------------- | --------------- |
| `Cell(int atRow, int atCol)` | The Constructor |

| SIGNALS                                  | DESCRIPTION                              |
| ---------------------------------------- | ---------------------------------------- |
| `void clicked(Cell *, QMouseEvent *)`    | Emitted when the user left_clicks a cell |
| `void clicked_double(Cell *, QMouseEvent *)` | Emitted when the user double_clicks a cell |
| `void statusChanged()`                   | Emitted when a cell's status has chan    |

| SLOTS              | DESCRIPTION                              |
| ------------------ | ---------------------------------------- |
| `void refreshUI()` | Refreshes the cell's UI on receiving the statusChanged() |



For the AI Class:

| PROPERTIES                               | DESCRIPTION                              |
| ---------------------------------------- | ---------------------------------------- |
| `CellMatrix *cells`                      | The 2-D matrix of cells in the game      |
| `FlatList *mines`                        | The 1-D Array of mines in the game       |
| `QString time`                           | The time the user has spent on a game    |
| `Board board`                            | The game board indicating rowCount and colCount of the matrix of cells in the game |
| `UserInteractionHandler *_interactionHandler` | The User Interaction Handler             |
| `SoundHandler *_soundHandler`            | The Sound Handler                        |

| INSTANCE METHODS                         | DESCRIPTION                              |
| ---------------------------------------- | ---------------------------------------- |
| `CellMatrix *initCells(int rowCount=12, int colCount=12)` | Generates a matrix of cells, rowCount and colCount being 12 by default |
| `void layMines(Cell *clickedCell)`       | Lay mines on cells except for the cell that the user clicked for the first time |
| `void countNeighbourMines(CellMatrix *cells)` | Counts neighboring mines and set the cells' content |
| `void revealCell(Cell *clickedCell)`     | Recursively reveals the clickedCell      |
| `void judge()`                           | Judges if the user has won the game      |
| `void bindCellsToInteractionHandler(Cell *, UserInteractionHandler *)` | Binding signals and slots                |
| `void bindInteractionHandlerToAI(UserInteractionHandler *, AI *)` | Binding signals and slots                |
| `void bindInteractionhandlerToSoundHandler(UserInteractionHandler *, SoundHandler *)` | Binding signals and slots                |
| `void bindAIToSoundHandler(AI *, SoundHandler *)` | Binding signals and slots                |

| CLASS METHODS                 | DESCRIPTION                              |
| ----------------------------- | ---------------------------------------- |
| `AI()`                        | The Constructor                          |
| `static AI &sharedInstance()` | Returns the reference of the AI Singleton |

| SIGNALS                       | DESCRIPTION                              |
| ----------------------------- | ---------------------------------------- |
| `void steppedOnAMine(Cell *)` | Emitted when the user has stepped on a mine |
| `void gameInitialized()`      | Emitted when the game has been initialized |
| `void waitingForTheTime()`    | Emitted when the AI needs the stop watch to tell it the time |
| `void succeeded()`            | Emitted when user has won t              |
| `void reloadGame()`           | Emitted when the user has changed the preferences or clicked restart / new game |
| `void newWindowPopped()`      | Emitted when a new Window pops up above the main window |
| `void topViewDismissed()`     | Emitted when the main windows became the top window in the view hierachy |

| SLOTS                                    | DESCRIPTION                              |
| ---------------------------------------- | ---------------------------------------- |
| `void leftClickACell(Cell *)`            | Left clicks a cell on receiving left click interaction from the `_userInteractionHandler` |
| `void rightClickACell(Cell *)`           | Right clicks a cell on receiving right click interaction from the `_userInteractionHandler` |
| `void pause()`                           | Pauses the game (the stopwatch) on receiving the SIGNAL `newWindowPopped` |
| `void resume()`                          | Resumes the game (the stopwatch) on receiving the SIGNAL `topViewDismissed` |
| `void receivedNewPreferences(Preferences *)` | Changes the preferences on receiving a Preference_Changed signal |
| `void userClickedRestart()`              | Restarts the game when the user clicks restart |
| `void receivedTime(QString)`             | Sets the time when received time from the stopwatch |




