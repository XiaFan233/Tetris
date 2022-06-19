# [main](./main.md)

---

## game

### 1. `namespace Shape`

Shape 总共有7种: `I` `Z` `S` `T` `L` `J` `O`

### 2. `namespace Colour`

Colour 总共有7种

### 3. `Tetromino` 可控制的四方块组成的结构

- `pos` 四个方块坐标
- `shape`
- `colour`
- 用 `void initTetromino()` 初始化随机

### 4. `Tetris` 主要游戏框架

- `matrix` 地图颜色矩阵

- `Tetromino`
    - `now` 当前控制
    - `backup` 备份, 当控制违法时候回滚
    - `next` 显示在侧边栏, 当 `now` 销毁时候替代，并随机生成新的

- 纯虚函数 `draw`
纯虚函数在被继承是必须要实现，在这里我用 `TetrominoSprite` 平移显示的方式打印在屏幕上

- `moveX` 方块左右移动
- `moveY` 方块向下移动
- `rotate` 方块旋转, 先获取 `旋转中心` ，在运作用 `旋转矩阵` 逐一旋转`90`
- `checkLines` 逐行检查是否被充满了，如果充满了，删除这一行，并且 `分数++`