#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class Grid {
public:
    int** grid;
    int boxSize;
    int gridSize;

    // 默认构造函数
    Grid() : boxSize(3), gridSize(9) {
        initializeGrid();
    }

    // 参数化构造函数
    Grid(int boxSize, int gridSize) : boxSize(boxSize), gridSize(gridSize) {
        if (gridSize % boxSize != 0) {
            throw std::invalid_argument("Grid size must be a multiple of box size");
        }
        initializeGrid();
    }

    // 复制构造函数
    Grid(const Grid& other) {
        boxSize = other.boxSize;
        gridSize = other.gridSize;
        initializeGrid();
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                grid[i][j] = other.grid[i][j];
            }
        }
    }

    // 析构函数
    ~Grid() {
        for (int i = 0; i < gridSize; ++i) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    // 打印网格
    void printGrid() const {
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // 获取指定行
    int* getRow(int row) const {
        if (row < 0 || row >= gridSize) {
            throw std::out_of_range("Row index out of range");
        }
        return grid[row];
    }

    // 获取指定列
    int* getColumn(int col) const {
        if (col < 0 || col >= gridSize) {
            throw std::out_of_range("Column index out of range");
        }
        int* column = new int[gridSize];
        for (int i = 0; i < gridSize; i++) {
            column[i] = grid[i][col];
        }
        return column;
    }

    // 获取指定小方块
    int* getBox(int box) const {
        if (box < 0 || box >= (boxSize * boxSize)) {
            throw std::out_of_range("Box index out of range");
        }
        int* boxValues = new int[gridSize];
        for (int i = 0; i < boxSize; i++) {
            for (int j = 0; j < boxSize; j++) {
                boxValues[i * boxSize + j] = grid[i + (box / boxSize) * boxSize][j + (box % boxSize) * boxSize];
            }
        }
        return boxValues;
    }

private:
    void initializeGrid() {
        grid = new int*[gridSize];
        for (int i = 0; i < gridSize; ++i) {
            grid[i] = new int[gridSize]();
        }
    }
};

class Sudoku : public Grid {
public:
    // 定义哈希表用于更方便地获得候选值
    int hashRows[9][9] = {};
    int hashCols[9][9] = {};
    int hashBoxes[3][3][9] = {};

    // 默认构造函数
    Sudoku() : Grid() {}

    // 解析构造函数
    Sudoku(const std::string &inputString) : Grid() {
        parseSudoku(inputString);
    }

    // 解析数独字符串
    bool parseSudoku(const std::string &inputString) {
        if (inputString.size() != 81)
            return false;

        int i = 0, j = 0;
        for (char c : inputString) {
            if (c != '0') {
                int index = c - '0' - 1;
                hashRows[i][index]++;
                hashCols[j][index]++;
                hashBoxes[i / 3][j / 3][index]++;
                if (hashRows[i][index] > 1 || hashCols[j][index] > 1 || hashBoxes[i / 3][j / 3][index] > 1) {
                    return false;
                }
            }
            grid[i][j] = c - '0';
            if (++j == 9) {
                j = 0; i++;
            }
        }
        return true;
    }

    // 获取候选提示
    bool getInferences(int row, int col, std::vector<int> &candidateList) {
        if (row < 0 || row >= gridSize || col < 0 || col >= gridSize) {
            throw std::out_of_range("Row or column index out of range");
        }
        if (grid[row][col] != 0) {
            return false;
        }
        for (int i = 0; i < gridSize; i++) {
            if (hashRows[row][i] == 0 && hashCols[col][i] == 0 && hashBoxes[row / 3][col / 3][i] == 0) {
                candidateList.push_back(i + 1);
            }
        }
        return true;
    }

};

int main() {
    // 示例数独谜题
    Sudoku sudoku("017903600000080000900000507072010430000402070064370250701000065000030000005601720");
    sudoku.printGrid();

    // 测试解析
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::vector<int> candidates;
            if (sudoku.getInferences(i, j, candidates)) {
                std::cout << "Candidate number of " << "(" << i << ", " << j << "): ";
                for (int num : candidates) {
                    std::cout << num << " ";
                }
                std::cout << std::endl;
            } else {
                std::cout << "(" << i << ", " << j << ") has been filled." << std::endl;
            }
        }
    }

    return 0;
}
