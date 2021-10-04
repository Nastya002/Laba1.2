#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

const int N{ 2 };
const int NumOfMarks{ 4 };


struct birthday {
	int day;
	int m;
	int year;
};

struct data
{
	std::string name;
	std::string surname;
	birthday b{ 0,0,0 };
	std::string groupName;
	int index{};
	int marks[4]{};
	float aver{};
};

struct student {
	data s;
	student* next{ nullptr };
	student* prev{ nullptr };
};
void RW(std::string fileName, std::string* str);

void RW(std::string fileName, student* head);

void RW(std::string fileName, std::string* str)
{
	std::ofstream outf(fileName, std::ios::app);
	if (outf.is_open())
	{
		outf << *str << std::endl;
		outf.close();
	}
	else std::cout << "RW dat" << std::endl;

}

void RW(std::string fileName, student* head)
{
	student* current = head;
	std::ofstream outf(fileName, std::ios::binary);
	if (outf.is_open())
	{
		while (current)
		{
			///outf << current->surname << '\t' << current->name << '\t' << current->b.day << "\t" << current->b.m << "\t" << current->b.year << std::endl;
			outf.write((char*)&current->s, sizeof(data));
			current = current->next;
		}
		outf.close();
	}
	else std::cout << "RW dat" << std::endl;
}

void RD(std::string fileName);
student* RD(std::string fileName, birthday bb);

void RD(std::string fileName)
{
	std::ifstream inf{ fileName }; // зчитується текстовий файл
	if (inf.is_open())
	{
		while (!inf.eof()) // зчитається чи не закінчився файл
		{
			std::string str;
			std::getline(inf, str); //файл читається по строках 
			std::cout << str << std::endl;
		}
		inf.close();
	}
	else std::cout << "RD txt" << std::endl;

}

student* RD()
{
	student* temp_head{ new student };
	student* head{}, * current{};
	student* temp_current = temp_head;
	std::ifstream inf{ "info.dat" };
	student* tmp{};
	data temp{};
	int numOfStuds{};
	float* arr{};
	if (inf.is_open())
	{
		while (!inf.eof())
		{

			inf.read((char*)&temp, sizeof(data));
			temp_current->s = temp;
			for (int i{}; i < NumOfMarks; i++)
			{
				temp_current->s.aver += temp_current->s.marks[i]; // розрахунок середнього бала
			}
			temp_current->s.aver /= NumOfMarks;
			if (!inf.eof())
			{
				temp_current->next = new student;
				student* temp = temp_current;
				temp_current = temp_current->next;
				temp_current->prev = temp;
			}
			numOfStuds++;
		}
		tmp = temp_current;
		temp_current = tmp->prev;
		temp_current->next = nullptr;
		delete tmp;
		numOfStuds--;
		temp_current = temp_head;
		arr = new float[numOfStuds];
		for (int i{}; i < numOfStuds; i++)
		{
			arr[i] = temp_current->s.aver;
			temp_current = temp_current->next;
		}
		std::sort(arr, arr + numOfStuds);
		temp_current = temp_head;
		head = new student;
		current = head;
		for (int i{ numOfStuds - 1 }; i >= 0; i--)
		{
			temp_current = temp_head;
			while (temp_current)
			{
				if (arr[i] == temp_current->s.aver)
				{
					data temp{ temp_current->s };
					current->s = temp;
					if (i != 0)
					{
						student* tmp{ current };
						current->next = new student;
						current = current->next;
						current->prev = tmp;
					}
					break;
				}
				else
				{
					temp_current = temp_current->next;
				}
			}
		}
		return head;
	}
	else std::cout << "RW txt" << std::endl;

}



int main()
{
	student* stud{ new student };
	student* head = stud;
	student* current = head;
	if (stud)
	{
		for (int i{ 0 }; i < N; i++)
		{
			std::cout << "Enter name: ";
			std::cin >> current->s.name;
			std::cout << "Enter surname: ";
			std::cin >> current->s.surname;
			std::cout << "Enter birth year: ";
			std::cin >> current->s.b.year;
			std::cout << "Enter birth month: ";
			std::cin >> current->s.b.m;
			std::cout << "Enter birth day: ";
			std::cin >> current->s.b.day;
			std::cout << "Enter name of group: ";
			std::cin >> current->s.groupName;
			std::cout << "Enter marks: ";
			current->s.index = i;
			for (int i{}; i < 4; i++) std::cin >> current->s.marks[i];
			if (i != N - 1)
			{
				student* temp = current;
				current->next = new student;
				current = current->next;
				current->prev = temp;
			}
			//std::cout << stud->surname << '\t' << stud->name << '\t' << stud->b.day << "." << stud->b.m << "." << stud->b.year << std::endl;
		}
	}
	current = head;
	while (current)
	{
		std::cout << current->s.surname << '\t' << current->s.name << '\t' << current->s.b.day << "." << current->s.b.m << "." << current->s.b.year << std::endl;
		for (int i{}; i < NumOfMarks; i++) std::cout << current->s.marks[i] << '\t';
		std::cout << std::endl;
		current = current->next;

	}
	//std::cout << head->surname << '\t' << head->name << '\t' << head->b.day << "." << head->b.m << "." << head->b.year << std::endl;
	std::string str{};
	std::stringstream strss{};
	current = head;
	while (current)
	{
		strss << current->s.name << '\t' << current->s.surname << '\t' << current->s.b.day << "." << current->s.b.m << "." << current->s.b.year << '\t';
		for (int i{}; i < NumOfMarks; i++) strss << current->s.marks[i] << '\t';
		strss << std::endl;
		std::getline(strss, str);
		RW("info.txt", &str);
		strss.clear();
		current = current->next;
	}

	RD("info.txt");
	RW("info.dat", head);
	head = NULL;
	head = RD();
	current = head;
	while (current)
	{
		std::cout << current->s.surname << '\t' << current->s.name << '\t' << current->s.b.day << "." << current->s.b.m << "." << current->s.b.year << std::endl;
		std::cout << "Average mark: " << current->s.aver << std::endl;;
		current = current->next;
	}
	return 0;
}