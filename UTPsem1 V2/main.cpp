#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <iomanip> 

using namespace std;

const int MaxCountOfStudents{ 70 }, MaxCountOfSymbols{ 20 };

enum CommandsOfMenu {
	KeyboardInput = 1,
	InputFromTextFile = 2,
	InputFromBinary = 3,
	DisplayDatabase = 4,
	OutputDataToFile = 5,
	Request = 6,
	ConvertToTextFile = 7,
	ConvertToBinaryFile = 8,
	AddANote = 9,
	ChangeANote = 10,
	DeleteANote = 11,
	SortDatabase = 12,
	Exit = 0
};

enum CommandsOfSort {
	SortByName = 1,
	SortBySurname = 2,
	SortByYearOfAdmission = 3, 
	SortByYearOfBirth = 4,
	SortByCourse = 5,
	SortByGroup = 6
};

enum DataTypeToSort {
	Int = 1, 
	Char = 2
};

enum SortingType {
	Ascending = 1,
	Descending = 2
};

struct Student {
	char name[MaxCountOfSymbols]{};
	char surname[MaxCountOfSymbols]{};
	int yearOfAdmission{};
	int yearOfBirth{};
	int course{};
	char group[MaxCountOfSymbols]{};
};

int correctDataTypeIntInput(int minNumber, int maxNumber);
void correctDataTypeCharInput(char returnValue[], unsigned int maxCountOfSymbols);

void displayMainMenuItems();

int inputCountOfStudents();
void keyboardInput(int ņountOfStudents, int maxCountOfSymbols, Student students[]);
void inputFromTextFile(int maxCountOfSymbols, int &countOfStudents, Student students[]);
void inputFromBinary(int& countOfStudents, Student students[]);
void displayDatabase(int countOfStudents, Student students[]);
void outputDataToFile(int countOfStudents, Student students[]);
void request(int countOfStudents, Student students[]);
void convertToTextFile(int countOfStudents, Student students[]);
void convertToBinaryFile(int maxCountOfSymbols);
void addANote(int &countOfStudents, int maxCountOfSymbols, Student students[]);
void changeANote(int &countOfStudents, int maxCountOfSymbols, Student students[]);
void deleteANote(int &countOfStudents, Student students[]);

void sortDatabase(int maxCountOfSymbols, int countOfStudents, Student students[]);
void displaySortMenuItems();
int findOutTheSortingType();
void sorting(int maxCountOfSymbols, int countOfStudents, int valueSortingType, int* sortingŅharacteristics, Student students[]);
void sorting(int maxCountOfSymbols, int countOfStudents, int valueSortingType, char** sortingŅharacteristics, Student students[]);

void strCopy(char* dynamicSymbolsArray, char* staticSymbolsArray);
void swapInt(int& number1, int& number2);
void swapStudents(Student& student1, Student& student2);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color B");

	int countOfStudents{}, itemNumber{ -1 };
	int* pointerCountOfStudents = &countOfStudents;
	Student students[MaxCountOfStudents]{};


	while (itemNumber != 0) {
		displayMainMenuItems();

		itemNumber = correctDataTypeIntInput(0, 12);
		system("cls");

		switch (itemNumber) {
		case Exit:
			break;
		case KeyboardInput:
			countOfStudents = inputCountOfStudents();
			system("cls");
			keyboardInput(countOfStudents, MaxCountOfSymbols, students);
			break;
		case InputFromTextFile:
			inputFromTextFile(MaxCountOfSymbols, countOfStudents, students);
			break;
		case InputFromBinary:
			inputFromBinary(countOfStudents, students);
			break;
		case DisplayDatabase:
			displayDatabase(countOfStudents, students);
			break;
		case OutputDataToFile:
			outputDataToFile(countOfStudents, students);
			break;
		case Request:
			request(countOfStudents, students);
			break;
		case ConvertToTextFile:
			convertToTextFile(countOfStudents, students);
			break;
		case ConvertToBinaryFile:
			convertToBinaryFile(MaxCountOfStudents);
			break;
		case AddANote:
			addANote(countOfStudents, MaxCountOfSymbols, students);
			break;
		case ChangeANote:
			changeANote(countOfStudents, MaxCountOfSymbols, students);
			break;
		case DeleteANote:
			deleteANote(countOfStudents, students);
			break;
		case SortDatabase:
			sortDatabase(MaxCountOfSymbols, countOfStudents, students);
			break;
		}

		system("pause");
		system("cls");
	}

	return 0;
}

int correctDataTypeIntInput(int minNumber, int maxNumber) {
	int number{};
	bool correctNumberFound{ false };
	cin >> number;

	while (!(correctNumberFound)) {
		if (!((number >= minNumber) && (number <= maxNumber))) {
			cout << "\nÂâåäåííîå âāėč ũčņëî íåęîððåęōíî, ââåäčōå ũčņëî â äčāïāįîíå îō " << minNumber << " äî " << maxNumber << " âęëþũčōåëüíî: ";
			cin >> number;
		} else {
			correctNumberFound = true;
		}
	}
	
	cin.ignore(1, '\n');
	return number;
}

void correctDataTypeCharInput(char returnValue[], unsigned int maxCountOfSymbols) {
	const int TheMaximumNumberOfSymbols{ 1000 };
	char* value = new char [TheMaximumNumberOfSymbols] {};
	bool correctValueFound{ false };
	cin.getline(value, TheMaximumNumberOfSymbols);

	while (!(correctValueFound)) {
		if ((strlen(value) < maxCountOfSymbols) && strcmp(value, "")) {
			strCopy(returnValue, value);
			correctValueFound = true;
		} else {
			cout << "\nÂâåäåííîå âāėč įíāũåíčå íåęîððåęōíî čëč ïîëå îņōāâëåííî ïóņōûė, ââåäčōå įíāũåíčå,\níå ïðåâûøāþųåå ęîëčũåņōâî ņčėâîëîâ, ðāâíîå " << maxCountOfSymbols << ": ";
			cin.getline(value, TheMaximumNumberOfSymbols);
		}
	}

	delete[] value;
}

void displayMainMenuItems() {
	cout << "Ðāáîōā ņî ņïčņęîė óũåáíîé ãðóïïû:\n\n";

	cout << " 1) Ââåņōč číôîðėāöčþ ņ ęëāâčāōóðû.\n";
	cout << " 2) Ââåņōč číôîðėāöčþ čį óæå ņîįäāííîãî ōåęņōîâîãî ôāéëā.\n";
	cout << " 3) Ââåņōč číôîðėāöčþ čį óæå ņîįäāííîãî áčíāðíîãî ôāéëā.\n";
	cout << " 4) Âûâåņōč äāííûå íā ýęðāí\n";
	cout << " 5) Âûâåņōč äāííûå â ôāéë.\n";
	cout << " 6) Âûâåņōč ðāņïåũāōęó číôîðėāöčč äāííûõ ïî įāïðîņó.\n";
	cout << " 7) Ïåðåâåņōč áāįó äāííûõ â ōåęņōîâûé ôāéë.\n";
	cout << " 8) Ïåðåâåņōč ņîäåðæčėîå ōåęņōîâîãî ôāéëā â áčíāðíûé ôāéë.\n";
	cout << " 9) Äîáāâčōü įāïčņü.\n";
	cout << "10) Čįėåíčōü įāïčņü.\n";
	cout << "11) Óäāëčōü įāïčņü.\n";
	cout << "12) Ņîðōčðîâāōü áāįó äāííûõ.\n";
	cout << " 0) Âûõîä.\n\n";

	cout << "Ââåäčōå íîėåð ïóíęōā: ";
}

int inputCountOfStudents() {
	int countOfStudents{};

	cout << "Ėāęņčėāëüíîå ęîëčũåņōâî ņōóäåíōîâ â áâįå äāííûõ - " << MaxCountOfStudents << ".\nČíôîðėāöčþ î ęāęîė ęîëčũåņōâå ņōóäåíōîâ âû õîōčōå ââåņōč ? \nĘîëčũåņōâî ņōóäåíōîâ : ";
	countOfStudents = correctDataTypeIntInput(1, 70);

	return countOfStudents;
}

void keyboardInput(int countOfStudents, int maxCountOfSymbols, Student students[]) {
	for (int i = 0; i < countOfStudents; i++) {
		cout << "Ââåäčōå číôîðėāöčþ î ņōóäåíōāõ, ęîëčũåņōâî ęîōîðûõ ðāâíî " << countOfStudents << "\n\n";
		cout << "Čėĸ ņōóäåíōā íîėåð " << i + 1 << ": ";
		correctDataTypeCharInput(students[i].name, maxCountOfSymbols);
		cout << "Ôāėčëčĸ ņōóäåíōā íîėåð " << i + 1 << ": ";
		correctDataTypeCharInput(students[i].surname, maxCountOfSymbols);
		cout << "Ãîä ïîņōóïëåíčĸ ņōóäåíōā íîėåð " << i + 1 << ": ";
		students[i].yearOfAdmission = correctDataTypeIntInput(2014, 2021);
		cout << "Ãîä ðîæäåíčĸ ņōóäåíōā íîėåð " << i + 1 << ": ";
		students[i].yearOfBirth = correctDataTypeIntInput(1901, 2013);
		cout << "Ęóðņ ņōóäåíōā íîėåð " << i + 1 << ": ";
		students[i].course = correctDataTypeIntInput(1, 6);
		cout << "Ãðóïïā ņōóäåíōā íîėåð " << i + 1 << ": ";
		correctDataTypeCharInput(students[i].group, maxCountOfSymbols);

		system("cls");
	}
}

void inputFromTextFile(int maxCountOfSymbols, int &countOfStudents, Student students[]) {
	ifstream fin;
	fin.open("database.txt");

	if (fin.is_open()) {
		fin >> countOfStudents;
		fin.ignore(1, '\n');
		for (int i = 0; i < countOfStudents; i++) {
			fin.getline(students[i].name, maxCountOfSymbols);
			fin.getline(students[i].surname, maxCountOfSymbols);
			fin >> students[i].yearOfAdmission;
			fin >> students[i].yearOfBirth;
			fin >> students[i].course;
			fin.ignore(1, '\n');
			fin.getline(students[i].group, maxCountOfSymbols);
		}
	} else {
		system("cls");
		cout << "Îøčáęā îōęðûōčĸ ôāéëā.";
		system("pause");
	}

	fin.close();
}

void inputFromBinary(int& countOfStudents, Student students[]){
	ifstream fin;
	fin.open("database.bin", ios::binary);

	if (fin.is_open()) {
		fin.read((char*)&countOfStudents, sizeof(countOfStudents));

		for (int i = 0; i < countOfStudents; i++) {
			fin.read((char*)&students[i], sizeof(students[i]));
		}
	} else {
		system("cls");
		cout << "Îøčáęā îōęðûōčĸ ôāéëā.";
		system("pause");
	}

	fin.close();
}

void displayDatabase(int countOfStudents, Student students[]){
	const char headerTable[7][16]{ "   ", "Čėĸ", "Ôāėčëčĸ", "Ãîä ïîņōóïëåíčĸ", "Ãîä ðîæäåíčĸ", "Ęóðņ", "Ãðóïïā" };

	cout << headerTable[0];
	cout << left << setw(16) << headerTable[1];
	cout << left << setw(20) << headerTable[2];
	cout << left << setw(19) << headerTable[3];
	cout << left << setw(16) << headerTable[4];
	cout << left << setw(8) << headerTable[5];
	cout << left << setw(10) << headerTable[6];
	cout << "\n";

	for (int i = 0; i < countOfStudents; i++) {
		cout << left << setw(3) << i + 1;
		cout << left << setw(16) << students[i].name;
		cout << left << setw(20) << students[i].surname;
		cout << left << setw(19) << students[i].yearOfAdmission;
		cout << left << setw(16) << students[i].yearOfBirth;
		cout << left << setw(8) << students[i].course;
		cout << left << setw(8) << students[i].group;

		cout << "\n";
	}
	cout << "\n";
}

void outputDataToFile(int countOfStudents, Student students[]){
	ofstream  fout;
	const char headerTable[7][16]{ "   ", "Čėĸ", "Ôāėčëčĸ", "Ãîä ïîņōóïëåíčĸ", "Ãîä ðîæäåíčĸ", "Ęóðņ", "Ãðóïïā" };
	const int MaxCountOfSymbolsInFileAddress{ 200 };
	char fileAddress[MaxCountOfSymbolsInFileAddress]{};

	cout << "Ââåäčōå āäðåņ ōåęņōîâîãî ôāéëā (ïðčėåð: D:\\Users\\example\\example.txt):\n";
	cin.getline(fileAddress, MaxCountOfSymbolsInFileAddress);

	fout.open(fileAddress);

	if (fout.is_open()) {
		fout << headerTable[0];
		fout << left << setw(16) << headerTable[1];
		fout << left << setw(20) << headerTable[2];
		fout << left << setw(19) << headerTable[3];
		fout << left << setw(16) << headerTable[4];
		fout << left << setw(8) << headerTable[5];
		fout << left << setw(10) << headerTable[6];
		fout << "\n";

		for (int i = 0; i < countOfStudents; i++) {
			fout << left << setw(3) << i + 1;
			fout << left << setw(16) << students[i].name;
			fout << left << setw(20) << students[i].surname;
			fout << left << setw(19) << students[i].yearOfAdmission;
			fout << left << setw(16) << students[i].yearOfBirth;
			fout << left << setw(8) << students[i].course;
			fout << left << setw(8) << students[i].group;

			fout << "\n";
		}
		fout << "\n";
	} else {
		system("cls");
		cout << "Îøčáęā îōęðûōčĸ ôāéëā.";
		system("pause");
	}

	fout.close();
}

void request(int countOfStudents, Student students[]){
	const char headerTable[7][8]{ "   ", "Ôāėčëčĸ", "Ãðóïïā" };
	
	int* serialNumbers = new int [countOfStudents] {};
	int* yearsOfBirth = new int [countOfStudents] {};

	for (int i = 0; i < countOfStudents; i++) {
		serialNumbers[i] = i;
		yearsOfBirth[i] = students[i].yearOfBirth;
	}

	for (int i = 1; i < countOfStudents - 1; i++) {
		for (int j = 0; j < countOfStudents - i; j++) {
			if (yearsOfBirth[j] > yearsOfBirth[j + 1]) {
				swapInt(serialNumbers[j], serialNumbers[j + 1]);
				swapInt(yearsOfBirth[j], yearsOfBirth[j + 1]);
			}
		}
	}

	cout << headerTable[0];
	cout << left << setw(20) << headerTable[1];
	cout << left << setw(10) << headerTable[2];
	cout << "\n";

	cout << left << setw(3) << serialNumbers[countOfStudents - 1] + 1;
	cout << left << setw(20) << students[serialNumbers[countOfStudents - 1]].surname;
	cout << left << setw(8) << students[serialNumbers[countOfStudents - 1]].group;
	cout << "\n";

	cout << left << setw(3) << serialNumbers[countOfStudents - 2] + 1;
	cout << left << setw(20) << students[serialNumbers[countOfStudents - 2]].surname;
	cout << left << setw(8) << students[serialNumbers[countOfStudents - 2]].group;
	cout << "\n";

	delete[] serialNumbers;
	delete[] yearsOfBirth;
}

void convertToTextFile(int countOfStudents, Student students[]){
	ofstream fout;
	fout.open("database.txt");

	if (fout.is_open()) {
		fout << countOfStudents << '\n';
		for (int i = 0; i < countOfStudents; i++) {
			fout << students[i].name << '\n';
			fout << students[i].surname << '\n';
			fout << students[i].yearOfAdmission << '\n';
			fout << students[i].yearOfBirth << '\n';
			fout << students[i].course << '\n';
			fout << students[i].group << '\n';
		}
	} else {
		system("cls");
		cout << "Îøčáęā îōęðûōčĸ ôāéëā.";
		system("pause");
	}

	fout.close();
}

void convertToBinaryFile(int maxCountOfSymbols){
	Student tempStudent{};
	int countOfStudents{};

	ifstream fin;
	ofstream fout;
	fin.open("database.txt");
	fout.open("database.bin", ios::binary);

	if (fin.is_open() && fout.is_open()) {
		fin >> countOfStudents;
		fout.write((char*)&countOfStudents, sizeof(countOfStudents));
		fin.ignore(1, '\n');

		for (int i = 0; i < countOfStudents; i++) {
			fin.getline(tempStudent.name, maxCountOfSymbols);
			fin.getline(tempStudent.surname, maxCountOfSymbols);
			fin >> tempStudent.yearOfAdmission;
			fin >> tempStudent.yearOfBirth;
			fin >> tempStudent.course;
			fin.ignore(1, '\n');
			fin.getline(tempStudent.group, maxCountOfSymbols);

			fout.write((char*)&tempStudent, sizeof(tempStudent));
		}
	} else {
		system("cls");
		cout << "Îøčáęā îōęðûōčĸ ôāéëā.";
		system("pause");
	}

	fin.close();
	fout.close();
}

void addANote(int &countOfStudents, int maxCountOfSymbols, Student students[]){
	cout << "Ââåäčōå číôîðėāöčþ î ņōóäåíōāõ, ęîëčũåņōâî ęîōîðûõ ðāâíî " << countOfStudents + 1 << "\n\n";
	cout << "Čėĸ ņōóäåíōā íîėåð " << countOfStudents + 1 << ": ";
	correctDataTypeCharInput(students[countOfStudents].name, maxCountOfSymbols);
	cout << "Ôāėčëčĸ ņōóäåíōā íîėåð " << countOfStudents + 1 << ": ";
	correctDataTypeCharInput(students[countOfStudents].surname, maxCountOfSymbols);
	cout << "Ãîä ïîņōóïëåíčĸ ņōóäåíōā íîėåð " << countOfStudents + 1 << ": ";
	students[countOfStudents].yearOfAdmission = correctDataTypeIntInput(2014, 2021);
	cout << "Ãîä ðîæäåíčĸ ņōóäåíōā íîėåð " << countOfStudents + 1 << ": ";
	students[countOfStudents].yearOfBirth = correctDataTypeIntInput(1901, 2013);
	cout << "Ęóðņ ņōóäåíōā íîėåð " << countOfStudents + 1 << ": ";
	students[countOfStudents].course = correctDataTypeIntInput(1, 6);
	cout << "Ãðóïïā ņōóäåíōā íîėåð " << countOfStudents + 1 << ": ";
	correctDataTypeCharInput(students[countOfStudents].group, maxCountOfSymbols);

	countOfStudents++;

	system("cls");
}

void changeANote(int &countOfStudents, int maxCountOfSymbols, Student students[]){
	int indexOfItemBeingModified{};

	cout << "Ââåäčōå íîėåð ņōóäåíōā: ";
	indexOfItemBeingModified = correctDataTypeIntInput(1, countOfStudents);
	indexOfItemBeingModified--;

	cout << "Ââåäčōå îáíîâëåííóþ číôîðėāöčþ î ņōóäåíōå\n\n";
	cout << "Čėĸ ņōóäåíōā: ";
	correctDataTypeCharInput(students[indexOfItemBeingModified].name, maxCountOfSymbols);
	cout << "Ôāėčëčĸ ņōóäåíōā: ";
	correctDataTypeCharInput(students[indexOfItemBeingModified].surname, maxCountOfSymbols);
	cout << "Ãîä ïîņōóïëåíčĸ ņōóäåíōā: ";
	students[indexOfItemBeingModified].yearOfAdmission = correctDataTypeIntInput(2014, 2021); 
	cout << "Ãîä ðîæäåíčĸ ņōóäåíōā: ";
	students[indexOfItemBeingModified].yearOfBirth = correctDataTypeIntInput(1901, 2013);
	cout << "Ęóðņ ņōóäåíōā: ";
	students[indexOfItemBeingModified].course = correctDataTypeIntInput(1, 6);
	cout << "Ãðóïïā ņōóäåíōā: ";
	correctDataTypeCharInput(students[indexOfItemBeingModified].group, maxCountOfSymbols);

	system("cls");
}

void deleteANote(int &countOfStudents, Student students[]){
	int indexOfItemToRemove{};

	cout << "Ââåäčōå íîėåð ņōóäåíōā: ";
	indexOfItemToRemove = correctDataTypeIntInput(1, countOfStudents);
	indexOfItemToRemove--;

	for (int i = indexOfItemToRemove; i < countOfStudents - 1; i++) {
		strcpy_s(students[i].name, students[i + 1].name);
		strcpy_s(students[i].surname, students[i + 1].surname);
		students[i].yearOfAdmission = students[i + 1].yearOfAdmission;
		students[i].yearOfBirth = students[i + 1].yearOfBirth;
		students[i].course = students[i + 1].course;
		strcpy_s(students[i].group, students[i + 1].group);
	}

	strcpy_s(students[countOfStudents - 1].name, "");
	strcpy_s(students[countOfStudents - 1].surname, "");
	students[countOfStudents - 1].yearOfAdmission = 0;
	students[countOfStudents - 1].yearOfBirth = 0;
	students[countOfStudents - 1].course = 0;
	strcpy_s(students[countOfStudents - 1].group, "");

	countOfStudents--;

	system("cls");
}

void sortDatabase(int maxCountOfSymbols, int countOfStudents, Student students[]){ 
	int itemNumber{ -1 }, valueSortingType{}, dataTypeToSort{};
	int* sortingŅharacteristicsInt = new int[countOfStudents]{};
	char** sortingŅharacteristicsChar = new char* [countOfStudents]{nullptr};
	for (int i = 0; i < countOfStudents; i++) {
		sortingŅharacteristicsChar[i] = new char[maxCountOfSymbols];
	}

	displaySortMenuItems();
	itemNumber = correctDataTypeIntInput(1, 6);
	system("cls");

	valueSortingType = findOutTheSortingType(); 

	switch (itemNumber) {								
	case SortByName:		
		for (int i = 0; i < countOfStudents; i++) {
			sortingŅharacteristicsChar[i] = students[i].name;
		}
		dataTypeToSort = Char;
		break;
	case SortBySurname:
		for (int i = 0; i < countOfStudents; i++) {
			sortingŅharacteristicsChar[i] = students[i].surname;
		}
		dataTypeToSort = Char;
		break;
	case SortByYearOfAdmission:
		for (int i = 0; i < countOfStudents; i++) {
			sortingŅharacteristicsInt[i] = students[i].yearOfAdmission;
		}
		dataTypeToSort = Int;
		break;
	case SortByYearOfBirth:
		for (int i = 0; i < countOfStudents; i++) {
			sortingŅharacteristicsInt[i] = students[i].yearOfBirth;
		}
		dataTypeToSort = Int;
		break;
	case SortByCourse:
		for (int i = 0; i < countOfStudents; i++) {
			sortingŅharacteristicsInt[i] = students[i].course;
		}
		dataTypeToSort = Int;
		break;
	case SortByGroup:
		for (int i = 0; i < countOfStudents; i++) {
			sortingŅharacteristicsChar[i] = students[i].group;
		}
		dataTypeToSort = Char;
		break;
	}

	if (dataTypeToSort == Int) {
		sorting(maxCountOfSymbols, countOfStudents, valueSortingType, sortingŅharacteristicsInt, students);
	} else if (dataTypeToSort == Char) {
		sorting(maxCountOfSymbols, countOfStudents, valueSortingType, sortingŅharacteristicsChar, students);
	}

	delete[] sortingŅharacteristicsInt;
	delete[] sortingŅharacteristicsChar;
}

void displaySortMenuItems() {
	cout << "1) Ņîðōčðîâāōü ïî čėåíč.\n";
	cout << "2) Ņîðōčðîâāōü ïî ôāėčëčč.\n";
	cout << "3) Ņîðōčðîâāōü ïî ãîäó ïîņōóïëåíčĸ.\n";
	cout << "4) Ņîðōčðîâāōü ïî ãîäó ðîæäåíčĸ.\n";
	cout << "5) Ņîðōčðîâāōü ïî íîėåðó ęóðņā.\n";
	cout << "6) Ņîðōčðîâāōü ïî ãðóïïå ņōóäåíōā.\n\n";

	cout << "Ââåäčōå íîėåð ïóíęōā: ";
}

int findOutTheSortingType(){
	int itemNumber{};

	cout << "1) Ņîðōčðîâāōü ïî âîįðāņōāíčþ.\n";
	cout << "2) Ņîðōčðîâāōü ïî óáûâāíčþ.\n\n";

	cout << "Ââåäčōå íîėåð ïóíęōā: ";
	itemNumber = correctDataTypeIntInput(1, 2);
	system("cls");

	return itemNumber;
}

void sorting(int maxCountOfSymbols, int countOfStudents, int valueSortingType, int* sortingŅharacteristics, Student students[]) {
	if (valueSortingType == Ascending) {
		for (int i = 1; i < countOfStudents; i++) {
			for (int j = 0; j < countOfStudents - i; j++) {
				if (sortingŅharacteristics[j] > sortingŅharacteristics[j + 1]) {
					swapInt(sortingŅharacteristics[j], sortingŅharacteristics[j + 1]);
					swapStudents(students[j], students[j + 1]);
				}
			}
		}
	} else if (valueSortingType == Descending) {
		for (int i = 1; i < countOfStudents; i++) {
			for (int j = 0; j < countOfStudents - i; j++) {
				if (sortingŅharacteristics[j] < sortingŅharacteristics[j + 1]) {
					swapInt(sortingŅharacteristics[j], sortingŅharacteristics[j + 1]);
					swapStudents(students[j], students[j + 1]);
				}
			}
		}
	}
}

void sorting(int maxCountOfSymbols, int countOfStudents, int valueSortingType, char** sortingŅharacteristics, Student students[]) {
	char* tempSortingŅharacteristic = new char [maxCountOfSymbols] {};

	if (valueSortingType == Ascending) {
		for (int i = 1; i < countOfStudents; i++) {
			for (int j = 0; j < countOfStudents - i; j++) {
				if (sortingŅharacteristics[j][0] > sortingŅharacteristics[j + 1][0]) {
					swapStudents(students[j], students[j + 1]);
				}
			}
		}
	} else if (valueSortingType == Descending) {
		for (int i = 1; i < countOfStudents; i++) {
			for (int j = 0; j < countOfStudents - i; j++) {
				if (sortingŅharacteristics[j][0] < sortingŅharacteristics[j + 1][0]) {
					swapStudents(students[j], students[j + 1]);
				}
			}
		}
	}

	delete[] tempSortingŅharacteristic;
}

void strCopy(char* symbolsArray1, char* symbolsArray2) {
	for (unsigned int i = 0; i < strlen(symbolsArray1); i++) {
		symbolsArray1[i] = ' ';
	}

	for (unsigned int i = 0; i < strlen(symbolsArray2); i++) {
		symbolsArray1[i] = symbolsArray2[i];
	}
}

void swapInt(int& number1, int& number2) {
	int tempNumber{};

	tempNumber = number1;
	number1 = number2;
	number2 = tempNumber;
}

void swapStudents(Student& student1, Student& student2) {
	Student tempStudent{};

	tempStudent = student1;
	student1 = student2;
	student2 = tempStudent;
}