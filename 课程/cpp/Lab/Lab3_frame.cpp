/* run 函数的函数实现 */

#include "Lab3_fun.h"//一定需要
#include "Lab3_data.h"

#pragma warning(disable:4996)//为使用不安全的函数，fopen() 以及 strcpy()

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void run(int argc, char *argv[])
{
	int c;//用于接收选项

	char filepath[MAX_STR_LEN];//暂存输入的路径
	char number[MAXNUM];//暂存输入的记录条数

	bool set_filepath = false;//是否指定文件路径
	bool set_number = false;//是否指定数据记录条数

	srand(time(0));//初始化种子数

	if (argc > 3)//输入参数过多
	{
		printf("错误!参数过多。");
		return;
	}

	/* 正确个数的命令行参数时，处理所有参数 */
	while (--argc > 0)
	{
		if (!illegal_number(*++argv))//如果是合法数字
		{
			configinfo.number = atoi(*argv);
			set_number = true;
		}
		else if (!illegal_filepath(*argv)) //如果是合法路径
		{
			strcpy(filepath, *argv);
			set_filepath = true;
		}

	}


	if (!set_number)//如果没有设置数目
	{
		printf("没有发现记录条数，请输入记录条数：\n");

		do
		{
			scanf("%s", number);

			if (!illegal_number(number))
			{
				configinfo.number = atoi(*argv);
				set_number = true;
			}
			else
			{


			}

		} while (!set_number);
	}

	if (!set_filepath)//如果没有设置路径
	{
		printf("没有发现文件路径，请输入文件路径：\n");
		do
		{
			scanf("%s", filepath);

			if (!illegal_filepath(filepath))
			{
				set_filepath = true;
			}
			else
			{

			}

		} while (!set_filepath);

	}

	process_filepath(filepath);
	random_record(configinfo.number);
	write();

	/*************************************************
	* 整个程序大概分几个模块：
	*	1.处理命令行参数。
	*	2.如果没有输入合法的数字或者路径，要求补充输入。
		（至此，路径及数字均成功保存）
	*	3.调用 处理路径的函数（分离出文件名和保存路径）
	*	4.调用 文件生成函数
	*
	* 编写的函数：
	*	1.	判断 数字 是否合法
	*		判断 路径 是否合法（★）
	*
	*	2.	处理路径的函数（分离出文件名和保存路径）
	*
	*	3.	生成指定范围内随机数
	*		文件生成函数（★）
	* 
	*	void random_record(int row);//随机生成指定行数的三元组
	*	void write(char *filename, int row);//写入文件
	*	bool illegal_number(char *number);
	*	bool illegal_filepath(char *filepath);
	*	void process_filepath(char *filepath);
	*
	*************************************************/
	return;
}