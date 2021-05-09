/* run 函数的函数实现 */
#include "Lab3_fun.h"
#include "Lab3_data.h"

#include <iostream>
using namespace std;

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <direct.h>
#include <io.h>

/* 全局变量 */
CONF configinfo;

/*
*函数名称：run
*函数功能：处理命令行参数，调用路径处理函数，调用文件生成函数
*输入参数：int argc, char *argv[]：来自main函数的命令行参数
*返回值：无
*版本信息：
*/
void run(int argc, char *argv[])
{
	char curdir[MAX_STR_LEN]; //存放当前路径(测试用)

	/* 测试代码 */
	if (_getcwd(curdir, MAX_STR_LEN))
	{
		printf("当前工作路径：%s\n", curdir);
	}

	/* 初始化文件名和路径 */
	strcpy(configinfo.filename, "dafault.txt"); //默认文件名
	
	strcat(curdir, "\\OutputData\\"); //默认与程序同级的OutputData目录
	strcpy(configinfo.filesavepath, curdir);

	/* 初始化其他默认值 */
	configinfo.maxvalue1 = MAXNUM;
	configinfo.minvalue1 = MINNUM;
	configinfo.maxvalue2 = MAXNUM;
	configinfo.minvalue2 = MINNUM;
	configinfo.number = 0;
	configinfo.recordcount1 = MAXNUM;
	configinfo.recordcount2 = MINNUM;

	char filepath[MAX_STR_LEN]; //暂存输入的路径
	char number[MAX_STR_LEN]; //暂存输入的记录条数

	memset(filepath, '\0', sizeof(filepath)); //初始化置空
	memset(number, '\0', sizeof(filepath));

	bool set_filepath = false; //是否指定文件路径
	bool set_number = false; //是否指定数据记录条数

	bool user_def_dir = false; //是否用户自定义

	srand(time(0)); //初始化种子数

	if (argc > 3) //输入参数过多
	{
		printf("错误!参数过多。");
		return;
	}

	/* 正确输入命令行参数时，处理所有参数 */
	while (--argc > 0) 
	{
		if (!illegal_number(*++argv)) //如果是合法数字
		{
			configinfo.number = atoi(*argv); //转换成数字，存入配置中
			set_number = true;
			printf("记录条数设置成功。\n");
		}
		else if(!illegal_filepath(*argv)) //如果是合法路径
		{
			strcpy(filepath, *argv); //暂存，以便分离
			set_filepath = true;
			printf("文件路径设置成功。\n");

			user_def_dir = true; //用户自定义了路径
		}

	}

		
	if (!set_number) //如果没有设置数目
	{
		printf("没有发现合法的记录条数，请输入记录条数：");

		do
		{
			cin >> number;

			if (!illegal_number(number)) //如果是合法数字
			{
				printf("记录条数设置成功。\n");
				configinfo.number = atoi(number); //转换成数字，存入配置中
				set_number = true;
			}
			else
			{
				printf("输入的记录条数非法（允许范围1~1000），是否随机生成记录条数？Y/N：");
				char c; //用于接收选项
				cin >> c;
				switch (c)
				{
				case'Y': case'y':
					configinfo.number = rand_num(configinfo.recordcount2, configinfo.recordcount1);
					set_number = true;
					printf("记录条数设置成功。\n");
					continue;
				case'N': case'n':
					printf("请重新输入记录条数：");
					continue;
				default:
					printf("错误!请重新输入记录条数：");
					continue;
				}

			} 

		} while (!set_number);
	}

	if (!set_filepath) //如果没有设置路径
	{
		printf("没有发现合法的文件路径，请输入文件路径：");
		do
		{
			cin >> filepath;

			if (!illegal_filepath(filepath)) //如果是合法路径
			{
				user_def_dir = true; //用户自定义路径
				set_filepath = true;
				printf("文件路径设置成功。\n");
			}
			else
			{
				printf("输入的路径非法，是否使用默认路径？Y/N：");
				char c; //用于接收选项
				cin >> c;
				switch (c)
				{
				case'Y': case'y':
					set_filepath = false; //用户没有自定义路径
					set_filepath = true;
					printf("文件路径设置成功。\n");
					continue;
				case'N': case'n':
					printf("请重新输入路径：");
					continue;
				default:
					printf("错误!请重新输入路径：");
					continue;
				}
			}

		} while (!set_filepath);

	}

	if (user_def_dir) //如果用户自定义路径
	{
		process_filepath(filepath); //分离路径及文件名，存入配置
	}
	
	write(); //数据文件生成

	return;
} 
