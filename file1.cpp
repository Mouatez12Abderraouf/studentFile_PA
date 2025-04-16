
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct student{
	string firstName, lastName;
	short group;
	float avrage;
};

void fillStudentFile(student st, string nameFile, short i);

bool isEnterPressed()
{
	string input;
	getline(cin, input);
	return input.empty();
}

void resetScreen()
{
	system("cls");
}

void printMenu()
{
	cout << "(1) insert new student.\n";
	cout << "(2) delete student.\n";
	cout << "(3) search for a student, and print their information.\n";
	cout << "(4) save a list of student in file.\n";
	cout << "(5) exit.\n";

}

short readPositiveNumber()
{
	short nb;
	
	do
	{
		cin >> nb;
	} while (nb <= 0);

	return nb;
}

short searchForStudent(student st[], string fName, string lName, short length)
{
	for (short i = 0; i < length; i++)
	{
		if (st[i].firstName == fName && st[i].lastName == lName)
		{
			return i;
		}
	}
	return -1;
}

void printInfo(student st[], short index)
{

	cout << "first name: " << st[index].firstName << endl;
	cout << "last name: " << st[index].lastName << endl;
	cout << "group: " << st[index].group << endl;
	cout << "avrage: " << st[index].avrage << endl;

}

student* deleteStudent(student st[], short &length)
{
	string firstName, lastName;
	short index;

	cout << "Enter the first name of student: \n";
	cin.ignore();
	getline(cin, firstName);

	cout << "Enter the last name of student: \n";
	getline(cin, lastName);

	index = searchForStudent(st, firstName, lastName, length);

	for (int i = index; i < length - 1; i++)
	{
		st[i] = st[i + 1];
	}

	length -= 1;

	return st;

}

void readInfo(student & st)
{
	cout << "Enter the first name of student: \n";
	cin.ignore();
	getline(cin , st.firstName);

	cout << "Enter the last name of student: \n";
	getline(cin, st.lastName);

	cout << "Enter the group of student: ";
	cin >> st.group;

	cout << "Enter the avrage of student: ";
	cin >> st.avrage;

}

//void createListOfstudent(student st[], short length)
//{
//	for (int i = 0; i < length; i++)
//	{
//		readInfo(st[i]);
//		
//	}
//}

//void printListOfStudent(student st[], short length)
//{
//	for (int i = 0; i < length; i++)
//	{
//		cout << "\n\n-----------------Student " << i + 1 << "-----------------\n\n";
//
//		printInfo(st[i], length);
//
//	}
//}

void fillStudentFile(student st, string nameFile, short i)
{
	fstream myFile(nameFile, ios::out | ios::app);

	if (myFile.is_open())
	{
		myFile << "\n\n-----------------Student " << i + 1 << "-----------------\n\n";

		myFile << "first name: " << st.firstName << endl;
		myFile << "last name: " << st.lastName << endl;
		myFile << "group: " << st.group << endl;
		myFile << "avrage: " << st.avrage << endl;

	}
}

void fillListStudentFile(student st[], string nameFile, short length)
{
	


	for (int i = 0; i < length; i++)
	{
		fillStudentFile(st[i], nameFile, i);
	}
}

void copyArray(student orStudent[], student cpStudent[], short length)
{
	for (int i = 0; i < length; i++)
	{
		cpStudent[i].firstName = orStudent[i].firstName;
		cpStudent[i].lastName = orStudent[i].lastName;
		cpStudent[i].group = orStudent[i].group;
		cpStudent[i].avrage = orStudent[i].avrage;
	}

	readInfo(cpStudent[length]);

}
	
student* addStudent(student st[], short &length)
{
	student* ptr1 = new student[length + 1];

	copyArray(st, ptr1, length);
	length++;

	return ptr1;
}

void printFile(string file, vector<string> &v)
{
	fstream myFile;
	myFile.open(file, ios::in);

	string line;

	if (myFile.is_open())
	{
		while (getline(myFile, line))
		{
			//cout << line << endl;
			v.push_back(line);
		}

		myFile.close();
	}
}

char readValidationChar()
{
	char ch;
	do
	{
		cin >> ch;
	} while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N');

	return ch;
}

int main()
{
	string fName, lName, nameFile;
	bool off_on = false;
	short choice;
	student* ptr = new student[1];
	char check, input;
	short numberStudent = 0;

	cout << "--------------------------------------------\n";
	cout << "|       Welcome, Student Coordinator       |\n";
	cout << "--------------------------------------------\n\n\n\n";
	cout << "               press enter\n";

	begin1:

	if (!isEnterPressed())
	{
		goto begin1;
	}


	while (off_on == false)
	{
		begin2:

		resetScreen();

		cout << "enter your choice: \n";

		printMenu();

		choice = readPositiveNumber();


		switch (choice)
		{

		case 1:
			ptr = addStudent(ptr, numberStudent);
			cout << "Addition process successful.\n";
			break;

		case 2:
			ptr = deleteStudent(ptr, numberStudent);
			cout << "deletion process successful.\n";
			break;

		case 3:
			begin3:
			cout << "Enter the first name of student: \n";
			cin.ignore();
			getline(cin, fName);

			cout << "Enter the last name of student: \n";
			getline(cin, lName);

			choice = searchForStudent(ptr, fName, lName, numberStudent);
			if (choice != -1)
			{
				cout << "information of student is:\n";
				printInfo(ptr, choice);
				cout << "\n\n\npress enter if you want to go to menu.\n";

			begin4:
				if (!isEnterPressed())
				{
					goto begin4;
				}
			}
			else
			{
				cout << "the student not existe.\n";
				cout << "Do you try agine [y/n]:";
				input = readValidationChar();

				if (input == 'Y' || input == 'y')
				{
					goto begin3;
				}
				
			}
			break;

		case 4:
			if (numberStudent == 0)
			{
				cout << "the list of student is empty.\n";
			}
			else
			{
				cout << "enter the name of file:\n";
				cin >> nameFile;
				fillListStudentFile(ptr, nameFile, numberStudent);
				cout << "the file is done.\n";
			}
			break;
			
		case 5:
			off_on = true;
			break;

		default:
			cout << "your choice is not exist.";
			goto begin2;
			break;
		}
	}

	delete ptr;


	

	/*cout << "Enter the number of student : ";
	cin >> numberStudent;

	ptr = new student[numberStudent];

	createListOfstudent(ptr, numberStudent);

	do {

		cout << "do you want to add student? [y/n]? : ";
		cin >> check;
	
		if(check == 'y' || check == 'Y')
			ptr = addStudent(ptr, numberStudent);
	
	} while (check == 'y' || check == 'Y');
	vector <string> vec;
	printFile("myFile.txt" , vec);

	for (string &i : vec)
	{
		cout << i << endl;
	}*/

}
