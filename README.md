## C++ 软件实践——扫雷

鲍一心 3014216002 计算机科学与技术 2014 级 1 班



### 问题描述：

​	实现扫雷游戏，要求界面上的格子数从 20x20 到 50x50 可选。

### 问题分析：

##### 对问题的理解：

​	在很多人眼里，扫雷「MineSweeper」是 Microsoft 为 Windows 写作的一个经典小游戏。其实扫雷的历史远比这个悠久，它始于 1960 年代，经过多年的演变，如今的 Windows 10 App Store 里面的 MineSweeper 已经进化到一个全新的形态。不过究其根源，MineSweeper 的规则永远如下：

- 游戏界面由一系列排列号的方块组成，方块分为两种：地雷与不是地雷。不是地雷的方块的显示内容为其四面八方紧邻的方块中地雷的个数

- 用户左键点击砖块，方块被翻面显示其内容

- 用户右键点击砖块，方块被旗帜标记或者被问号标记

- 如果内容是地雷的砖块被显示，则游戏失败

- 如果用户在不踩到地雷的情况下将所有安全的砖块翻面，则用户胜利

  那么创作这个游戏的过程就可以分为 `GUI 绘制`，`逻辑实现` 两部分。`GUI 绘制` 有很多方案，不一一赘述。逻辑实现上，就要考虑到**埋雷**、计算每个砖块的**显示内容**、给砖块**翻面**与**递归翻面**等。

##### 解决问题的方案：

​	对于 `GUI 绘制`，虽然个人偏爱 Apple 的 Cocoa 与 Cocoa Touch，但考虑到跨平台问题，我选择了在跨平台 C++ GUI 领域中较为优秀和广为人知的 Qt。

​	对于 `逻辑实现`，我有以下几点：

- 程序由 C++11 实现。


- 在大多数的 MineSweeper 实现里，用户第一次点击是绝不会点击到地雷的。Microsoft 对这条规则的解决方案是：如果用户第一次点击到了地雷，则将地雷的位置移动，相当于简化的`二次埋雷`。而我的处理方案是，用户点击第一次以后再进行埋雷，此时程序的 AI 进行埋雷时会故意避开用户第一次点击的这块砖块。
- 在大多数的 MineSweeper 实现里，当用户点击到一个空白的砖块（周围没有地雷）时，其周围的砖块也会自动地被翻面。我将我的解决方案成为**展开与递归展开**。C++ 的指针类型对我的实现有很大帮助。具体实现方法请看后面的算法描述。
- 判断游戏失败或者成功。我的解决方案是：成功就是用户将所有不是地雷的砖块都翻面。失败就是用户踩到了地雷。

### 数据模型

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



### 算法描述

##### 设计思路：

如何存取我当前游戏局面里的所有 `cells` 呢？我试图构建一个 C++ 的二维数组，像 Swift 这样的语言里面二维数组直接这样写：`[[Cell]]`，数组的数组。C++ 没有这样的语法，我写了一个这样的指针的指针：

```c++
//返回一个指针的指针的指针 :-(
//很明显这样的存储非常的难看，非常的粗鲁，非常的不优雅
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

以上不优雅的实现不仅很难看，还存在很多问题。于是我使用了 Qt 自带类型 QList 来构建二维数组（矩阵）

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

好了这下优雅多了。

接下来，表示砖块与砖块之间的联系是至关重要的一步，这涉及到**递归展开**的实现方法。最开始我想到单纯通过坐标来检索 `Cell` 以及其周围的 `Cells`，比如这个被展开的 `Cell` 的坐标为 `(3, 5)`，那么我们就要同时考察它周围的八个 `Cells` 的状态。通过坐标计算的话，可以得出周围八个 `Cells` 的坐标分别是：`(2, 4)`，`(2, 5)`，`(2, 6)`，`(3, 4)`，`(3, 6)`，`(4, 4)`，`(4, 5)`，`(4, 6)`。我们可以看到这样的计算是非常的复杂的（容易弄错）。更别提比如左上角的 `Cell` 坐标为 (0, 0)，那么它的周围并没有八个 `Cells`，而程序会试图访问 `(-1, -1)` 这种坐标上的 `Cell`，很明显 `(-1, -1)` 上并没有 `Cell`。

于是我想到了用指针来存取一个 `Cell` 周围的八个 `Cells`。在生成 `AI::sharedInstance().cells` 这个矩阵时，我通过计算坐标一次性地将指针附上。当然仍然会遇到处在边角上的 `Cell` 该如何赋指针——毕竟它们的周围并没有八个 `Cells`。最初的做法是，无论如何直接把当前坐标的值赋给那个指针，如`cell->North = cells.at(-1).at(-1)`，因为我想到的是，如果这个值不存在，那么程序应该会直接给我返回 `NULL`，如果是 `NULL` 的话就非常好处理。结果这样做了之后发现程序并不能正确地返回 `NULL`，而是会直接崩溃。

那么给不存在的地方的指针赋上 `NULL` 行不通之后，我想到了另一个方法，在生成矩阵的时候，在用户自定义大小矩阵外面多加一圈。在赋指针的时候，只考虑圈内的这些 `Cells`，这样就可以无忧无虑地赋指针了，因为每个 `Cell` 的周围都有八个 `Cells` 了。如图：

![](http://ogbzxx07e.bkt.clouddn.com/UselessCells.png)

（其中青色的方块即为了解决问题加入的「无用」砖块，可以看到这时就不用担心有些 `Cells` 周围没有八个 `Cells` 了。)

就是说 `AI::sharedInstance().cells` 中有了一圈「无用」的不能被显示出来的 `Cells`，那么我就遇到下一个问题：该如何遍历这个矩阵呢？

本来的做法是，面对一个 m * n 的矩阵，我们的遍历做法应该是一个如下的嵌套 `for-loop`：

```c++
for (int i=0; i<m; ++i) {
  for (int j=0; j<n; ++j) {
    //cells.at(i).at(j) 就是位于 (i, j) 上的一个 cell
  }
}
```

可是显然加入了外面一圈「无用」的`Cells` 之后，我们不能这样做了，此时用户本来想生成一个 m * n 的矩阵，而我们实则生成了 (m+2) * (n+2) 的矩阵。为了在遍历时步遍历外面一圈的「无用」`Cells`，我的做法是这样的：

```c++
for (int i=1; i<m+1; ++i) {
  for (int j=1; j<n+1; ++j) {
    //cells.at(i).at(j) 就是位于 (i, j) 上的一个 cell
  }
}
```

这样的遍历就能保证我们访问到的是「有用」的 `cell`。

这个问题处理完之后，那么就面临**递归展开**的问题了。我的递归展开算法如下：

```c++
//大致的伪代码
void revealACell(Cell *cell) {
  if cell is not initialized
    layMines
  if cell is already revealed and its content != 0
    if the number of flagged cells = cell.content
      for cell in cell.cellsAround() {
        revealACell(cell)
      }
}
```

可以看到，如果一个 `cell` 已经被展开，此时计算它周围被 flag 的个数，如果这个个数等于该 `cell` 的 content，则将其周围所有没被标记的 `cell` 自动展开（因为用户自认为把这个 `cell` 周围的地雷都标记完了，可以自动展开其它）。那么此时还是会遇到边角上的 `cell` 周围会遇到之前所生成的「无用」`cell`，我们很显然无法对这种「无用」`cell` 进行展开，这时候怎么做呢？

在上面的伪代码里面可以看见对于 `Cell` 类我有一个实例方法叫做 `FlatList *cellsAround()`，这个方法返回了一个 `cell` 周围的 `cells` 的一维数组。在这个方法里面我对「无用」`cell` 进行了过滤。如下：

```c++
//Iterate Pointers Around a Cell and save'em into a list
FlatList *Cell::cellsAround() {
  FlatList *foo = new FlatList;
  if (-2 == content) {
    return NULL;
  }
  
  //如果它的周围有没有被初始化即 content 仍然等于 -2 的 cell，那么这样的 cell 是无用的，不能加入 list
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

至于**埋雷**的算法就不用赘述了，随机数解决。

##### 主要程序代码：

```c++
//cells 矩阵的生成算法
CellMatrix *AI::initCells(int rowCount, int columnCount) {
    CellMatrix *cells = new CellMatrix;
    for (int i=0; i < rowCount+2; ++i) {
        cells->append((new FlatList));
        for (int j=0; j<columnCount+2; ++j) {
            Cell *foo = new Cell(i, j);
            cells->at(i)->append(foo);
        }
    }

    for(int k = 1; k < rowCount + 1; ++k) {
        for (int l = 1; l < columnCount + 1; ++l) {
            auto foo = cells->at(k)->at(l);

            //Binds Signals and Slots
            bindCellsToInteractionHandler(foo, _interactionHandler);
            foo->NorthWest = cells->at(k-1)->at(l-1);
            foo->North = cells->at(k-1)->at(l);
            foo->NorthEast = cells->at(k-1)->at(l+1);
            foo->East = cells->at(k)->at(l+1);
            foo->SouthEast = cells->at(k+1)->at(l+1);
            foo->South = cells->at(k+1)->at(l);
            foo->SouthWest = cells->at(k+1)->at(l-1);
            foo->West = cells->at(k)->at(l-1);
        }
    }

    return cells;
}

//给 cells 矩阵埋雷的算法
void AI::layMines(Cell *cell) {
    int maxRow = cells->count() - 2;
    int maxCol = cells->at(0)->count() - 2;
    int foo = board.mineCount;
    while (foo != 0) {
        int randomRow = (qrand() % maxRow) + 1;
        int randomCol = (qrand() % maxCol) + 1;
        if ((randomRow != cell->coordinate.atRow) && (randomCol != cell->coordinate.atCol) && (cells->at(randomRow)->at(randomCol)->isMine != true)) {
            cells->at(randomRow)->at(randomCol)->isMine = true;
            mines->append(cells->at(randomRow)->at(randomCol));
            foo -= 1;
        }
    }
    countNeighbourMines(cells);
}

//给每个 cell 计算其 content 的算法
void AI::countNeighbourMines(CellMatrix *cells) {

    for (int i = 1; i < cells->count()-1; ++i) {
        for (int j = 1; j < cells->at(i)->count()-1; ++j) {
            auto foo = cells->at(i)->at(j);
            if (foo->isMine) {
                foo->content = -1;
                continue;
            }
            foo->content = 0;
            if (foo->cellsAround() != NULL) {
            	FlatList *fooList = foo->cellsAround();
                for (int i=0; i<fooList->count(); ++i) {
                	if (fooList->at(i)->isMine) {
                    	foo->content += 1;
            		}
            	}
            }
        }
    }
}

//revealCell 算法
void AI::revealCell(Cell *cell) {
    //foo here represents the number of flagged cells around the clicked cell
    int foo = 0;

    if (-2 == cell->content) {
        layMines(cell);
    }

    if (cell->status == revealed && cell->content != 0) {
        FlatList *fooListToReveal = new FlatList;
        if (cell->cellsAround() != NULL) {
            FlatList *fooList = cell->cellsAround();
            for (int i=0; i<fooList->count(); ++i) {
                if (fooList->at(i)->status == flagged) {
                    foo += 1;
                } else {
                    fooListToReveal->append(fooList->at(i));
                }
            }
        }

        if (foo == cell->content) {
            for (int i=0; i<fooListToReveal->count(); ++i) {
                if (fooListToReveal->at(i)->status != revealed && fooListToReveal->at(i)->content != -2) {
                    revealCell(fooListToReveal->at(i));
                }
            }
        }

        //judge the game to see if the user has won
        this->judge();

    } else {
        cell->setStatus(revealed);
        board.numberOfCellsRevealed += 1;
        switch (cell->content) {
        case -1: {
            for (int i=0; i<mines->count(); ++i) {
                if (cell != mines->at(i)) {
                    revealCell(mines->at(i));
                }
            }
            emit steppedOnAMine(cell);
            break;
        }

        default: {
            FlatList *fooListToReveal = new FlatList;
            if (cell->cellsAround() != NULL) {
                FlatList *fooList = cell->cellsAround();
                for (int i=0; i<fooList->count(); ++i) {
                    if (fooList->at(i)->status == flagged) {
                        foo += 1;
                    } else {
                        fooListToReveal->append(fooList->at(i));
                    }
                }
            }

            if (foo == cell->content) {
                for (int i=0; i<fooListToReveal->count(); ++i) {
                    if (fooListToReveal->at(i)->status != revealed && fooListToReveal->at(i)->content != -2) {
                        revealCell(fooListToReveal->at(i));
                    }
                }
            }
            break;
        }
        }

        this->judge();
    }
}

//judge 算法
void AI::judge() {
    if (board.numberOfCellsRevealed == board.normalCellCount) {
      	//ready to receive the time from the stopwatch to show results
        emit waitingForTheTime();
    }
}
```



##### 程序流程图：

用户交互处理：

![](http://ogbzxx07e.bkt.clouddn.com/Interactions.png)

AI 递归展开的逻辑：

![](http://ogbzxx07e.bkt.clouddn.com/revealCellDiagram.png)



### 实习心得

这是我第一次使用 C++ 来写 GUI 程序。已有的经验是 Swift 和 Objective-C 这样的拥有十分优雅的 GUI 库的语言。C++ 因为相对底层，让我在书写过程中感到一些原始野蛮的感觉。

当然 C++ 是非常棒的语言，能实现各种各样的编程范式，在写这个扫雷的时候，我非常想念 Swift 和 Haskell 里面的函数式编程特性，于是我尝试实现了 C++ 里面的 Lambda。虽然没有实际地去用（因为实在没时间去调……）。

这一次的写作过程，我写到一半意识到自己事先构思的 M-V-C 结构我没有完全实现，图一时简单将一些东西混在了一起，比如 Cell 这个类是 Model 和 View 的混合。但是后来想一想，其实这种游戏类别的程序并不一定要遵循这样的结构。

写每个类的时候，都要考虑到日后的可扩展性。各个模块之间的耦合度都应极力讲到最低甚至完全解耦，方便模块的热拔插。