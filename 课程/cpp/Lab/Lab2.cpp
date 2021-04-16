#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MINNUM 1
#define MAXNUM 1000

#pragma warning(disable:4996)//为使用不安全的函数，fopen() 以及 strcpy()

//全局变量声明
int data[MAXNUM][3];//数据存储容器

//函数声明
void random_record(int row);//随机生成指定行数的三元组
void write(char *filename, int row);//写入文件

/*
*函数名称：main
*函数功能：数据文件自动生成
*输入参数：可选的命令行参数
*返回值：无
*版本信息：
*/
int main(int argc, char *argv[])
{
	char filename[100];//存放文件名称
	char number[100];//存放数据记录的条数
	int row = 0;//记录转换后的数据记录的条数
	int c;//用于接收选项
	bool set_filename = false;//是否指定文件名称
	bool set_number = false;//是否指定数据记录条数

	srand(time(0));//初始化种子数

	/* 输入命令行参数时，处理所有参数 */
	/* 支持的输入格式为：-n:指定的条数 -f:文件名 */
	while (--argc > 0 && (*++argv)[0] == '-')
		// *argv是一个指向参数字符串的指针，因此 (*argv)[0]是它的第一个字符
		switch (c = (*argv)[1]) //识别第二个字符
		{
		case 'n':
			if ((*argv)[2] == ':')
			{
				set_number = true;

				int i = 3, j = 0;
				while ((*argv)[i] != '\0')
				{
					number[j++] = (*argv)[i++];//保存数据记录的条数
				}
				number[j] = '\0';
				row = atoi(number);

				if (row > MAXNUM || row < MINNUM)//数据记录条数不在允许的范围内
				{
					printf("Error: The number of records is too large.\n");
					printf("\tThe supported size is 1~1000\n");
					printf("\tThis parameter will be set random.\n\n");

				}
			}
			else//数据记录条数格式错误
			{
				printf("Find: The number of records formal error.\n");
				printf("\tThe correct format is:-n:* -f:*.txt\n");
				printf("\tThis parameter will be set random.\n\n");
			}
			break;


		case 'f':
			if ((*argv)[2] == ':')
			{
				set_filename = true;

				int i = 3, j = 0;
				while ((*argv)[i] != '\0')
				{
					filename[j++] = (*argv)[i++];//保存文件名称
				}
				filename[j] = '\0';
			}
			else//文件名格式错误
			{
				printf("Find: Filename formal error.\n");
				printf("\tThe correct format is:-n:* -f:*.txt\n");
				printf("\tThis parameter will be set to default.\n\n");
			}
			break;

			/* 出现不支持的参数 */
		default:
			printf("Find: Illegal option : %c\n", c);
			printf("\tThe correct format is:-n:* -f:*.txt\n");
			printf("\tFilename or number of records will be set to default.\n\n");
			argc = 0;
			break;
		}

	/* 没有输入命令行参数时 */
	if (!set_filename)//若用户不输入文件名参数，则由程序默认指定一个文件名称（命令行参数格式错误时，也将执行）
	{
		strcpy(filename, "record.txt");
	}
	if (!set_number)//若用户不输入数据记录条数参数，则数据记录的条数由随机函数生成（命令行参数格式错误时，也将执行）
	{
		row = MINNUM + rand() % (MAXNUM - MINNUM + 1);
	}

	random_record(row);
	write(filename, row);
	printf("The file was successfully generated.");

	return 0;


}

/*
*函数名称：random_record
*函数功能：生成三元组
*输入参数：int row 行数
*返回值：无
*版本信息：
*/
void random_record(int row)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			data[i][j] = MINNUM + rand() % (MAXNUM - MINNUM + 1);
		}
	}
	return;
}

/*
*函数名称：write
*函数功能：写入编辑文件
*输入参数：char *filename 名称，int row 行数
*返回参数：无
*版本信息：
*/
void write(char *filename, int row)
{

	FILE *fp = fopen(filename, "w");

	if (NULL == fp)
	{
		printf("Cannot open file!");
		exit(0);
	}

	fprintf(fp, "%d\n", row);//打印条数
	for (int i = 0; i < row; i++)//逐条打印记录
	{
		fprintf(fp, "%d,%d,%d\n", data[i][0], data[i][1], data[i][2]);
	}
	fclose(fp);
	return;
}
