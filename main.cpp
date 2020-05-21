#include"head.h"
int main()
{
	//github测试 
	ListInitiate(&head);
	Load();//加载已有的数据到链表
	Menu();
	Save();//保存数据到文件
	printf("欢迎下次使用！\n");
}
