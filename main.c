﻿/************************************************************************/
/* 文件名称：main.c                                                     */
/* 文件描述：现阶段仅供测试使用                                         */
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
//包含公共接口，包括全局变量，各模块相关函数声明
#include "interface.h"

int main()
{
    //读取文件
    GetDataToAry(FILEPATH);

    system("pause");
    return 0;
}