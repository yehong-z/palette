### 中位切分法实现图片主色提取

#### visual studio中使用:


- Debug切换为Release, x86切换成x64
- 修改项目属性:
    - 设置头文件和链接库所在目录
    - C++ - 代码生成 - 运行库 改为 $/MT$
    - 链接器-依赖 中写入静态库名称
        ```c++
        palette.lib
        ```
- 在头文件中写上:
```c++
#include <test.h>
```
- 然后就可以调用链接库中的函数了.

#### 实现的功能

目前只实现了一个函数

##### cal_pale:

```c++
void cal_pale(std::string, int);
```
- 输入有效的图片文件路径和所需要的颜色数目, 即可在控制台上打印出图片主色的$[B,G,R]$值.

示例:
```c++
#include<test.h>
#include<string>
#include<iostream>
#include<ctime>

using namespace std;
int main()
{
    std::string s = R"图片路径代替";
    clock_t startTime, endTime;
    startTime = clock();
    cal_pale(s, 5);
    endTime = clock();
    cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    return 0;
}
```
- 控制台输出结果
```
color:
[59, 56, 78]
[136, 134, 144]
[121, 127, 168]
[134, 135, 168]
[124, 116, 135]
The run time is: 0.15s
```
