# SFML 小项目

## 简介
一个使用 **C++ 和 SFML** 编写的简单项目。
目前已完成游戏页面的基本框架，支持多级页面切换。
目前正在编写游戏页面逻辑。
后续将继续完善框架和游戏页面。

项目主要用于学习C++和面向对象。

---

## 开发环境

- 操作系统：Windows 10 / 11
- 编译器：MinGW-w64（支持 C++20）
- IDE：Visual Studio Code
- C++ 标准：C++20

---

## 依赖库

- **SFML 3.0.2**
  - sfml-graphics
  - sfml-window
  - sfml-system

确保安装SFML，并配置好环境变量或在编译时指定include/lib路径。

---

## 编译方式

使用 g++ 手动编译（示例）：

```bash
g++ src/main.cpp src/application.cpp src/core/state.cpp src/core/StateStack.cpp \
    src/states/MenuState.cpp src/states/DifficultyState.cpp src/states/ManualState.cpp src/states/GameState.cpp \
    src/ui/Button.cpp src/ui/Page.cpp src/ui/Text.cpp \
    src/entities/Entity.cpp src/entities/Player.cpp src/entities/Enemy.cpp src/entities/Bullet.cpp \
    -std=c++20 \
    -Iinclude \
    -IC:/msys64/mingw64/include \
    -LC:/msys64/mingw64/lib \
    -lsfml-graphics -lsfml-window -lsfml-system \
    -o main.exe
```

实际请根据安装的SFML位置自行指定路径。

请务必将.exe文件生成在项目文件夹根目录下（test文件夹下）。

--- 

## 运行方式

编译成功后，运行生成在根目录的可执行文件
./main.exe

---

## 操作说明

主菜单
- Up / Down： 选择按钮
- Z： 确定
- X / Esc： 选择Quit

Start页
- Up / Down / Left / Right： 选择按钮
- Z： 确定
- X / Esc： 返回上一级菜单

Manual页
- Left / Right： 翻页
- X / Esc： 返回上一级菜单

Easy难度
- Up / Down / Left / Right: 自机移动
- LShift: 按下时低速移动并显示判定点
- Z: 射击

---

## 项目结构

root/

├─ .vscode/                 # VS Code 配置文件

│  ├─ c_cpp_properties.json # C/C++ IntelliSense 与编译配置

│  └─ tasks.json            # 构建任务（g++ + SFML）

│

├─ assets/                  # 游戏资源

│  ├─ fonts/                # 字体资源

│  └─ textures/             # 贴图 / 图片资源

│

├─ include/                 # 头文件（.h）

│  ├─ basicstates/          # 基础状态类（基类、通用状态）

│  ├─ core/                 # 核心系统（游戏循环、状态栈）

│  ├─ entities/             # 游戏实体（玩家、敌人）

│  ├─ states/               # 具体游戏状态（各级菜单）

│  └─ ui/                   # UI

│

├─ src/                     # .cpp源文件

│  ├─ basicstates/

│  ├─ core/

│  ├─ entities/

│  ├─ states/

│  ├─ ui/

│  └─ main.cpp              # 程序入口

│

├─ README.md                # 项目说明文档

└─ main.exe                 # 编译生成的可执行文件

