/* run �������Ӻ�����ʵ�� */
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
	int item1; //���ݼ�¼��Ԫ���һ��Ԫ��
	int item2; //���ݼ�¼��Ԫ��ڶ���Ԫ��
	int item3; //���ݼ�¼��Ԫ�������Ԫ��
} DATAITEM;

bool write_text(const char fname[], DATAITEM *data);
bool write_binary(const char fname[], DATAITEM *data);


/*
*�������ƣ�write
*�������ܣ����������ļ�����
*�����������
*����ֵ����
*�汾��Ϣ��
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

	/* ���ɼ�¼������ṹ������ */
	start1 = clock();
	for (int i = 0; i < configinfo.number; i++)
	{
		p->item1 = rand_num(configinfo.minvalue1, configinfo.maxvalue1); //���ɵ�һ��Ԫ��
		do
		{
			p->item2 = rand_num(configinfo.minvalue1, configinfo.maxvalue1); //���ɵڶ���Ԫ�أ������һ��Ԫ����ͬ��
		} while (p->item2 == p->item1);
		p->item3 = rand_num(configinfo.minvalue2, configinfo.maxvalue2); //���ɵ�����Ԫ��
		p++;
	}
	finish1 = clock();
	double time = (double)(finish1 - start1) / CLOCKS_PER_SEC;
	cout << "\n���ɼ�¼��ɡ�\n\t";
	cout << "time:" << time << "s\n";

	/* �����ļ��� */
	char fname[_MAX_FNAME]; //�ļ���
	char ext[_MAX_EXT]; //��չ��
	_splitpath(configinfo.filename, NULL, NULL, fname, ext);


	/* д���ļ� */
	if (strcmp(configinfo.fileformat, "text") == 0) //�����ı��ļ�
	{
		write_text(fname, data);
	}
	else if (strcmp(configinfo.fileformat, "binary") == 0) //���ɶ������ļ�
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
*�������ƣ�init_conf
*�������ܣ���ʼ�����ñ�������
*�����������
*����ֵ��bool���ͣ���ʼ���ɹ�����1�����򷵻�0
*�汾��Ϣ��
*/
bool init_conf()
{
	extern CONF configinfo;
	configinfo.number = MAXNUM;
	char curdir[MAX_STR_LEN]; //��ŵ�ǰ·��(������)

	/* ���Դ��� */
	if (_getcwd(curdir, MAX_STR_LEN))
	{
		printf("��ǰ����·����%s\n\n", curdir);
	}

	if (access("conf.ini", 00)) //��������ļ�������
	{
		printf("����·����δ���������ļ������Զ����������ļ���\n");
		FILE *fp = fopen("conf.ini", "w");
		if (!fp)
		{
			printf("���������ļ�ʧ�ܣ�");
			return false;
		}

		/* ��ʼ���ļ�����·�� */
		strcpy(configinfo.filename, "dafault.txt"); //Ĭ���ļ���

		strcat(curdir, "\\OutputData\\"); //Ĭ�������ͬ����OutputDataĿ¼
		strcpy(configinfo.filesavepath, curdir);

		/* ��ʼ������Ĭ��ֵ */
		configinfo.maxvalue1 = MAXNUM;
		configinfo.minvalue1 = MINNUM;
		configinfo.maxvalue2 = MAXNUM;
		configinfo.minvalue2 = MINNUM;
		configinfo.recordcount1 = MAXNUM;
		configinfo.recordcount2 = MINNUM;

		fprintf(fp, "%s\n", configinfo.filesavepath); // 1��Ĭ�ϴ洢Ŀ¼
		fprintf(fp, "%s\n", configinfo.filename); // 2��Ĭ���ļ���
		fprintf(fp, "%d\n", configinfo.maxvalue1); // 3�����ݼ�¼��Ԫ����1��2Ԫ��ֵ������
		fprintf(fp, "%d\n", configinfo.minvalue1); // 4�����ݼ�¼��Ԫ����1��2Ԫ��ֵ������
		fprintf(fp, "%d\n", configinfo.maxvalue2); // 5�����ݼ�¼��Ԫ���е�3Ԫ��ֵ������
		fprintf(fp, "%d\n", configinfo.minvalue2); // 6�����ݼ�¼��Ԫ���е�3Ԫ��ֵ������
		fprintf(fp, "%d\n", configinfo.recordcount1); // 7�����ɵļ�¼��������
		fprintf(fp, "%d\n", configinfo.recordcount2); // 8�����ɵļ�¼��������

		printf("�����ļ����ɳɹ���\n\n");

		fclose(fp);
		return true;
	}
	else //�����ļ����ڣ�
	{
		printf("����·���·��������ļ�����ȡ�����ļ���\n");
		FILE *fp = fopen("conf.ini", "r"); //��ȡ�����ļ�
		if (!fp)
		{
			printf("��ȡ�����ļ�ʧ�ܣ�");
			return false;
		}

		fscanf(fp, "%s", configinfo.filesavepath); // 1��Ĭ�ϴ洢Ŀ¼
		fscanf(fp, "%s", configinfo.filename); // 2��Ĭ���ļ���
		fscanf(fp, "%d", &configinfo.maxvalue1); // 3�����ݼ�¼��Ԫ����1��2Ԫ��ֵ������
		fscanf(fp, "%d", &configinfo.minvalue1); // 4�����ݼ�¼��Ԫ����1��2Ԫ��ֵ������
		fscanf(fp, "%d", &configinfo.maxvalue2); // 5�����ݼ�¼��Ԫ���е�3Ԫ��ֵ������
		fscanf(fp, "%d", &configinfo.minvalue2); // 6�����ݼ�¼��Ԫ���е�3Ԫ��ֵ������
		fscanf(fp, "%d", &configinfo.recordcount1); // 7�����ɵļ�¼��������
		fscanf(fp, "%d", &configinfo.recordcount2); // 8�����ɵļ�¼��������

		printf("�����ļ���ȡ�ɹ���\n\n");

		fclose(fp);
		return true;
	}

	strcpy(configinfo.fileformat, "default"); //Ĭ��ͬʱ�����ı��ļ��Ͷ������ļ�

	return false;
}

/*
*�������ƣ�illegal_number
*�������ܣ��ж������в����Ƿ�Ϊ�Ϸ�����
*���������const char number[]����Ϊ���ֵ������в���
*����ֵ��bool���ͣ��ǷǷ������򷵻�1�����򷵻�0
*�汾��Ϣ��
*/
bool illegal_number(const char number[])
{
	if (strcmp(number, "") == 0) //���ַ�
	{
		return true; //���ǺϷ�����
	}

	int length = strlen(number);

	for (int i = 0; i < length; i++) //����ÿ���ַ�
	{
		if (!isdigit(number[i])) //������ַ���������
		{
			return true; //�ò����ַ����಻������
		}
	}
	int num = atoi(number); //�ݴ�����
	if (num<MINNUM || num>MAXNUM)
	{
		printf("������������ֲ�������ķ�Χ�ڡ�������Χ1~100000��\n");
		return true; //�ǷǷ�����
	}
	return false; //ͨ�������м�ˣ��ǺϷ�����
}

/*
*�������ƣ�illegal_filepath
*�������ܣ��ж������в����Ƿ�Ϊ�Ϸ�·��
*���������const char number[]����Ϊ·���������в���
*����ֵ��bool���ͣ��ǷǷ�·���򷵻�1�����򷵻�0
*�汾��Ϣ��
*/
bool illegal_filepath(const char filepath[])
{	
	/* ���ȷ����ļ�·�� */
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath(filepath, drive, dir, fname, ext);

	/* ����չ������ֱ��ȷ���ǷǷ�·�� */
	if (!strcmp(".txt", ext) || !strcmp(".dat", ext)) //��չ����ȷ������һ��strcmp()�Ľ����Ϊ0��
	{
		int length = strlen(fname);
		for (int i = 0; i < length; i++) //�����ļ����������зǷ��ַ���ȷ���ǷǷ�·��
		{
			switch (fname[i])
			{
			case':': case'*': case'?': case'\\': 
			case'<': case'>': case'|':
				printf("�����ļ����Ƿ���%s\n", fname);
				return true; //�Ƿ�

			default:
				break;
			}
		}

	}
	else //��չ������
	{
		printf("������չ��������%s\n", ext);
		return true;
	}

	/* δʶ����������� */
	return false; //����Ϊ��ȷ��ʽ
}

/*
*�������ƣ�separate_filepath
*�������ܣ�����·���������Ϊ�ļ��洢Ŀ¼���ļ����ƣ���������
*���������const char filepath[]���ļ�·��
*����ֵ����
*�汾��Ϣ��
*/
void separate_filepath(const char filepath[])
{
	/* ���ȷ����ļ�·�� */
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath(filepath, drive, dir, fname, ext);

	extern CONF configinfo;
	
	memset(configinfo.filesavepath, '\0', sizeof(configinfo.filesavepath)); //ԭ�����Ĭ��ֵ���ÿ�
	memset(configinfo.filename, '\0', sizeof(configinfo.filename));

	strcat(configinfo.filesavepath, drive); //�����ļ��洢Ŀ¼
	strcat(configinfo.filesavepath, dir);

	strcat(configinfo.filename, fname); //�����ļ���
	strcat(configinfo.filename, ext);

}

/*
*�������ƣ�process_dir
*�������ܣ�����·����ͨ����·���ֽ�Ϊ������·�������ת�롣
*�����������
*����ֵ����
*�汾��Ϣ��
*/
void process_dir()
{
	char curdir[MAX_STR_LEN]; //��ŵ�ǰ·��(������)
	extern CONF configinfo;

	if (strcmp(configinfo.filesavepath, "") != 0) //���·����Ϊ��
	{
		if (_access(configinfo.filesavepath, 00) == -1) //����ļ��в�����
		{
			printf("���õ�·�������ڣ�������·����\n");

			/* ���½���·������ */
			char drive[_MAX_DRIVE];
			char dir[_MAX_DIR];
			_splitpath(configinfo.filesavepath, drive, dir, NULL, NULL);
			printf("  Drive: %s\n", drive);
			printf("  Dir: %s\n", dir);
			printf("ע�⣺�Ϸ���Ŀ¼�ָ���Ϊ��/����\\����\n\n");

			if (strcmp(drive, "") == 0) //δ�����̷�
			{
				printf("δ�����̷������·����\n");
			}
			else //�������̷�
			{
				printf("�������̷�������·����\n");
				if (!isalpha(drive[0])) //��һ���ַ�������ĸ
				{
					printf("�̷�����%s\n", drive);
					return;
				}
				char cm[MAX_STR_LEN];
				sprintf(cm, "%s/", drive); //�������
				_chdir(cm); //�����̷�

				/* ���Դ��� */
				if (_getcwd(curdir, MAX_STR_LEN))
				{
					printf("��ǰ����·����%s\n", curdir);
				}
			}

			char *head, *tail; //·�������α�
			char path[MAX_STR_LEN]; //��Ŵ�ת����·��
			head = dir; //head��ʼʱָ��ͷ��

			/* ����·��ǰ���� */
			tail = head; //tailָ���head����ʼ�ƶ�
			while (*tail != '\\' && *tail != '/') //Ѱ��Ŀ¼�ָ���'\\'��'/'��λ��
			{
				tail++;
			}
			int i;
			for (i = 0; head < tail; head++) //����һ��·����������head == tail��
			{
				path[i] = *head;
				i++;
			}
			path[i] = '\0'; //�ַ���������

			if (strcmp(path, "") == 0) //˵����һ���ַ�Ϊ'/'
			{

				if (strcmp(drive, "") == 0)
				{
					printf("��һ���ַ�Ϊ��/������ת���̷���Ŀ¼\n");
					_chdir("/");

					/* ���Դ��� */
					if (_getcwd(curdir, MAX_STR_LEN))
					{
						printf("��ǰ����·����%s\n", curdir);
					}
				}
			}
			else if (strcmp(path, "..") == 0)
			{
				printf("������һ��·��\n");
				_chdir("..");

				/* ���Դ��� */
				if (_getcwd(curdir, MAX_STR_LEN))
				{
					printf("��ǰ����·����%s\n", curdir);
				}
			}
			else if (_access(path, 00) == -1) //�����һ���ļ��в�����
			{
				if (_mkdir(path) == -1) //����
				{
					printf("�����ļ���ʧ�ܣ�%s\n", path);
					return;
				}
				_chdir(path); //��ת cd path 

				/* ���Դ��� */
				if (_getcwd(curdir, MAX_STR_LEN))
				{
					printf("��ǰ����·����%s\n", curdir);
				}
			}
			else //�ļ��д��ڡ�cd path 
			{
				_chdir(path); //��ת cd path 

				/* ���Դ��� */
				if (_getcwd(curdir, MAX_STR_LEN))
				{
					printf("��ǰ����·����%s\n", curdir);
				}
			}

			/* ǰ����������� */

			/* ����·���ļ��� */
			while (*(tail + 1) != '\0')
			{
				head = tail + 1;
				tail = tail + 1;
				while (*tail != '\\' && *tail != '/' && *tail != '\0') //Ѱ��Ŀ¼�ָ���'\\'��'/'��λ�ã����β
				{
					tail++;
				}
				int i;
				for (i = 0; head < tail; head++) //����һ��·����������head == tail��
				{
					path[i] = *head;
					i++;
				}
				path[i] = '\0'; //�ַ���������
				if (strcmp(path, "") == 0)
				{
					printf("���󣡴��ڶ����Ŀ¼�ָ�����/����\\����\n\n");
				}
				if (strcmp(path, "..") == 0)
				{
					printf("������һ��·��\n");
					_chdir("..");
				}
				else if (_access(path, 00) == -1) //�����һ���ļ��в�����
				{
					if (_mkdir(path) == -1) //����
					{
						printf("�����ļ���ʧ�ܣ�\n%s", path);
						return;
					}
					_chdir(path); //��ת cd path 

					/* ���Դ��� */
					if (_getcwd(curdir, MAX_STR_LEN))
					{
						printf("��ǰ����·����%s\n", curdir);
					}
				}
				else //�ļ��д��ڡ�cd path 
				{
					_chdir(path); //��ת cd path 

					/* ���Դ��� */
					if (_getcwd(curdir, MAX_STR_LEN))
					{
						printf("��ǰ����·����%s\n", curdir);
					}
				}
			}
			printf("����·���ɹ���\n");
		}
		else //�ļ��д��� �� û��·��ֻ���ļ���
		{
			printf("���õ�·�����ڣ���ת��\n");
			_chdir(configinfo.filesavepath);
			/* ���Դ��� */
			if (_getcwd(curdir, MAX_STR_LEN))
			{
				printf("��ǰ����·����%s\n", curdir);
			}
		}
	}
}

/*
*�������ƣ�rand_num
*�������ܣ������ƶ���Χ�ڵ������
*���������int minvalue����ֵ����, int maxvalue����ֵ����
*����ֵ�����ɵ������
*�汾��Ϣ��
*/
int rand_num(int minvalue, int maxvalue)
{
	return minvalue + rand() % (maxvalue - minvalue + 1);
}

/*
*�������ƣ�write_text
*�������ܣ����ı��ļ���ʽд�������ļ���
*���������const char fname[]���ļ�����, DATAITEM *data���ṹ�������ַ
*����ֵ��bool���ͣ����ɳɹ�����1�����򷵻�0
*�汾��Ϣ��
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

	FILE *fp = fopen(filename, "w"); //���ļ�
	if (NULL == fp) //�ļ���ʧ��
	{
		printf("�ļ���ʧ��!\n");
		return false;
	}
	fprintf(fp, "%d\n", configinfo.number); //��ӡ��¼����
	for (int i = 0; i < configinfo.number; i++)
	{
		fprintf(fp, "%d,%d,%d\n", data[i].item1, data[i].item2, data[i].item3);
	}
	fclose(fp);

	finish2 = clock();
	double time = (double)(finish2 - start2) / CLOCKS_PER_SEC;
	cout << "�����ļ����ɳɹ������ı��ļ���\n\t";
	cout << "time:" << time << "s\n";
	return true;
}

/*
*�������ƣ�write_binary
*�������ܣ����ı��ļ���ʽд�������ļ���
*���������const char fname[]���ļ�����, DATAITEM *data���ṹ�������ַ
*����ֵ��bool���ͣ����ɳɹ�����1�����򷵻�0
*�汾��Ϣ��
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

	FILE *fp = fopen(filename, "wb"); //���ļ�
	if (NULL == fp) //�ļ���ʧ��
	{
		printf("�ļ���ʧ��!\n");
		return false;
	}

	fwrite(&configinfo.number, sizeof(int), 1, fp);
	fwrite(data, sizeof(DATAITEM), configinfo.number, fp);

	fclose(fp);

	finish3 = clock();
	double time = (double)(finish3 - start3) / CLOCKS_PER_SEC;
	cout << "�����ļ����ɳɹ������������ļ���\n\t";
	cout << "time:" << time << "s\n";
	return true;
}
