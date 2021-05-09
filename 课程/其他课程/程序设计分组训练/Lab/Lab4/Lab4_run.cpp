/* run �����ĺ���ʵ�� */
#include "Lab4_fun.h"
#include "Lab4_data.h"

#include <iostream>
using namespace std;

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <direct.h>
#include <io.h>

/* ȫ�ֱ��� */
CONF configinfo;

/*
*�������ƣ�run
*�������ܣ����������в���������·���������������ļ����ɺ���
*���������int argc, char *argv[]������main�����������в���
*����ֵ����
*�汾��Ϣ��
*/
void run(int argc, char *argv[])
{
	if (!init_conf()) //���ó�ʼ�����ñ�������
	{
		return;
	}

	char filepath[MAX_STR_LEN]; //�ݴ������·��
	char number[MAX_STR_LEN]; //�ݴ�����ļ�¼����

	memset(filepath, '\0', sizeof(filepath)); //��ʼ���ÿ�
	memset(number, '\0', sizeof(filepath));

	bool set_filepath = false; //�Ƿ�ָ���ļ�·��
	bool set_number = false; //�Ƿ�ָ�����ݼ�¼����

	bool user_def_dir = false; //�Ƿ��û��Զ���·��

	srand(time(0)); //��ʼ��������

	if (argc > 4) //�����������
	{
		printf("����!�������ࡣ");
		return;
	}

	/* ��ȷ���������в���ʱ���������в��� */
	while (--argc > 0) 
	{
		if (!illegal_number(*++argv) || strcmp(*argv, "r") == 0) //����ǺϷ����֣����������
		{
			if (strcmp(*argv, "r") == 0)
			{
				configinfo.number = rand_num(configinfo.recordcount2, configinfo.recordcount1); //�������
			}
			else
			{
				configinfo.number = atoi(*argv); //ת�������֣�����������
			}
			set_number = true;
			printf("��¼�������óɹ���\n");
		}
		else if (strcmp(*argv, "t") == 0 || strcmp(*argv, "d") == 0) //����ļ���ʽ
		{
			if (strcmp(*argv, "d") == 0) //�������ļ�
			{
				strcpy(configinfo.fileformat, "binary");
			}
			else
			{
				strcpy(configinfo.fileformat, "text");
			}
			printf("�ļ���ʽ�������óɹ���\n");
		}
		else if (!illegal_filepath(*argv)) //����ǺϷ�·��
		{
			strcpy(filepath, *argv); //�ݴ棬�Ա����
			set_filepath = true;
			printf("�ļ�·�����óɹ���\n");

			user_def_dir = true; //�û��Զ�����·��
		}
		else
		{
			printf("δʶ��������в�����%s\n", *argv);
		}
	}

		
	if (!set_number) //���û��������Ŀ
	{
		printf("û�з��ֺϷ��ļ�¼�������������¼������");

		do
		{
			cin >> number;

			if (!illegal_number(number)) //����ǺϷ�����
			{
				printf("��¼�������óɹ���\n");
				configinfo.number = atoi(number); //ת�������֣�����������
				set_number = true;
			}
			else
			{
				printf("����ļ�¼�����Ƿ�������Χ1~1000�����Ƿ�������ɼ�¼������Y/N��");
				char c; //���ڽ���ѡ��
				cin >> c;
				switch (c)
				{
				case'Y': case'y':
					configinfo.number = rand_num(configinfo.recordcount2, configinfo.recordcount1);
					set_number = true;
					printf("��¼�������óɹ���\n");
					continue;
				case'N': case'n':
					printf("�����������¼������");
					continue;
				default:
					printf("����!�����������¼������");
					continue;
				}

			} 

		} while (!set_number);
	}

	if (!set_filepath) //���û������·��
	{
		printf("û�з��ֺϷ����ļ�·�����������ļ�·����");
		do
		{
			cin >> filepath;

			if (!illegal_filepath(filepath)) //����ǺϷ�·��
			{
				user_def_dir = true; //�û��Զ���·��
				set_filepath = true;
				printf("�ļ�·�����óɹ���\n");
			}
			else
			{
				printf("�����·���Ƿ����Ƿ�ʹ��Ĭ��·����Y/N��");
				char c; //���ڽ���ѡ��
				cin >> c;
				switch (c)
				{
				case'Y': case'y':
					set_filepath = false; //�û�û���Զ���·��
					set_filepath = true;
					printf("�ļ�·�����óɹ���\n");
					continue;
				case'N': case'n':
					printf("����������·����");
					continue;
				default:
					printf("����!����������·����");
					continue;
				}
			}

		} while (!set_filepath);

	}

	if (user_def_dir) //����û��Զ���·��
	{
		separate_filepath(filepath); //����·�����ļ�������������
	}

	process_dir(); //����·��
	write(); //�����ļ�����

	return;
} 