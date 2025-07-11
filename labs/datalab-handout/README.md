
> “这文件到底让我干啥？哪些规则？怎么交作业？”

下面我帮你 **总结这份文件的核心内容**，中英文对照，一目了然。

---

# ✅ **CS\:APP Data Lab 总结 (bits.c)**

---

## 📝 文件作用 (What’s this file for?)

这就是你的作业文件，名字叫：

```
bits.c
```

你需要在里面 **写函数实现**。
每道题就是一个函数，要求：

* 用指定的 **位运算** 完成
* 不许用 if、for、while（除浮点题）
* 不许用大的常数，比如 0xffffffff
* 不许调用别的函数
* 不许用数组、结构体、联合体
* 不许写宏
* 不许类型转换（cast）
* 浮点题除外，有些规则放宽

**→ 最终你要交这个文件给老师。**

> This is the file you hand in. You have to implement the functions in it according to strict rules.

---

## ✅ 整数题 (Integer Coding Rules)

你能用的操作：

* **整型常数**：只能用 0\~255 (0xFF)
* **一元运算**：`~`  `!`
* **二元运算**：`&`  `^`  `|`  `+`  `<<`  `>>`

禁止：

* if, while, for, switch
* 函数调用
* 定义宏
* 数组、struct、union
* 逻辑运算符 &&、||、-、三目运算符 ?: 等
* 类型转换

例子：

```c
int pow2plus1(int x) {
    /* Compute 2^x + 1 using shift */
    return (1 << x) + 1;
}
```

---

## ✅ 浮点题 (Floating-Point Coding Rules)

对浮点题，规则宽松一些：

* 可以用 **if / while / for**
* 可以用 unsigned、int
* 可以用所有逻辑、算术运算
* 可以用大常数
* 仍然禁止：

  * 函数调用
  * 数组、struct、union
  * 浮点类型 float / double / long double
  * 浮点常数（比如 1.0f）

浮点数据都以 **unsigned int** 存储。例如：

* `float f` → 存在 `unsigned uf` 里
* 需要手写 bit-level 操作

例如：

```c
unsigned floatScale2(unsigned uf) {
    // 不允许写 float f = ...，都必须用位运算处理
    return ...;
}
```

---

## ✅ 工具 (Tools)

* 用 `dlc` 检查：

  > 检测语法、运算符个数
* 用 `btest` 检查正确性：

  > 跑测试
* 用 `BDD checker` 检查逻辑等价：

  > 严格验证所有输入

---

## ✅ 常见小技巧

比如整数题：

* 取相反数：`~x + 1` → -x
* 用移位算乘除：

  * x << n = x × 2^n
  * x >> n = x ÷ 2^n
* 检测 x 是否为 0：

  ```c
  !x
  ```
* 检测某些 bit 是否全为 1：

  ```c
  (x & MASK) ^ MASK
  ```

浮点题：

* 分离 sign, exponent, fraction
* exponent 全 1 → NaN 或 INF
* exponent 全 0 → Denorm
* 不能用 float 类型
* 合成浮点数：

  ```c
  return sign | (exp << 23) | frac;
  ```

---

## ✅ 文件结构

你的文件大概长这样：

```c
/* 函数头注释 */
int bitXor(int x, int y) {
    return ...;
}
```

比如：

```c
/*
 * bitXor - x^y using only ~ and &
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}
```

---

## ✅ 操作上限

每道题后面写了：

```
Max ops: 14
```

意思：

> 你最多用 14 个运算符 (比如 \~, &, << 等)

`dlc` 会检查这个限制。

---

## ✅ 提交注意

* 千万别加 `#include <stdio.h>`
* 不要定义 main
* 不要写 printf 除了你调试用（也会警告）

---


> 这就是 Data Lab，你要用位运算写出所有题目，不能用 if、循环，也不能用 float 类型，最后交这一个文件。



非常好！下面是你提供这段 Data Lab 文档的翻译与简明总结，附上中英文对照，并适当加入了一些幽默（毕竟做 Data Lab 的时候总需要一些精神支撑 ☕）。

---

## The CS\:APP Data Lab

《CS\:APP 数据实验室》

### Directions to Students

### 给学生的说明

---

### 🎯 Your Goal

> Your goal is to modify your copy of bits.c so that it passes all the tests in btest without violating any of the coding guidelines.

你的目标是修改你的 `bits.c` 文件，使它通过 `btest` 中的所有测试，同时不违反任何编码规范。

（翻译：你得在规定动作里做出花样，不能耍赖\~）

---

## 0. Files 文件清单

* **Makefile**
  用于编译 `btest`、`fshow` 和 `ishow`

* **README**
  本文件（就是你正在读的说明）

* **bits.c**
  需要你修改并提交的核心文件

* **bits.h**
  头文件

* **btest.c**
  `btest` 主程序

* **btest.h, decl.c, tests.c, tests-header.c**
  用于构建 `btest`

* **dlc**
  编码规范检查工具（Data Lab Compiler）

* **driver.pl**
  自动评分脚本，结合 `btest` 和 `dlc` 使用

* **Driverhdrs.pm**
  可选“Beat the Prof”竞赛的头文件

* **fshow\.c**
  用于查看浮点数表示

* **ishow\.c**
  用于查看整数表示

（翻译：要打赢 Data Lab 这场仗，先得搞清家伙事儿都在哪儿放着。）

---

## 1. Modifying bits.c and checking with dlc

## 修改 bits.c 并使用 dlc 检查

> IMPORTANT: Carefully read the instructions in the bits.c file before you start. These give the coding rules that you will need to follow if you want full credit.

⚠️ 重要：在开始之前，请仔细阅读 `bits.c` 文件内的指令。那里面写着你必须遵守的编码规则，否则就别想拿满分。

> Use the dlc compiler (./dlc) to automatically check your version of bits.c for compliance with the coding guidelines:

可以用 `dlc` 工具检查你的代码是否符合编码规范：

```bash
unix> ./dlc bits.c
```

如果没问题，`dlc` 不会输出任何东西；否则，会打印出违规信息。

如果想统计各个函数里用了多少运算符，可以用 `-e` 参数：

```bash
unix> ./dlc -e bits.c
```

（翻译：dlc 就像教练一样，专盯你动作标准不标准，还会数你做了几下。）

> Once you have a legal solution, you can test it for correctness using the ./btest program.

当你的代码通过规范检查，就可以用 `./btest` 测试正确性。

---

## 2. Testing with btest

## 使用 btest 进行测试

> The Makefile in this directory compiles your version of bits.c with additional code to create a program (or test harness) named btest.

Makefile 会把你的 `bits.c` 和其他测试代码编译成一个叫 `btest` 的程序。

编译并运行：

```bash
unix> make btest
unix> ./btest [可选命令行参数]
```

每次修改 `bits.c` 都要重新编译 `btest`。

如果换平台了（比如从 Linux 跳到 macOS），建议先清理再编译：

```bash
unix> make clean
unix> make btest
```

（翻译：别想偷懒，不重新编译的话，就像穿着昨天的袜子上战场。）

---

### btest 测试机制

> Btest tests your code for correctness by running millions of test cases…

`btest` 会用海量测试用例验证你的函数，包括边界值（比如整数题里的 Tmin、0，浮点题里的 0、inf、非规格化数等）。

一旦某个函数出错，它会打印：

* 哪个测试失败
* 错误结果
* 预期结果

然后终止该函数的后续测试。

---

### btest 命令行选项

```bash
unix> ./btest -h
Usage: ./btest [-hg] [-r <n>] [-f <name> [-1|-2|-3 <val>]*] [-T <time limit>]
  -1 <val>  指定第一个参数
  -2 <val>  指定第二个参数
  -3 <val>  指定第三个参数
  -f <name> 只测试指定函数
  -g        精简输出，方便自动评分
  -h        打印帮助
  -r <n>    给所有题目统一权重 n
  -T <lim>  设置超时限制
```

示例：

* 测全部函数并打印错误：

  ```bash
  unix> ./btest
  ```

* 精简输出（无错误提示）：

  ```bash
  unix> ./btest -g
  ```

* 单测函数 foo：

  ```bash
  unix> ./btest -f foo
  ```

* 单测函数 foo，指定参数：

  ```bash
  unix> ./btest -f foo -1 27 -2 0xf
  ```

（翻译：想调试单个函数？btest 帮你点菜，想吃啥测啥。）

---

## 3. Helper Programs

## 辅助程序

提供两个工具，帮你看数的二进制表示：

* **ishow**：查看整数
* **fshow**：查看浮点数

先编译：

```bash
unix> make
```

示例：

```bash
unix> ./ishow 0x27
Hex = 0x00000027,	Signed = 39,	Unsigned = 39

unix> ./ishow 27
Hex = 0x0000001b,	Signed = 27,	Unsigned = 27

unix> ./fshow 0x15213243
Floating point value 3.255334057e-26
Bit Representation 0x15213243, sign = 0, exponent = 0x2a, fraction = 0x213243
Normalized.  +1.2593463659 X 2^(-85)

unix> ./fshow 15213243
Floating point value 2.131829405e-38
Bit Representation 0x00e822bb, sign = 0, exponent = 0x01, fraction = 0x6822bb
Normalized.  +1.8135598898 X 2^(-126)
```

（翻译：不想心算二进制？用 ishow/fshow，人生少掉 90% 的崩溃。）

---

## 简明总结

* **要改哪个文件？** → bits.c
* **怎么查编码规范？** → ./dlc bits.c
* **怎么测对不对？** → ./btest
* **想看二进制？** → ./ishow 或 ./fshow
* **写完就交，别寄希望上帝保佑盲测能过。**