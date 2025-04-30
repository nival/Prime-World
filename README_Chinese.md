[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Prime World Trailer](PW_trailer.png)](https://youtu.be/Fkd-zva4npI)
[Prime World](https://wikipedia.org/wiki/Prime_World) 是一款多人在线战斗竞技场（MOBA）游戏，于2014年发布。该游戏由公司 [Nival](http://nival.com/) 基于自研游戏引擎开发，主要使用 C++ 编写。

游戏由两部分组成：城堡部分和战斗部分。玩家扮演领主或女领主的角色。在城堡中，玩家建造建筑、雇佣英雄并为其选择天赋。在战斗部分，玩家操控英雄，并利用天赋与其他玩家进行团队对抗。

2024年，游戏战斗部分的源代码以[特殊许可证](LICENSE.md)形式开源，禁止商业用途，但对游戏社区、学习和科研用途完全开放。
使用前请仔细阅读[许可协议](LICENSE.md)的条款。

## 本仓库内容
- `pw` — 战斗部分的主代码
- `pw_publish` — 已编译含作弊码的战斗客户端及客户端编辑器
- `pw/branches/r1117/Bin/PF_Editor.exe` — 游戏数据编辑器

## 准备工作
需要下载本仓库的数据，并将 `Bin` 文件夹与游戏主数据合并。操作步骤如下：

1. 将 `pw_publish/branch/Client/PvP/Bin` 文件夹复制到 `pw/branches/r1117` 并覆盖已有文件。
2. 用作弊码运行客户端 `pw/branches/r1117/Bin/PW_Game.exe`。
3. 如果一切正常，你会看到加载窗口，但没有画面且为黑屏。
4. 在文件夹 `Profiles -> game.cfg` 中，将 `local_game 0` 改为 `local_game 1`。
5. 再次用作弊码启动客户端。现在你应该可以看到大厅，选择地图、英雄并开始战斗。
6. 游戏中按键盘上的波浪键 (~)，会弹出代码输入控制台。

如遇到错误，请查看 `pw/branches/r1117/Bin/logs` 文件夹下的日志文件。

## 游戏数据
游戏数据可通过编辑器编辑，位于 `pw/branches/r1117/Data`

通过编辑数据，你可以：
1. 更改英雄天赋和技能的描述。
2. 修改英雄的天赋和技能。
3. 更改小兵和防御塔的逻辑。
4. 增加新英雄和技能。
5. 增加新天赋。
6. 修改和添加特效。
7. 修改和添加模型与动画。

修改数据后，无需重新编译客户端。只需点击 `File -> Save`，所有更改会立即在 `PW_Game` 客户端中生效。例如，可以尝试修改某个天赋或英雄技能的描述。

## 游戏数据编辑器
游戏数据编辑器位于 `pw/branches/r1117/Bin/PF_Editor.exe`

首次打开编辑器时需配置 `Data` 路径：
1. `Tools -> File System Configuration`
2. `Add -> WinFileSystem`
3. 设置 Data 文件夹为系统根目录：`pw/branches/r1117/Data`
4. 关闭窗口
5. 在编辑器中：`Views -> Object Browser` 和 `Views -> Properties Editor`。这是数据编辑的两个主面板。

编辑器标签页可拖动与停靠。

## 含作弊码的游戏客户端
在仓库中可找到已编译带作弊码的游戏客户端 `pw_publish/branch/Client/PvP/Bin/PW_Game.exe`

需要确保 `Bin` 文件夹旁有 `Localization`、`Profiles` 和 `Data` 文件夹，因此准备时需移动到 `pw` 目录下。如果修改了代码，需要重新编译客户端。

## 如何启动 PvP
1. 在 `Profiles -> game.cfg` 中将 `local_game 0` 改为 0。
2. 添加 `login_adress <server address>`。
3. 用参数 `-dev_login MyNickname` 启动游戏。

## 如何启动带有机器人的游戏
1. 将 `Profiles -> private.cfg_example` 文件重命名为 `private.cfg`。
2. 用记事本打开该文件。
3. 找到 `AT BEGINNING GAME`。
4. 添加新行：`add_ai bots` —— 为游戏中每个英雄分配一个AI机器人。

## 常见错误排查
1. 将 `Profiles -> private.cfg_example` 文件重命名为 `private.cfg`。
2. 用记事本打开该文件。
3. 找到 `performance section`。
4. 找到行 `setvar gfx_fullscreen = 0` —— 这样游戏会以窗口模式启动，通常更稳定。
5. 你也可以在 `performance section` 中调整其他性能优化设置。

## 致谢
感谢 **Prime World: Nova** 社区为文档与错误修复所作出的贡献。
