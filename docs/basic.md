# [README](../README.md)
# [game](./game.md)

---

## basic

- `Point` 坐标
- `Randomer` 随机数生成器

---

### Point

`x` , `y` 代表坐标

### Randomer

- 通过 `std::random_device` 生成真随机数 `seed`  
- 用 `std::mt19937` 批量生成基于 `seed` 的随机数 

Q: 为什么不直接使用 `std::random_device` ?  
A: `std::random_device` 有限，速度慢，如果耗尽会可能造成游戏卡死