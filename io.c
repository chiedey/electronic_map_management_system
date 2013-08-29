/************************************************************************/
/* 文件名称：io.c                                                       */
/* 文件描述：IO模块各个函数的具体实现部分                               */
/* 文件作者：翁启第                                                     */
/* 完成日期：2012年12月28日                                             */
/************************************************************************/
#include "io.h"
/************************************************************************/
/* 函数名称  ：void GetDataToAry( char *filePath )                      */
/* 函数描述  ：从二进制文件中读取二进制数据，并转换为相应的字符型、整型 */
/*             数据，存入到结构体数组中，供查找、排序调用               */
/* 返回值说明：返回值类型：void                                         */
/*             返回值含义：无需任何返回值                               */
/* 形参说明  ：形参类型  ：char*                                        */
/*             形参含义  ：该参数用于存放读取文件路径信息               */
/* 函数作者  ：翁启第                                                   */
/* 完成日期  ：2012年12月28日                                           */
/************************************************************************/
void GetDataToAry( char *filePath )
{

    FILE        *fileStream;
    GTBL         temp;
    unsigned int tmp;
    unsigned int k;
    //为结构体指针分配空间，模拟数组形式
    Data = (GTBL*)calloc( SIZE, sizeof(GTBL) );
    //打开文件
    fileStream = fopen( filePath, "rb" );
    //判断是否打开成功
    while(!IsFileOpen(fileStream))
    {   //如果打开失败，则手动修改读取路径，直至正确为止
        SetNewFilePath(&filePath);
        //根据新设置的路径重新打开文件
        fileStream = fopen( filePath, "rb" );
    }
    //打开成功后，顺序读取每一条道路信息，直至文件读取完毕
    for( k = 0; k<SIZE && !feof(fileStream); k++ )
    {   //获取该条道路数据所占字节数
        fread( &temp.sizeOfGTBL, 2, 1, fileStream );
        Data[k].sizeOfGTBL = TransToShort(temp.sizeOfGTBL);
        //获取该条道路编号
        fread( &temp.LinkID, 4, 1, fileStream );
        Data[k].LinkID = TransToInt(temp.LinkID);
        //获取该条道路名称尺寸
        fread( &temp.sizeOfRoadName, 2, 1, fileStream );
        Data[k].sizeOfRoadName = TransToShort(temp.sizeOfRoadName);
        //获取该条道路有无Flag信息、岔路数、番号
        fread( &tmp, 4, 1, fileStream );
        Data[k].flag = TransToFlag(tmp);
        Data[k].brunch = TransToBrunch(tmp);
        Data[k].dispClass = TransToDispClass(tmp);
        //获取该条道路名称
        Data[k].roadName = (char*)malloc( Data[k].sizeOfGTBL-12 );
        fread( Data[k].roadName, Data[k].sizeOfGTBL-12, 1, fileStream );
        /*测试（可删掉该段代码）*/
        printf("所占字节  道路编号  道路名称尺寸  有无Flag  岔路数  番号  道路名称\n");
        printf("%8d%10d%14d%10d%8d%6d%10s\n", Data[k].sizeOfGTBL, 
                                              Data[k].LinkID, 
                                              Data[k].sizeOfRoadName, 
                                              Data[k].flag, 
                                              Data[k].brunch, 
                                              Data[k].dispClass, 
                                              Data[k].roadName );
        /*测试（可删掉该段代码）*/
    }
    //确定数组边界
    maxSizeOfAry = k;
    //文件全部读取完毕后关闭文件
    fclose(fileStream);
}
/************************************************************************/
/* 函数名称  ：int IsFileOpen( FILE *stream )                           */
/* 函数描述  ：检查文件打开是否成功                                     */
/* 返回值说明：返回值类型：int                                          */
/*             返回值含义：正常读取文件返回1，读取失败返回0             */
/* 形参说明  ：形参类型  ：FILE*                                        */
/*             形参含义  ：接收传入的文件流指针，用以判断是否打开成功   */
/* 函数作者  ：翁启第                                                   */
/* 完成日期  ：2012年12月28日                                           */
/************************************************************************/
int IsFileOpen( FILE *stream )
{

    if( NULL == stream )
    {
        printf("文件打开错误!\n");
        return 0;
    }

    return 1;
}
/************************************************************************/
/* 函数名称  ：void SetNewFilePath( char **filePath )                   */
/* 函数描述  ：当默认读取路径出错时，此函数用于修改读取路径             */
/* 返回值说明：返回值类型：void                                         */
/*             返回值含义：无需任何返回值                               */
/* 形参说明  ：形参类型  ：char**                                       */
/*             形参含义  ：指向字符指针变量的指针，用于接收传入的存放路 */
/*                         径的指针变量的地址，以便在函数实现部分直接通 */
/*                         过访问该地址，随时改所存放的路径信息         */
/* 函数作者  ：翁启第                                                   */
/* 完成日期  ：2012年12月28日                                           */
/************************************************************************/
void SetNewFilePath( char **filePath )
{

    char *newFilePath = (char*)calloc( 36, sizeof(char) );

    printf("请输入读取路径: ");
    scanf ( "%s", newFilePath );

    *filePath = newFilePath;

}
/************************************************************************/
/* 函数名称  ：unsigned short TransToShort( unsigned short data )       */
/* 函数描述  ：通过位操作把未转换数据转换成正确的unsigned short类型数据 */
/* 返回值说明：返回值类型：unsigned short                               */
/*             返回值含义：返回转换后的unsigned short类型数据           */
/* 形参说明  ：形参类型  ：unsigned short                               */
/*             形参含义  ：用于接收传入的待转换数据                     */
/* 函数作者  ：翁启第                                                   */
/* 完成日期  ：2012年12月28日                                           */
/************************************************************************/
unsigned short TransToShort( unsigned short data )
{
    return ((data&0X00FF)<<8) | (data>>8);
}
/************************************************************************/
/* 函数名称  ：unsigned int TransToInt( unsigned int data )             */
/* 函数描述  ：通过位操作把未转换数据转换成正确的unsigned int类型数据   */
/* 返回值说明：返回值类型：unsigned int                                 */
/*             返回值含义：返回转换后的unsigned int类型数据             */
/* 形参说明  ：形参类型  ：unsigned int                                 */
/*             形参含义  ：用于接收传入的待转换数据                     */
/* 函数作者  ：翁启第                                                   */
/* 完成日期  ：2012年12月28日                                           */
/************************************************************************/
unsigned int TransToInt( unsigned int data )
{
    return (TransToShort(data&0X0000FFFF)<<16) | (TransToShort(data>>16));
}
/************************************************************************/
/* 函数名称  ：unsigned int TransToFlag( unsigned int data )            */
/* 函数描述  ：通过位操作把数据翻译成flag值                             */
/* 返回值说明：返回值类型：unsigned int                                 */
/*             返回值含义：返回翻译后的unsigned int类型flag数据         */
/* 形参说明  ：形参类型  ：unsigned int                                 */
/*             形参含义  ：用于接收传入的待翻译数据                     */
/* 函数作者  ：翁启第                                                   */
/* 完成日期  ：2012年12月28日                                           */
/************************************************************************/
unsigned int TransToFlag( unsigned int data )
{

    data = TransToInt(data);

    return (data>>7) & 1;
}
/************************************************************************/
/* 函数名称  ：unsigned int TransToBrunch( unsigned int data )          */
/* 函数描述  ：通过位操作把数据翻译成brunch值                           */
/* 返回值说明：返回值类型：unsigned int                                 */
/*             返回值含义：返回翻译后的unsigned int类型brunch数据       */
/* 形参说明  ：形参类型  ：unsigned int                                 */
/*             形参含义  ：用于接收传入的待翻译数据                     */
/* 函数作者  ：翁启第                                                   */
/* 完成日期  ：2012年12月28日                                           */
/************************************************************************/
unsigned int TransToBrunch( unsigned int data )
{

    data = TransToInt(data);

    return (data>>4) & 7;
}
/************************************************************************/
/* 函数名称  ：unsigned int TransToDispClass( unsigned int data )       */
/* 函数描述  ：通过位操作把数据翻译成dispClass值                        */
/* 返回值说明：返回值类型：unsigned int                                 */
/*             返回值含义：返回翻译后的unsigned int类型dispClass数据    */
/* 形参说明  ：形参类型  ：unsigned int                                 */
/*             形参含义  ：用于接收传入的待翻译数据                     */
/* 函数作者  ：翁启第                                                   */
/* 完成日期  ：2012年12月28日                                           */
/************************************************************************/
unsigned int TransToDispClass( unsigned int data )
{

    data = TransToInt(data);

    return data & 15;
}
