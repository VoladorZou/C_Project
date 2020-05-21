#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//枚举型岗位：销售员、技术员、销售经理、经理
enum workpost { SALESMAN = 0, TECHNICIAN, SALESMANAGER, MANAGER };
//员工类型：链表结点
struct Employee {
	int  id;				//员工号：主键，唯一
	char name[10];			//姓名
	char sex[3];			//性别：男或女
	int  age;				//年龄
	char department[20];	//部门
	enum workpost post;		//枚举型岗位
	int  workHour;			//当月工作小时数
	double sales;			//当月月销售额
	double salary;			//月工资
	struct Employee * next;//链表的指针域
};
#define LENGTH 50
//全局变量
Employee Employees[LENGTH];
typedef int DataType;
Employee *head;
int select = 1;//功能选择变量
int subselect = 1;//子功能选择变量
FILE *fp;
int i = 0;//循环变量
//函数声明
void ListInitiate(Employee **head);
void Load();
void Check();
void AddData();
void UpdataData();
void QueryData();
void DeleteData();
void Sorting();
void Statistics();
void Save();
//菜单函数
  //要求：至少有两层菜单。
void Menu()
{
	while (select)
	{
		printf("————————员工工资管理系统————————\n");
		printf("————1. 增添数据           2. 修改数据————\n");
		printf("————3. 查找数据           4. 删除数据————\n");
		printf("————5. 排序函数           6. 统计数据————\n");
		printf("————0. 退出程序           7. 查看链表————\n");
		printf("请输入你的选择：\n");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			AddData();
			break;
		case 2:
			UpdataData();
			break;
		case 3:
			QueryData();
			break;
		case 4:
			DeleteData();
			break;
		case 5:
			Sorting();
			break;
		case 6:
			Statistics();
			break;
		case 7:
			Check();
			break;
		case 0: break;
		default: printf("输入错误！请重新选择。\n");
		}
	}
}
//功能函数
  //初始化链表函数
void ListInitiate(Employee **head)//head是一个指针，*head也是一个指针
{
	*head = (Employee *)malloc(sizeof(Employee));//申请头结点
	(*head)->next = NULL;
}
//必须用文件来存储员工信息：
	//开始运行程序时从文件中读取员工信息到链表，退出程序时将员工信息保存到文件中。
void Load() {
	if ((fp = fopen("Employee.txt", "ab+")) == NULL)
	{
		printf("打开文件出错！\n");
		exit(1);
	}
	//未知文件长度，使用feof(FILE *Stream)判断文件结尾
	while (!feof(fp))
	{
		//feof(fp)通过fread/fscanf是否读写出错判断，应该在读写操作之后进行判断，否则多进行一轮循环
		if (fread(&Employees[i], sizeof(struct Employee), 1, fp) == 0)
		{
			continue;
		}
		Employee *p, *q;//分别用于指向第i个结点和待插入的新结点
		p = head;
		while (p->next != NULL)//把指针P定位到链表尾位置
		{
			p = p->next;
		}
		q = (Employee *)malloc(sizeof(Employee));//用指针Q申请新结点
		//存入数据到链表结点
		q->id = i;
		q->id++;
		strcpy(q->name, Employees[i].name);
		strcpy(q->sex, Employees[i].sex);
		q->age = Employees[i].age;
		strcpy(q->department, Employees[i].department);
		q->post = Employees[i].post;
		q->workHour = Employees[i].workHour;
		q->sales = Employees[i].sales;//当月月销售额
		q->salary = Employees[i].salary;//月工资
		q->next = p->next;//Q指针的next域指向P指针的next域，即第i个结点
		p->next = q;
		i++;
	}
	fclose(fp);
}
//检查链表数据输入是否准确
void Check()
{
	Employee *p;
	p = head;
	if (p->next == NULL)
	{
		printf("链表为空！\n");
	}
	else
	{
		printf("链表数据内容为：\n");
		while (p->next != NULL)
		{
			p = p->next;
			printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("数据有误！\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
		}
		printf("输出完毕！\n");
	}
}
//增添数据
  //添加一个员工，只输入该员工的基本信息（姓名、年龄、性别、部门、岗位）。
void AddData()
{
	Employee *p, *q;//分别用于指向第i个结点和待插入的新结点
	p = head;
	while (p->next != NULL)//把指针P定位到链表尾位置
	{
		p = p->next;
	}
	q = (Employee *)malloc(sizeof(Employee));//用指针Q申请新结点
	i++;
	q->id = i;
	printf("请输入员工姓名：\n");
	scanf("%s", q->name);
	printf("请输入员工年龄：\n");
	scanf("%d", &q->age);
	printf("请输入员工性别：\n");
	scanf("%s", q->sex);
	printf("请输入员工部门：\n");
	scanf("%s", q->department);
	printf("请输入员工岗位：\n");
	scanf("%d", &q->post);
	q->workHour = 0;
	if (q->post == 3)
	{
		q->salary = 8000.0;
	}
	else
	{
		q->salary = 0.0;
	}
	q->sales = 0.0;
	q->next = p->next;//Q指针的next域指向P指针的next域，即第i个结点
	p->next = q;
	printf("添加成功！\n");
}
//修改数据
/*
1)根据员工号来修改任意员工的基本信息（姓名、年龄、性别、部门、岗位）。
2)批量计算所有技术员的当月工资额（需填写技术员当月工作时间）。
3)批量计算所有销售员的当月工资额（需填写销售员当月销售额）；然后批量计算所有销售经理的当月工资额。
*/
void UpdataData()
{
	subselect = 1;
	Employee *p, *p1;
	p = head;
	while (subselect)
	{
		printf("——————  修改数据的二级菜单  ——————\n");
		printf("——1. 根据员工号来修改任意员工的基本信息\n");
		printf("——2. 批量计算所有技术员的当月工资额\n");
		printf("——3. 批量计算所有销售员的当月工资额，然后批量计算所有销售经理的当月工资额\n");
		printf("——0. 退出此子菜单\n");
		printf("请输入你的选择：\n");
		scanf("%d", &subselect);
		switch (subselect)
		{
		case 1:
			p = head;
			int ID;
			printf("请输入待修改的员工信息的员工号：\n");
			scanf("%d", &ID);
			while (p->next != NULL)
			{
				p = p->next;
				if (p->id == ID)
				{
					printf("请输入新的员工姓名：\n");
					scanf("%s", p->name);
					printf("请输入新的员工年龄：\n");
					scanf("%d", &p->age);
					printf("请输入新的员工性别：\n");
					scanf("%s", p->sex);
					printf("请输入新的员工部门：\n");
					scanf("%s", p->department);
					printf("请输入新的员工岗位：\n");
					scanf("%d", &p->post);
					printf("信息录入成功！\n");
					break;
				}
			}
			break;
		case 2:
			//批量计算所有技术员的当月工资额，技术员工资：工作时间＊小时工资（100元每小时）
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				if (p->post == 1)
				{
					printf("请填写员工号为%d的技术员当月工作时间：\n", p->id);
					scanf("%d", &p->workHour);
					p->salary = p->workHour * 100;
				}
			}
			break;
		case 3:
			//销售员工资：销售额＊4%提成；
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				if (p->post == 0)
				{
					printf("请填写员工号为%d的销售员当月销售额：\n", p->id);
					scanf("%lf", &p->sales);
					p->salary = p->sales*0.04;
				}
			} 
			//销售经理：底薪（5000）＋所辖部门销售额总额＊0.5%。
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				p1 = head;
				double sum_of_sales = 0.0;
				if (p->post == 2)
				{
				while(p1->next != NULL)
				{
					p1 = p1->next;
				    if (strcmp(p->department, p1->department)==0)
				    {
					   sum_of_sales += p1->sales ;
				    }
				}
				p->salary = sum_of_sales * 0.005 + 5000;
				}
			}
			break;
		case 0:
			break;
		default:
			printf("输入错误！请重新选择。\n");
		}
	}
}
//查询数据
void QueryData()
{
	subselect = 1;
	Employee *p;
	p = head;
	while (subselect)
	{
		printf("——————  查询数据的二级菜单   ——————\n");
		printf("——1. 根据工号或者姓名查询员工信息\n");
		printf("——2. 按部门显示本部门全部员工信息\n");
		printf("——3. 分别显示4种岗位的员工信息\n");
		printf("——4. 分页显示全部员工的信息\n");
		printf("——0. 退出此子菜单\n");
		printf("请输入你的选择：\n");
		scanf("%d", &subselect);
		switch (subselect)
		{
		case 1:
			p = head;
			int ID;
			printf("请输入工号：\n");
			scanf("%d", &ID);
			while (p->next != NULL)
			{
				p = p->next;
				if (p->id == ID)
			{
			printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("数据有误！\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
		    printf("输出完毕！\n");
	        }
	        }
		break;
		case 2:
			char Department[20];
			printf("请输入部门名称：\n");
					scanf("%s", &Department);
			p = head;
			while(p->next != NULL)
				{
					p = p->next;
				    if (strcmp(p->department, Department)==0)
				    {
					   printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("数据有误！\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				    }
				}
				printf("输出完毕！\n");
			
		break;
		case 3:
			printf("SALESMAN:\n");
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				if (p->post==0)
				    {
					   printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("数据有误！\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				    }
			} 
			printf("TECHNICIAN:\n");
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				if (p->post==1)
				    {
					   printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("数据有误！\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				    }
			} 
			printf("SALESMANAGER:\n");
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				if (p->post==2)
				    {
					   printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("数据有误！\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				    }
			} 
			printf("MANAGER:\n");
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				if (p->post==3)
				    {
					   printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("数据有误！\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				    }
			} 
			printf("输出完毕！\n");
		break;
		case 4:
			printf("分页功能略难（没学过），暂时留空吧\n");
		break;
		case 0:
		break;
		default:
		printf("输入错误！请重新选择。\n");
		}
    }
	
}
//删除数据
void DeleteData(){
	Employee *p, *s;
	p = head;
	printf("请输入要删除员工信息的员工号：\n");
	scanf("%d", &i);
	while (p->next != NULL)
	{
		s = p;
		p = p->next;
		if(p->id==i) break;	
	}
	s->next = s->next->next;
	free(p);
}

//按要求排序
void Sorting()
{
	subselect = 1;
	Employee *p, *p1;
	int z = 0;
	int f=0;
	int count = 0;
	double s[20];
	double storeNum;
	p = head;
	while (subselect)
	{
		printf("——————  排序数据的二级菜单   ——————\n");
		printf("——1. 所有员工信息按当月工资从高到低并显示\n");
		printf("——2. 某个岗位的员工信息按当月工资从高到低显示\n");
		printf("——0. 退出此子菜单\n");
		printf("请输入你的选择：\n");
		scanf("%d", &subselect);
		switch (subselect)
		{
		case 1:
			p = head;
			z = 0; 
			while (p->next != NULL)
			{
				p = p->next;
				s[z] = p->salary;
				z++;
			}
			//冒泡排序 
			for (int i = 0; i < z-1; i++)//因为进行两两比较，10个数最坏的情况就需要进行9趟
	        {
		    for (int j = 0; j < (z-1) - i; j++)//因为每进行一趟就可以排好一个数，所以循环次数-i
		    {
			if (s[j] > s[j+1])//两两比较
			{
				double temp = s[j];
				s[j] = s[j+1];
				s[j+1] = temp;
			}
		    }
	        }
	        z--;
			for (int i = z; i >= 0; i--)
			{
				if(storeNum == s[i])
				{
					continue;
				}
			    p = head;
			    while (p->next != NULL)
			    {
				p = p->next;
			    storeNum = s[i];
				if(p->salary==s[i])
				{
					printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("数据有误！\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				}
			}
		}
		break;	
		case 2:
			int Post;
			z = 0;
			storeNum = 0.0;
			printf("请输入岗位信息：（SALESMAN = 0, TECHNICIAN, SALESMANAGER, MANAGER）\n");
			scanf("%d", &Post);
			p = head;
			while(p->next != NULL)
				{
					p = p->next;
				    if (p->post==Post)
				    {
				    	s[z] = p->salary;
				        z++;
			       }
	        	}
			//冒泡排序 
			for (int i = 0; i < z-1; i++)
	        {
		    for (int j = 0; j < (z-1) - i; j++)//因为每进行一趟就可以排好一个数，所以循环次数-i
		    {
			if (s[j] > s[j+1])//两两比较
			{
				double temp = s[j];
				s[j] = s[j+1];
				s[j+1] = temp;
			}
		    }
	        }
	        z--;
	        for (int i = z; i >= 0; i--)
			{
				if(storeNum == s[i])
				{
					continue;
				}
			    p = head;
			    while (p->next != NULL)
			    {
				p = p->next;
				if(p->salary==s[i]&&p->post==Post)
				{
					storeNum = s[i];
					printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("数据有误！\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				}
			}
	     	}		    	
		break;
		case 0:
		break;
		default:
		printf("输入错误！请重新选择。\n");
	}
    }	
}
//统计数据
void Statistics()
{
	printf("hh\n");
}
//保存链表数据到文件
void Save()
{
	Employee *p;
	p = head;
	i = 0;
	//第一步将链表中的结点信息存入数组中
	while (p->next != NULL)
	{
		p = p->next;
		Employees[i].id = p->id;
		strcpy(Employees[i].name, p->name);
		strcpy(Employees[i].sex, p->sex);
		Employees[i].age = p->age;
		strcpy(Employees[i].department, p->department);
		Employees[i].post = p->post;
		Employees[i].workHour = p->workHour;
		Employees[i].sales = p->sales;//当月月销售额
		Employees[i].salary = p->salary;//月工资
		i++;
	}
	//第二步将数组数据录入文本文件
	if ((fp = fopen("employee.txt", "wb+")) == NULL)
	{
		printf("打开文件出错！\n");
		exit(1);
	}
	p = head;
	i = 0;
	while (p->next != NULL)
	{
		p = p->next;
		if (fwrite(&Employees[i], sizeof(struct Employee), 1, fp) != 1)
		{
			printf("写入文件出错！\n");
		}
		i++;
	}
	fclose(fp);
	printf("成功保存数据到文本文件employee\n");
}
