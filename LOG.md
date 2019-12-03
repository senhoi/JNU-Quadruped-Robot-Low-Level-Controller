# 开发日志
## 2019/12/03
#### Bug记录
* 表现：循环进入init_task()，不进入loop_task()
* 原因：SCA_API.h 中宏定义使用的执行器数量与实际数量不符
~~~c
#define SCA_NUM_USE		1
~~~
* 解决：将宏定义改成与init_task_innfos()函数中定义的驱动器数量相符