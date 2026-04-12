# 使用 C++20 + SFML3.0.2 搭建的 2D STG（弹幕射击游戏） 游戏框架

**这是一个学习项目**

**项目主要用于学习C++和面向对象**

## 简介
一个使用 **C++ 和 SFML** 编写的2D STG游戏框架

**已完成STG游戏基本框架搭建：**

已完成游戏的页面系统。拥有基本的可扩展UI，

已完成基本的STG游戏玩法和系统。

已完成模块化敌人、Boss、阶段创建。

已完成包括通过脚本构建固定流程道中、状态驱动多阶段Boss战和空白阶段的游戏基本流程。

已完成经过优化的碰撞检测


**近期任务：**

1 在现有表达体系下尝试设计多种弹幕，探索封装弹幕设计工具的方向

2 逐步加入更多特效/演出 ，从而推动特效/演出系统的细化和完善


**阶段目标：**

尝试使用此框架设计一个流程、弹幕、演出、特效都较为完善的闭环关卡

......

此外，后续将继续完善和优化页面系统和游戏系统的框架。

后续也将继续优化框架的游戏性能



## 核心架构与主要设计

**游戏初始化与主循环：**

游戏启动->建立游戏application类，包含窗口，同时加载各种资源->窗口存在时，每帧进行：处理输入、更新信息、渲染对象

**页面系统：**

使用State + StateStack

页面堆叠与聚焦采用页面栈，从而保护低级页面和确定优先级

处理输入、更新和渲染由通过页面栈根据优先级依次调用各页面的处理、更新和渲染方法（以下“处理、更新和渲染方法”将简称“方法”）

**创建游戏页面对象**

使用 比对象高一级的Manager + 自下而上的申请方法，对象在需要时向Manager发送申请

方法中涉及创建对象的操作的，向对应的Manager发送申请与配置信息

Factory负责创建对象。由一个配置信息返回一个对象

Manager申请到申请后，将申请交给Factory创建对象，并将返回的对象纳入管理

**游戏页面的对象管理：**

游戏页面中每个最小对象持有自己的方法

所有同类对象由一个对应的Manager统一管理，从而统一调用方法

每帧对所有Manager和独立对象调用方法

**游戏页面中信息的传递：**

同一类型的信息，一起打包为一个struct类型的Package

大部分信息传递通过传递Package实现

**表达游戏流程**

使用多层状态机来表达流程

游戏的每一个阶段是一个状态。每个阶段自己可以再持有多个状态

使用 比状态高一级的PhaseController + 自上而下的检查方法，PhaseController检查状态是否结束 统一管理状态切换

**游戏性能的优化：**

短生命周期、高频创建对象使用对象池

碰撞检测采用“粗判”（距离与碰撞半径判定）+细判（离散帧的连线连续碰撞检测）多级检测方式

算法中只涉及加减乘除以及向量点乘操作

**模块化游戏内对象**

对象本身不持有方法，方法写在Behavior中

对象根据需要绑定对应的Behavior

**脚本设计游戏内容**

各种方法仍需要写在.cpp文件中

脚本中存有对象的基本配置信息，同时包含对象间的上下级关系

在游戏开始时就完成所有对象的递归式创建、绑定上下级



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

使用CMake进行构建和编译：

**务必检查修改CMake中设置的SFML的路径为自己安装的SFML的路径！（第6行）**

**要求CMake ≥ 3.20，支持 C++20 的编译器（MinGW / MSVC），支持SFML 3.0.2**


创建构建目录与生成构建文件
```bash
mkdir build
cd build
cmake ..
```


编译
```bash
cmake --build .
```

main.exe将生成于./main.exe


也可以使用g++手动编译（示例如下）：

**实际请务必根据安装的SFML位置自行指定路径！！！**
**这段g++手动编译命令最后更新于2026.2。项目此后有变动，请自行将所有.cpp文件加入编译命令中**

```bash
g++ src/main.cpp src/application.cpp src/core/state.cpp src/core StateStack.cpp src/core/Clock.cpp \
    src/states/MenuState.cpp src/states/DifficultyState.cpp src/states/ManualState.cpp src/states/GameState.cpp src/states/PauseState.cpp \
    src/manager/EnemyManager.cpp src/manager/BulletManager.cpp src/manager/PhaseController.cpp src/manager/CollisionSystem.cpp \
    src/phases/Phase.cpp src/phases/basicphases/StartPhase.cpp src/phases/basicphases/TimePhase.cpp src/phases/basicphases/EventPhase.cpp src/phases/phases/MidPhase.cpp src/phases/phases/VoidPhase.cpp src/phases/phases/BossPhase.cpp src/phases/phases/SpellPhase.cpp \
    src/bullets/PlayerBullet.cpp src/bullets/LinearBullet.cpp\
    src/ui/Button.cpp src/ui/Page.cpp src/ui/Text.cpp src/ui/Frame.cpp \
    src/entities/Entity.cpp src/entities/Player.cpp src/entities/Enemy.cpp src/entities/Bullet.cpp src/entities/Boss.cpp src/enemies/Enemy1.cpp \
    src/mathematics/mathematics.cpp \
    src/collision/CollisionCheck.cpp \
    -std=c++20 \
    -Iinclude \
    -IC:/msys64/mingw64/include \
    -LC:/msys64/mingw64/lib \
    -lsfml-graphics -lsfml-window -lsfml-system \
    -o main.exe
```

也请务必将.exe文件生成在项目文件夹根目录下（test文件夹下）。

--- 

## 运行方式

编译成功后，运行生成在根目录的可执行文件(可以直接双击main.exe)
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
- Up / Down： 翻页
- X / Esc： 返回上一级菜单

Easy难度
- Up / Down / Left / Right: 自机移动
- LShift: 按下时低速移动并显示判定点
- Z: 射击
- X: 使用bomb

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

│  ├─ behaviors/            # 敌人行为（随机移动、定加速度移动等）

│  ├─ bullets/              # 不同种类子弹（自机狙、直线弹等）

│  ├─ collision/            # 碰撞处理算法

│  ├─ core/                 # 核心系统（游戏循环、状态栈）

│  ├─ entities/             # 游戏实体（玩家、敌人）

│  ├─ manager/              # 游戏页面资源、状态管理，碰撞处理系统

│  ├─ mathematics/          # 数学工具

│  ├─ overlays/             # 演出效果（加载中的帷幕等）

│  ├─ packages/             # 资源包裹（联系上级的资源，用于对象间联系的黄页）

│  ├─ phases/               # 游戏页面状态

│  ├─ states/               # 具体页面（各级菜单）

│  └─ ui/                   # UI

│

├─ src/                     # .cpp源文件

│  ├─ basicstates/

│  ├─ core/

│  ├─ entities/

│  ├─ states/

│  ├─ ui/

│  ├─ ......（与include结构一一对应）/

|    |

│  └─ main.cpp              # 程序入口

│

├─ README.md                # 项目说明文档

└─ main.exe                 # 编译生成的可执行文件

