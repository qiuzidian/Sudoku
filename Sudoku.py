class Grid:
    def __init__(self, box_size=3, grid_size=9):
        """初始化网格，默认小方块大小为3，网格大小为9"""
        if box_size * box_size != grid_size:
            raise ValueError("Invalid box size.")
        self.box_size = box_size
        self.grid_size = grid_size
        self.grid = [[0] * grid_size for _ in range(grid_size)]

    def print_grid(self):
        """打印网格"""
        for row in self.grid:
            print(" ".join(map(str, row)))

    def get_row(self, row):
        """获取指定行"""
        if row < 0 or row >= self.grid_size:
            raise IndexError("行索引超出范围")
        return self.grid[row]

    def get_column(self, col):
        """获取指定列"""
        if col < 0 or col >= self.grid_size:
            raise IndexError("列索引超出范围")
        return [self.grid[i][col] for i in range(self.grid_size)]

    def get_box(self, box):
        """获取指定小方块"""
        if box < 0 or box >= (self.box_size * self.box_size):
            raise IndexError("小方块索引超出范围")
        box_values = []
        for i in range(self.box_size):
            for j in range(self.box_size):
                box_values.append(self.grid[i + (box // self.box_size) * self.box_size][
                    j + (box % self.box_size) * self.box_size])
        return box_values


class Sudoku(Grid):
    def __init__(self, input_string=None):
        """初始化数独类"""
        super().__init__()

        self.hash_rows = [[0] * 9 for _ in range(9)]
        self.hash_cols = [[0] * 9 for _ in range(9)]
        self.hash_boxes = [[[0] * 9 for _ in range(3)] for _ in range(3)]

        if input_string is not None:
            if not self.parse_sudoku(input_string):
                raise ValueError("Invalid Sudoku input string.")

    def parse_sudoku(self, input_string):
        """解析数独字符串"""
        if len(input_string) != 81:
            return False

        i, j = 0, 0
        for c in input_string:
            if c < '0' or c > '9':
                return False
            if c != '0':
                index = int(c) - 1
                self.hash_rows[i][index] += 1
                self.hash_cols[j][index] += 1
                self.hash_boxes[i // 3][j // 3][index] += 1
                if (self.hash_rows[i][index] > 1 or 
                    self.hash_cols[j][index] > 1 or 
                    self.hash_boxes[i // 3][j // 3][index] > 1):
                    return False

            self.grid[i][j] = int(c)
            j += 1
            if j == 9:
                j = 0
                i += 1

        return True

    def get_inferences(self, row, col):
        """获取候选数"""
        if row < 0 or row >= self.grid_size or col < 0 or col >= self.grid_size:
            raise IndexError("行或列索引超出范围")
        if self.grid[row][col] != 0:
            return []

        candidate_list = []
        for i in range(self.grid_size):
            if (self.hash_rows[row][i] == 0 and
                    self.hash_cols[col][i] == 0 and
                    self.hash_boxes[row // 3][col // 3][i] == 0):
                candidate_list.append(i + 1)
        return candidate_list


if __name__ == "__main__":
    # 示例数独谜题
    sudoku = Sudoku("017903600000080000900000507072010430000402070064370250701000065000030000005601720")
    sudoku.print_grid()

    # 测试解析
    for i in range(9):
        for j in range(9):
            candidates = sudoku.get_inferences(i, j)
            print(f"Candidate number ({i}, {j}) of:", candidates)
