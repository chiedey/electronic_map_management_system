/************************************************************************/
/* 文件名称：structs_and_variable.h                                     */
/* 文件描述：定义工程所需的宏定义、相关全局变量及结构体                 */
/* 文件作者：翁启第                                                     */
/* 完成日期：2012年12月28日                                             */
/************************************************************************/
#ifndef _STRUCTSANDVARIABLE_H_
#define _STRUCTSANDVARIABLE_H_
//宏定义默认读取地址，如果需要可以修改
#define FILEPATH "./GTBL.dat"
//宏定义猜测数组大小，具体大小将在读取文件后确定，如果有必要可以修改
#define SIZE 71680
//定义结构体，成员包括用于存储道路各个信息的变量。该结构体作为存储一条道路信息的基本单位
typedef struct GTBL
{

    unsigned short sizeOfGTBL;      //记录该条数据所占字节数
    unsigned int   LinkID;          //道路编号
    unsigned short sizeOfRoadName;  //表示道路名称尺寸
             char  reserved[3];     //保留位
    unsigned int   flag;            //路线名称有无Flag
    unsigned int   brunch;          //岔路数
    unsigned int   dispClass;       //交叉Link列表示Class番号
             char *roadName;        //道路名称

}GTBL;
//定义结构体指针，以后为其分配一段内存空间用于存储数据
GTBL *Data;
/**
 * 数组边界，该值将在读取文件后确定，确定后*Data即可视为Data[maxSizeOfAry]数组
 * 注意：值范围应该是0 ~ maxSizeOfAry-1,取Data[maxSizeOfAry]无意义
 */
int maxSizeOfAry;

#endif