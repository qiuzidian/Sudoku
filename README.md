# 数独类实现文档

## 介绍

本项目实现了一个简单的数独（Sudoku）类，包含了网格（Grid）和数独（Sudoku）相关的功能。用户可以通过输入字符串来初始化数独，并进行打印、获取行、列、小方块以及候选数的操作。

## C++ 类定义

### Grid 类

- **构造函数**
  - `Grid()`: 默认构造函数，初始化一个 9x9 的网格。
  - `Grid(int boxSize, int gridSize)`: 参数化构造函数，初始化指定大小的网格。
  - `Grid(const Grid& other)`: 复制构造函数。

- **析构函数**
  - `~Grid()`: 释放动态分配的内存。

- **成员函数**
  - `void printGrid()`: 打印当前网格。
  - `int* getRow(int row)`: 获取指定行的值。
  - `int* getColumn(int col)`: 获取指定列的值。
  - `int* getBox(int box)`: 获取指定小方块的值。

### Sudoku 类

- **构造函数**
  - `Sudoku()`: 默认构造函数。
  - `Sudoku(const std::string &inputString)`: 使用输入字符串初始化数独。

- **成员函数**
  - `bool parseSudoku(const std::string &inputString)`: 解析输入字符串，返回是否成功。
  - `bool getInferences(int row, int col, std::vector<int> &candidateList)`: 获取指定位置的候选数。



## Python 类定义

### Grid 类

-   构造函数
    -   `__init__(self, box_size=3, grid_size=9)`: 初始化网格，默认小方块大小为3，网格大小为9。并检测输入的 `box_size` 和 `grid_size` 是否符合关系。
-   成员函数
    -   `print_grid(self)`: 打印当前网格。
    -   `get_row(self, row)`: 获取指定行的值。
    -   `get_column(self, col)`: 获取指定列的值。
    -   `get_box(self, box)`: 获取指定小方块的值。

### Sudoku 类

-   构造函数

    -   `__init__(self, input_string=None)`: 使用输入字符串初始化数独。

-   成员函数

    -   `parse_sudoku(self, input_string)`: 解析输入字符串，返回是否成功。
    -   `get_inferences(self, row, col)`: 获取指定位置的候选数。

    

## 待实现功能

### 1. 填入值功能

-   `fillValue(row, col, value)`: 在指定的行和列填入给定值，更新网格并相应地更新哈希表。需要检查当前状态是否合法。

### 2. 检查数独状态功能

-   `isValid()`: 检查当前数独的状态是否满足数独的规则（即每行、每列和每个小方块内的数字都是唯一的）。

### 3. 求解数独功能

-   `solve()`: 使用递归和回溯算法求解数独，返回一个布尔值，表示是否成功找到解。