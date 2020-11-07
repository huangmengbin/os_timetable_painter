### 如何运行

- 可以用vs创建一个空项目，把.h复制到头文件里面去，把.cpp复制到源文件，然后就能编译运行了。从现有代码创建项目好像要调一些配置什么的，太麻烦了。
- 打开vscode，可以使用markdown preview enhanced插件。把控制台里面的东西复制过去预览就行了。不建议用Typora。实在没有的话，粘贴到xxx.html里面让浏览器解析也是可以的。
- 然后截图，复制到word，完成。也可以页面的文本复制到word里面，但调整行距有点麻烦。
- 具体的内容在main里面硬编码完成。这个程序只能画图，不进行调度算法的计算，还是要手算的，毕竟考试也是手算...

### 结构说明

#### Base

  - 一个基类.顾名思义,它的作用比较鸡肋. Equipment(设备)和Task(任务)都是它的子类

#### Equipment和Task

  - 以Equipment类为例，它有一个成员变量：```vector<Triplet(Task*, int, int)> taskInfos```，里面装了很多很多个三元组。每个三元组记录着任务信息，代表这台设备分别在那些时间段被那个任务所占用。
  - taskInfos可以通过 ```usedByTask(Task*, int startTime, int endTime)``` 来添加任务。
  - 不过taskInfos是public的，这个设计貌似不太好
  - Task类也是差不多的

#### Painter

  - 用于打印信息、绘制时间状态图。内部分别有一个设备列表和任务列表。还有一个map，记录每一个设备or任务的名字。

    ```cpp
    map<Base*, string> base2name;
    vector<Equipment*> equipments;
    vector<Task*> tasks;
    ```

  - 主要思想是，通过add来添加要打印的设备和任务。根据设备和任务的信息，以及一些配置参数，进行打印or绘图操作。

### Painter 接口说明

英文名起的不太好，T_T

#### add(string name, Base* base);

  - 添加一个设备or任务进入列表里面。不然怎么知道要对谁进行操作呢？
  
- 会检测base的运行时实际类型，放入相应列表。同时会记录下base的名字为name.
  - 后面为了简化操作，使用了宏定义``` #define add(a) add((#a),(a))```，从main里面不需要传入名字了，只需要把局部变量的命名写好就行了.
  - 下面示例会记录下CPU的名字是“CPU”, 并把它放入equipments列表里面。
    ```cpp
    Base* CPU = new Equipment();
    painter->add(CPU);
    ```

#### buildByEquipmentInfoOfTask();

- 也是为了使用起来更方便。
- 比方说，已经手动算出了每个任务的使用设备信息，但我们还想查看设备的分别在哪些时间段被谁占用了，就可以调用它自动地根据任务的使用设备信息，来扩充设备被任务占用的信息。
- 这个方法会强行改equipment的taskInfos列表。前面也说了，taskInfos是public的，这样耦合不太好。

#### setSplit(int);

- 设置最顶部时间轴，每隔多少多少画一个刻度。

#### setPrintMode(int mode);

- 传入的mode必须是``` NO_PRINT_NAME  PRINT_NAME_INLINE  PRINT_NAME_ABOVE```之一，代表着要不要在轴上打印设备的名字，如果要，打印在哪些地方。默认是```PRINT_NAME_ABOVE```因为它方便改字体大小

#### setFontSize(int);

- 设置字体的大小。

#### setVerticalLineLen(int);

- 设置蓝色竖直虚线的长度。其实这些虚线没啥用，就拿来对齐而已。
- 也可以把VERTICAL_LINE改成"|"，那就是打印实线了，都差不多8
- 如果设置成0，就不打印它们
#### setLineSpacing(double);

- 设置行距。就是竖直的虚线，如果按照行距1，就会显得太稀疏了。建议设置成0.6766666  ^_^
- 如果竖直方向想打印实线，或者不打印，那还是用1吧。

#### setZoomIn(int) 和 setZoomOut(int)

- 有的题目总时间太大了，最大去到了300.  有的时间间隔太短了。所以通过放大缩小倍数来进行调整。
- 为了避免调整后是小数，导致数轴显示混乱：需要保证调整后，对于所有要显示的时间，time * zoom_in  % zoom_out == 0
- 相关内容可参考```bool checkVallid();``` ``` inline int getAdjustedValue(int value)```

#### printText();

- 打印信息

#### drawGraph();

- 画图