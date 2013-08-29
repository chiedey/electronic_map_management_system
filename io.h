/************************************************************************/
/* 文件名称：io.h                                                       */
/* 文件描述：IO模块接口头文件                                           */
/*           声明了IO模块的所有函数，包含了函数实现时所需的头文件       */
/* 文件作者：翁启第                                                     */
/* 完成日期：2012年12月28日                                             */
/************************************************************************/
#ifndef _IO_H_
#define _IO_H_
//所需头文件
#include <stdio.h>
#include <stdlib.h>
#include "structs_and_variable.h"
//接口函数声明
         void  GetDataToAry    (          char  *filePath );
         int   IsFileOpen      (          FILE  *stream   );
         void  SetNewFilePath  (          char **filePath );
unsigned short TransToShort    ( unsigned short  data     );
unsigned int   TransToInt      ( unsigned int    data     );
unsigned int   TransToFlag     ( unsigned int    data     );
unsigned int   TransToBrunch   ( unsigned int    data     );
unsigned int   TransToDispClass( unsigned int    data     );

#endif