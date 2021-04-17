/* run 函数的子函数的实现 */
#include "Lab4_fun.h"
#include "Lab4_data.h"

#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <time.h>
#include <io.h>

#include <iostream>
using namespace std;

typedef struct DataItem {
	int item1; //数据记录三元组第一个元素
	int item2; //数据记录三元组第二个元素
	int item3; //数据记录三元组第三个元素
} DATAITEM;

bool write_text(const char fname[], DATAITEM *data);
bool write_binary(const char fname[], DATAITEM *data);


/*
*函数名称：write
*函数功能：生成数据文件函数
*输入参数：无
*返回值：无
*版本信息：
*/
void write()
{
	extern CONF configinfo;
	DATAITEM *data = (DATAITEM *)malloc(configinfo.number * sizeof(DATAITEM));
	if (NULL == data)
	{
		return;
	}
	DATAITEM *p = data;
	clock_t start1, finish1;

	/* 生成记录并存入结构体数组 */
	start1 = clock();
	for (int i = 0; i < configinfo.number; i++)
	{
		p->item1 = rand_num(configinfo.minvalue1, configinfo.maxvalue1); //生成第一个元素
		do
		{
			p->item2 = rand_num(configinfo.minvalue1, configinfo.maxvalue1); //生成第二个元素（不与第一个元素相同）
		} while (p->item2 == p->item1);
		p->item3 = rand_num(configinfo.minvalue2, configinfo.maxvalue2); //生成第三个元素
		p++;
	}
	finish1 = clock();
	double time = (double)(finish1 - start1) / CLOCKS_PER_SEC;
	cout << "\n生成记录完成。\n\t";
	cout << "time:" << time << "s\n";

	/* 分离文件名 */
	char fname[_MAX_FNAME]; //文件名
	char ext[_MAX_EXT]; //扩展名
	_splitpath(configinfo.filename, NULL, NULL, fname, ext);


	/* 写入文件 */
	if (strcmp(configinfo.fileformat, "text") == 0) //生成文本文件
	{
		write_text(fname, data);
	}
	else if (strcmp(configinfo.fileformat, "binary") == 0) //生成二进制文件
	{
		write_binary(fname, data);
	}
	else //default
	{
		write_text(fname, data);
		write_binary(fname, data);
	}

	free(data);

	return;
}

/*
*函数名称：init_conf
*函数功能：初始化配置变量函数
*输入参数：无
*返回值：bool类型：初始化成功返回1，否则返回0
*版本信息：
*/
bool init_conf()
{
	extern CONF configinfo;
	configinfo.number = MAXNUM;
	strcpy(configinfo.fileformat, "default"); //默认同时生成文本文件和二进制文件
	
	char curdir[MAX_STR_LEN]; //存放当前路径(测试用)

	/* 测试代码 */
	if (_getcwd(curdir, MAX_STR_LEN))
	{
		printf("当前工作路径：%s\n\n", curdir);
	}

	if (access("conf.ini", 00)) //如果配置文件不存在
	{
		printf("程序路径下未发现配置文件，将自动生成配置文件。\n");
		FILE *fp = fopen("conf.ini", "w");
		if (!fp)
		{
			printf("生成配置文件失败！");
			return false;
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
		configinfo.recordcount1 = MAXNUM;
		configinfo.recordcount2 = MINNUM;

		fprintf(fp, "%s\n", configinfo.filesavepath); // 1：默认存储目录
		fprintf(fp, "%s\n", configinfo.filename); // 2：默认文件名
		fprintf(fp, "%d\n", configinfo.maxvalue1); // 3：数据记录三元组中1、2元素值的上限
		fprintf(fp, "%d\n", configinfo.minvalue1); // 4：数据记录三元组中1、2元素值的下限
		fprintf(fp, "%d\n", configinfo.maxvalue2); // 5：数据记录三元组中第3元素值的上限
		fprintf(fp, "%d\n", configinfo.minvalue2); // 6：数据记录三元组中第3元素值的下限
		fprintf(fp, "%d\n", configinfo.recordcount1); // 7：生成的记录条数上限
		fprintf(fp, "%d\n", configinfo.recordcount2); // 8：生成的记录条数下限

		printf("配置文件生成成功。\n\n");

		fclose(fp);
		return true;
	}
	else //配置文件存在，
	{
		printf("程序路径下发现配置文件，读取配置文件。\n");
		FILE *fp = fopen("conf.ini", "r"); //读取配置文件
		if (!fp)
		{
			printf("读取配置文件失败！");
			return false;
		}

		fscanf(fp, "%s", configinfo.filesavepath); // 1：默认存储目录
		fscanf(fp, "%s", configinfo.filename); // 2：默认文件名
		fscanf(fp, "%d", &configinfo.maxvalue1); // 3：数据记录三元组中1、2元素值的上限
		fscanf(fp, "%d", &configinfo.minvalue1); // 4：数据记录三元组中1、2元素值的下限
		fscanf(fp, "%d", &configinfo.maxvalue2); // 5：数据记录三元组中第3元素值的上限
		fscanf(fp, "%d", &configinfo.minvalue2); // 6：数据记录三元组中第3元素值的下限
		fscanf(fp, "%d", &configinfo.recordcount1); // 7：生成的记录条数上限
		fscanf(fp, "%d", &configinfo.recordcount2); // 8：生成的记录条数下限

		printf("配置文件读取成功。\n\n");

		fclose(fp);
		return true;
	}
}

/*
*函数名称：illegal_number
*函数功能：判断命令行参数是否为合法数字
*输入参数：const char number[]：视为数字的命令行参数
*返回值：bool类型：是非法数字则返回1，否则返回0
*版本信息：
*/
bool illegal_number(const char number[])
{
	if (strcmp(number, "") == 0) //空字符
	{
		return true; //不是合法数字
	}

	int length = strlen(number);

	for (int i = 0; i < length; i++) //遍历每个字符
	{
		if (!isdigit(number[i])) //如果该字符不是数字
		{
			return true; //该参数字符串亦不是数字
		}
	}
	int num = atoi(number); //暂存数据
	if (num<MINNUM || num>MAXNUM)
	{
		printf("错误：输入的数字不在允许的范围内。（允许范围1~100000）\n");
		return true; //是非法数字
	}
	return false; //通过了所有检核，是合法数字
}

/*
*函数名称：illegal_filepath
*函数功能：判断命令行参数是否为合法路径
*输入参数：const char number[]：视为路径的命令行参数
*返回值：bool类型：是非法路径则返回1，否则返回0
*版本信息：
*/
bool illegal_filepath(const char filepath[])
{	
	/* 首先分离文件路径 */
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath(filepath, drive, dir, fname, ext);

	/* 若扩展名错误，直接确定是非法路径 */
	if (!strcmp(".txt", ext) || !strcmp(".dat", ext)) //扩展名正确（其中一个strcmp()的结果将为0）
	{
		int length = strlen(fname);
		for (int i = 0; i < length; i++) //遍历文件名，若含有非法字符，确定是非法路径
		{
			switch (fname[i])
			{
			case':': case'*': case'?': case'\\': 
			case'<': case'>': case'|':
				printf("错误：文件名非法：%s\n", fname);
				return true; //非法

			default:
				break;
			}
		}

	}
	else //扩展名不符
	{
		printf("错误：扩展名不符：%s\n", ext);
		return true;
	}

	/* 未识别出其他错误 */
	return false; //暂认为正确格式
}

/*
*函数名称：separate_filepath
*函数功能：分离路径，将其分为文件存储目录和文件名称，存入配置
*输入参数：const char filepath[]：文件路径
*返回值：无
*版本信息：
*/
void separate_filepath(const char filepath[])
{
	/* 首先分离文件路径 */
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath(filepath, drive, dir, fname, ext);

	extern CONF configinfo;
	
	memset(configinfo.filesavepath, '\0', sizeof(configinfo.filesavepath)); //原本存放默认值，置空
	memset(configinfo.filename, '\0', sizeof(configinfo.filename));

	strcat(configinfo.filesavepath, drive); //存入文件存储目录
	strcat(configinfo.filesavepath, dir);

	strcat(configinfo.filename, fname); //存入文件名
	strcat(configinfo.filename, ext);

}

/*
*函数名称：process_dir
*函数功能：处理路径。通过将路径分解为若干子路径，逐个转入。
*输入参数：无
*返回值：无
*版本信息：
*/
void process_dir()
{
	char curdir[MAX_STR_LEN]; //存放当前路径(测试用)
	extern CONF configinfo;

	if (strcmp(configinfo.filesavepath, "") != 0) //如果路径不为空
	{
		if (_access(configinfo.filesavepath, 00) == -1) //如果文件夹不存在
		{
			printf("设置的路径不存在，将创建路径。\n");

			/* 以下进行路径处理 */
			char drive[_MAX_DRIVE];
			char dir[_MAX_DIR];
			_splitpath(configinfo.filesavepath, drive, dir, NULL, NULL);
			printf("  Drive: %s\n", drive);
			printf("  Dir: %s\n", dir);
			printf("注意：合法的目录分隔符为“/”或“\\”。\n\n");

			if (strcmp(drive, "") == 0) //未设置盘符
			{
				printf("未设置盘符，相对路径。\n");
			}
			else //设置了盘符
			{
				printf("设置了盘符，绝对路径。\n");
				if (!isalpha(drive[0])) //第一个字符不是字母
				{
					printf("盘符错误！%s\n", drive);
					return;
				}
				char cm[MAX_STR_LEN];
				sprintf(cm, "%s/", drive); //组成命令
				_chdir(cm); //进入盘符

				/* 测试代码 */
				if (_getcwd(curdir, MAX_STR_LEN))
				{
					printf("当前工作路径：%s\n", curdir);
				}
			}

			char *head, *tail; //路径处理游标
			char path[MAX_STR_LEN]; //存放待转到的路径
			head = dir; //head初始时指向头部

			/* 处理路径前导符 */
			tail = head; //tail指针从head处开始移动
			while (*tail != '\\' && *tail != '/') //寻找目录分隔符'\\'或'/'的位置
			{
				tail++;
			}
			int i;
			for (i = 0; head < tail; head++) //拷贝一级路径。结束后head == tail。
			{
				path[i] = *head;
				i++;
			}
			path[i] = '\0'; //字符串结束符

			if (strcmp(path, "") == 0) //说明第一个字符为'/'
			{

				if (strcmp(drive, "") == 0)
				{
					printf("第一个字符为“/”，跳转到盘符根目录\n");
					_chdir("/");

					/* 测试代码 */
					if (_getcwd(curdir, MAX_STR_LEN))
					{
						printf("当前工作路径：%s\n", curdir);
					}
				}
			}
			else if (strcmp(path, "..") == 0)
			{
				printf("返回上一级路径\n");
				_chdir("..");

				/* 测试代码 */
				if (_getcwd(curdir, MAX_STR_LEN))
				{
					printf("当前工作路径：%s\n", curdir);
				}
			}
			else if (_access(path, 00) == -1) //如果这一级文件夹不存在
			{
				if (_mkdir(path) == -1) //创建
				{
					printf("创建文件夹失败！%s\n", path);
					return;
				}
				_chdir(path); //跳转 cd path 

				/* 测试代码 */
				if (_getcwd(curdir, MAX_STR_LEN))
				{
					printf("当前工作路径：%s\n", curdir);
				}
			}
			else //文件夹存在。cd path 
			{
				_chdir(path); //跳转 cd path 

				/* 测试代码 */
				if (_getcwd(curdir, MAX_STR_LEN))
				{
					printf("当前工作路径：%s\n", curdir);
				}
			}

			/* 前导符处理完毕 */

			/* 处理路径文件夹 */
			while (*(tail + 1) != '\0')
			{
				head = tail + 1;
				tail = tail + 1;
				while (*tail != '\\' && *tail != '/' && *tail != '\0') //寻找目录分隔符'\\'或'/'的位置，或结尾
				{
					tail++;
				}
				int i;
				for (i = 0; head < tail; head++) //拷贝一级路径。结束后head == tail。
				{
					path[i] = *head;
					i++;
				}
				path[i] = '\0'; //字符串结束符
				if (strcmp(path, "") == 0)
				{
					printf("错误！存在多余的目录分隔符“/”或“\\”。\n\n");
				}
				if (strcmp(path, "..") == 0)
				{
					printf("返回上一级路径\n");
					_chdir("..");
				}
				else if (_access(path, 00) == -1) //如果这一级文件夹不存在
				{
					if (_mkdir(path) == -1) //创建
					{
						printf("创建文件夹失败！\n%s", path);
						return;
					}
					_chdir(path); //跳转 cd path 

					/* 测试代码 */
					if (_getcwd(curdir, MAX_STR_LEN))
					{
						printf("当前工作路径：%s\n", curdir);
					}
				}
				else //文件夹存在。cd path 
				{
					_chdir(path); //跳转 cd path 

					/* 测试代码 */
					if (_getcwd(curdir, MAX_STR_LEN))
					{
						printf("当前工作路径：%s\n", curdir);
					}
				}
			}
			printf("创建路径成功。\n");
		}
		else //文件夹存在 或 没有路径只有文件名
		{
			printf("设置的路径存在，跳转。\n");
			_chdir(configinfo.filesavepath);
			/* 测试代码 */
			if (_getcwd(curdir, MAX_STR_LEN))
			{
				printf("当前工作路径：%s\n", curdir);
			}
		}
	}
}

/*
*函数名称：rand_num
*函数功能：生成制定范围内的随机数
*输入参数：int minvalue：数值下限, int maxvalue：数值上限
*返回值：生成的随机数
*版本信息：
*/
int rand_num(int minvalue, int maxvalue)
{
	return minvalue + rand() % (maxvalue - minvalue + 1);
}

/*
*函数名称：write_text
*函数功能：以文本文件形式写入数据文件。
*输入参数：const char fname[]：文件名称, DATAITEM *data：结构数组基地址
*返回值：bool类型：生成成功返回1，否则返回0
*版本信息：
*/
bool write_text(const char fname[], DATAITEM *data)
{
	extern CONF configinfo;
	clock_t start2, finish2;

	char filename[MAX_STR_LEN];
	memset(filename, '\0', sizeof(filename));
	strcat(filename, fname);
	strcat(filename, ".txt");

	start2 = clock();

	FILE *fp = fopen(filename, "w"); //打开文件
	if (NULL == fp) //文件打开失败
	{
		printf("文件打开失败!\n");
		return false;
	}
	fprintf(fp, "%d\n", configinfo.number); //打印记录条数
	for (int i = 0; i < configinfo.number; i++)
	{
		fprintf(fp, "%d,%d,%d\n", data[i].item1, data[i].item2, data[i].item3);
	}
	fclose(fp);

	finish2 = clock();
	double time = (double)(finish2 - start2) / CLOCKS_PER_SEC;
	cout << "数据文件生成成功。（文本文件）\n\t";
	cout << "time:" << time << "s\n";
	return true;
}

/*
*函数名称：write_binary
*函数功能：以文本文件形式写入数据文件。
*输入参数：const char fname[]：文件名称, DATAITEM *data：结构数组基地址
*返回值：bool类型：生成成功返回1，否则返回0
*版本信息：
*/
bool write_binary(const char fname[], DATAITEM *data)
{
	extern CONF configinfo;
	clock_t start3, finish3;

	char filename[MAX_STR_LEN];
	memset(filename, '\0', sizeof(filename));
	strcat(filename, fname);
	strcat(filename, ".bin");

	start3 = clock();

	FILE *fp = fopen(filename, "wb"); //打开文件
	if (NULL == fp) //文件打开失败
	{
		printf("文件打开失败!\n");
		return false;
	}

	fwrite(&configinfo.number, sizeof(int), 1, fp);
	fwrite(data, sizeof(DATAITEM), configinfo.number, fp);

	fclose(fp);

	finish3 = clock();
	double time = (double)(finish3 - start3) / CLOCKS_PER_SEC;
	cout << "数据文件生成成功。（二进制文件）\n\t";
	cout << "time:" << time << "s\n";
	return true;
}
