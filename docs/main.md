# [README](../README.md)
## main
- [basic](./basic.md)
- [game](./game.md)

### 1. 预处理
#### 1.1 读入文件，创建基本`sf::Drawable`的class
- `sf::Texture`是图像class
- `sf::Font`是字体class
- `sf::Sprite`是`sf::Drawable`的图像class
- `sf::Text`是`sf::Drawable`的文字class
#### 1.2 创建主要游戏对象`Game::Tetris`

### 2. 主循环
#### 2.1 接收键盘输入和其他消息
```C++
while (window.pollEvent(e)) {
    // ...
}
```
- `timer`计时器
- `rotate`是否旋转
- `dx`是否左右移动
- `score`分数
#### 2.2 清空`window`,画上所有class