/* run �����ĺ���ʵ�� */

#include "Lab3_fun.h"//һ����Ҫ
#include "Lab3_data.h"

#pragma warning(disable:4996)//Ϊʹ�ò���ȫ�ĺ�����fopen() �Լ� strcpy()

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void run(int argc, char *argv[])
{
	int c;//���ڽ���ѡ��

	char filepath[MAX_STR_LEN];//�ݴ������·��
	char number[MAXNUM];//�ݴ�����ļ�¼����

	bool set_filepath = false;//�Ƿ�ָ���ļ�·��
	bool set_number = false;//�Ƿ�ָ�����ݼ�¼����

	srand(time(0));//��ʼ��������

	if (argc > 3)//�����������
	{
		printf("����!�������ࡣ");
		return;
	}

	/* ��ȷ�����������в���ʱ���������в��� */
	while (--argc > 0)
	{
		if (!illegal_number(*++argv))//����ǺϷ�����
		{
			configinfo.number = atoi(*argv);
			set_number = true;
		}
		else if (!illegal_filepath(*argv)) //����ǺϷ�·��
		{
			strcpy(filepath, *argv);
			set_filepath = true;
		}

	}


	if (!set_number)//���û��������Ŀ
	{
		printf("û�з��ּ�¼�������������¼������\n");

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

	if (!set_filepath)//���û������·��
	{
		printf("û�з����ļ�·�����������ļ�·����\n");
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
	* ���������ŷּ���ģ�飺
	*	1.���������в�����
	*	2.���û������Ϸ������ֻ���·����Ҫ�󲹳����롣
		�����ˣ�·�������־��ɹ����棩
	*	3.���� ����·���ĺ�����������ļ����ͱ���·����
	*	4.���� �ļ����ɺ���
	*
	* ��д�ĺ�����
	*	1.	�ж� ���� �Ƿ�Ϸ�
	*		�ж� ·�� �Ƿ�Ϸ����
	*
	*	2.	����·���ĺ�����������ļ����ͱ���·����
	*
	*	3.	����ָ����Χ�������
	*		�ļ����ɺ������
	* 
	*	void random_record(int row);//�������ָ����������Ԫ��
	*	void write(char *filename, int row);//д���ļ�
	*	bool illegal_number(char *number);
	*	bool illegal_filepath(char *filepath);
	*	void process_filepath(char *filepath);
	*
	*************************************************/
	return;
}