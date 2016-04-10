#define _CRT_SECURE_NO_WARNINGS 

# include<stdio.h>
# include<stdlib.h>

enum Tag      
{
	C_BEGIN,
	C_END,
};

void Convert(const char* fIn,char* fOut)
{
	FILE* Input = fopen(fIn, "r");
	if (NULL == Input)
	{
		printf("���ļ�%sʧ��\n",fIn);
		return;
	}	
	FILE* Output = fopen(fOut, "w");
	if (NULL == Input)
	{
		printf("���ļ�%sʧ��\n", fOut);
		return;
	}

	Tag tag = C_END;
	char ch = fgetc(Input);
	char second;
	while (ch != EOF)
	{
		switch (ch)
			{
			case '/':
				fputc('/', Output);
				second = fgetc(Input);
				if (second == '*')
				{
					//4.ƥ������
					if (tag == C_END) 
					{
						fputc('/', Output);
						tag = C_BEGIN;
					}
					else
					{
						fputc('*', Output);
					}
				}
				else if (second == '/')     // 7. ����c++ע�ͣ�����һ��
				{
					fputc(second, Output);
					char cur;
					do
					{
						cur = fgetc(Input);
						if (cur == EOF)
						{
							return;
						}
						fputc(cur, Output);
					} while (cur != '\n');
				}
				else
				{
					fputc(second, Output);
				}
				break;
			case '*':
				second = fgetc(Input);
				if (second == '/' && tag == C_BEGIN)   
				{	
					//  3. ��������
					char next = fgetc(Input);
					if (next != '\n' && next != EOF)
					{
						fputc('\n', Output);
						fseek(Input, -1, SEEK_CUR);   //6.����ע��  /**//**/
					}
					else
					{
						fputc(next, Output);
					}
					tag = C_END;
				}
				else                      //   2. /***/ 
				{
					fputc('*', Output);
					fseek(Input, -1, SEEK_CUR);
				}
				break;
			case '\n':
				fputc('\n', Output);
				// 5. ����ע��
				if (tag == C_BEGIN)
				{
					fputc('/', Output);
					fputc('/', Output);
				}
				break;
			default:
				fputc(ch, Output);
		}
		ch = fgetc(Input);
	}
	fclose(Input);
	fclose(Output);
}

void Test()
{
	Convert("Input.cpp","Output.cpp");
}
int main()
{
	Test();
	system("pause");
	return 0;
}
