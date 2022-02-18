#include <stdio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#define PATH "Students.txt"
#define head1 "|              Фамилия              |                Имя                |             Отчество              | Дата рождения |      Пол      |\n"
#define head2 "|           Год поступления         |             Факультет             |             Кафедра               | Номер зачетной книжки         |\n"
#define line cout << " "; for (int j = 0; j < 140; j++) cout << "-"; cout << " \n";
using namespace std;

struct Sub {
	char* name = new char[21];
	int* mark = new int();
};

class Program {
public:
	void print(char* val) {
		cout << val;
	}

	void print(int val) {
		cout << val;
	}

	void print(string val) {
		cout << val;
	}

	void cin_cl() {
		cin.seekg(0, ios::end);
		cin.clear();
	}

	void cin_ig() {
		cin.clear();
		cin.ignore();
	}

	bool check_date(int day, int month, int year) {
		if (day != 0 && month != 0 && year != 0) {
			if (year >= 1900 && year <= 2020) {
				if (month >= 1 && month <= 12) {
					switch (month) {
					case 1: case 3: case 5: case 7: case 8: case 10: case 12:
						if (day >= 1 && day <= 31) {
							return true;
						}
						break;
					case 2:
						if (year % 4 != 0 || year % 100 == 0 && year % 400 != 0) {
							if (day >= 1 && day <= 28) {
								return true;
							}
						}
						else {
							if (day >= 1 && day <= 29) {
								return true;
							}
						}
						break;
					case 4: case 6: case 9: case 11:
						if (day >= 1 && day <= 30) {
							return true;
						}
						break;
					default:
						print("[ERROR] - Введена неверная дата\n");
						break;
					}

				}
				else {
					print("[ERROR] - Месяц должен быть от 1 до 12\n");
				}
			}
			else {
				print("[ERROR] - Год должен быть от 1900 до 2020\n");
			}
		}
		print("Не верная дата\n");
		return false;
	}

	int protection_year_of_receipt() {
		int value;
		while (true) {
			cin >> value;
			if (value > 0) {
				cin_ig();
				if (value >= 1900 && value <= 2021) {
					return value;
				}
				else {
					print("Неверные данные! Повторите ввод \n");
				}
			}
			print("Неверные данные! Вводите только int данные \n");
			cin_ig();
		}
	}

	char protection_gender() {
		char value;
		while (true) {
			cin >> value;
			if (value == 'М' || value == 'Ж') {
				cin_cl();
				return value;
			}
			print("Не верные данные! Пожалуйста вводите только M для Юношей или F для Девушек! \n");
			cin_cl();
		}
	}

	void protect_inp_ch(char* in, int len) {
		char* buf = new char[len]();
		cin_cl();
		cin.get(buf, len);
		cin_cl();
		if (strlen(buf) == 0) {
			print("Строка пустая, повторите ввод: ");
			protect_inp_ch(in, len);
		}
		else {
			for (int i = 0; i < len; i++) {
				in[i] = *(buf + i);
			}
			delete[] buf;
		}
	}

	inline void Wait() {
		char* temp = new char[2]();
		print("Нажмите любую кнопку для продолжения...");
		cin_cl();
		cin.get(temp, 1);
		cin_cl();
		delete[] temp;
	}

};

class Student: Program {
	friend class File;
public:

	Student(){
		fam = new char[31]();
		name = new char[31]();
		otc = new char[31]();
		day = new int(0);
		month = new int(0);
		year = new int(0);
		priem_year = new int(0);
		gen = new char[2]();
		fac = new char[25]();
		kaf = new char[25]();
		group = new char[11]();
		book = new char[21]();
	}
	~Student() {
		delete fam;
		delete name;
		delete otc;
		delete day;
		delete month;
		delete year;
		delete priem_year;
		delete fac;
		delete kaf;
		delete group;
		delete book;
	}

	void Set() {
		Set_fam();
		Set_name();
		Set_otc();
		Set_bday();
		Set_priem_year();
		Set_gender();
		Set_fac();
		Set_kaf();
		Set_group();
		Set_book();
	}

	void Set_fam() {
		print("Введите Фамилию {30}: ");
		protect_inp_ch(fam, 31);
		cin_cl();
	}

	void Set_name() {
		print("Введите Имя {30}: ");
		protect_inp_ch(name, 31);
		cin_cl();
	}

	void Set_otc() {
		print("Введите Отчество {30}: ");
		protect_inp_ch(otc, 31);
		cin_cl();
	}

	void Set_bday() {
		print("Дата Рождения {dd.mm.yyyy}: ");
		char* temp = new char[11];
		*day = 0;
		*month = 0;
		*year = 0;
		cin.get(temp, 11);
		cin_ig();
		for (int i = 0; *(temp + i) != '\0'; i++) {
			if (*(temp + i) >= 48 && *(temp + i) <= 57 && ((i >= 0 && i <= 1) || (i >= 3 && i <= 4) || (i >= 6 && i <= 9))) {
				switch (i) {
				case 0: case 1:
					*day = *day * 10 + *(temp + i) - 0x30;
					break;
				case 3: case 4:
					*month = *month * 10 + *(temp + i) - 0x30;
					break;
				case 6: case 7: case 8: case 9:
					*year = *year * 10 + *(temp + i) - 0x30;
					break;
				}
			}
		}

		delete[] temp;
		if (!check_date(*day, *month, *year)) {
			*day = 0;
			*month = 0;
			*year = 0;
			Set_bday();
		}
	}

	void Set_priem_year() {
		print("Год Поступления {1900-2020}: ");
		*priem_year = protection_year_of_receipt();
		if (*priem_year <= *year) {
			print("Год поступления не может равняться или быть меньше года рождения \n");
			Set_priem_year();
		}
	}

	void Set_gender() {
		print("Пол {[М/Ж]}: ");
		*gen = protection_gender();
		*(gen + 1) = '\0';
	}

	void Set_fac() {
		print("Введите Факультет {25}: ");
		protect_inp_ch(fac, 25);
		cin_cl();
	}

	void Set_kaf() {
		print("Введите Кафедру {25}: ");
		protect_inp_ch(kaf, 25);
		cin_cl();
	}

	void Set_group() {
		print("Введите Группу {11}: ");
		protect_inp_ch(group, 11);
		cin_cl();
	}

	void Set_book() {
		print("Введите Номер зачетной книжки {21}: ");
		protect_inp_ch(book, 21);
		cin_cl();
		if (!Check_book()) {
			print("Такой номер зачетной книжки уже существует\n");
			Set_book();
		}
		
	} 

	bool Check_book() {
		int* len = new int(0);
		int* len_file = new int(0);
		char* buf = new char[21];

		ifstream File;
		File.open(PATH, ios::binary);

		File.seekg(0, ios::end);
		*len_file = File.tellg();
		File.seekg(0, ios::beg);

		while (*len != *len_file) {
			if (*len_file == -1) {
				print("[ERROR] файл не существует\n");
				return true;
			}
			if (*len_file == 0) {
				print("[ERROR] В файле нет данных");
				return true;
			}

			File.seekg(171, ios::beg);

			*len = *len + 171;

			File.read(buf, 21);
			*len = *len + 21;

			if (!strcmp(buf, book)) {
				return false;
			}

			int* session_count = new int(0);
			int* subject_count = new int(0);
			int* sum = new int(0);

			File.read((char*)&*session_count, 4);
			*len = *len + 4;

			*len = *len + *session_count * 4;

			for (int i = 0; i < *session_count; i++) {
				File.read((char*)subject_count, 4);
				*sum = *sum + *subject_count;
			}
			File.seekg((*sum) * 25, ios::cur);
			*len = *len + (*sum) * 25;
		}
		return true;
	}

	void Get() {
		Get_fam();
		Get_name();
		Get_otc();
		Get_gender();
		Get_day();
		Get_priem_year();
		Get_fac();
		Get_kaf();
		Get_group();
		Get_book();
	}

	char* Get_fam() {
		return fam;
	}

	char* Get_name() {
		return name;
	}

	char* Get_otc() {
		return otc;
	}

	int Get_day() {
		return *day;
	}

	int Get_month() {
		return *month;
	}

	int Get_year() {
		return *year;
	}
	
	char Get_gender() {
		return *gen;
	}

	int Get_priem_year() {
		return *priem_year;
	}

	char* Get_fac() {
		return fac;
	}

	char* Get_kaf() {
		return kaf;
	}

	char* Get_group() {
		return group;
	}

	char* Get_book() {
		return book;
	}

	

private:
	char* fam = nullptr;
	char* name = nullptr;
	char* otc = nullptr;
	int* day = nullptr;
	int* month = nullptr;
	int* year = nullptr;
	int* priem_year = nullptr;
	char* gen = nullptr;
	char* fac = nullptr;
	char* kaf = nullptr;
	char* group = nullptr;
	char* book = nullptr;
};

class Session: Program {
	friend class File;
public:
	Session() {
		sesion_count = new int(0);
		sub_count = nullptr;
	}
	
	~Session() {
		delete sesion_count;
		delete sub_count;
		delete subject;
	}

	void Set_sesion() {
		Set_sesion_count();
		Set_sub_count();
		Set_sub();
	}

	void Set_sesion_count() {
		print("Количество семестров {1-9}: ");
		int value;
		while (true) {
			cin >> value;
			cin_cl();
			if (value >= 1 && value <= 9) {
				*sesion_count = value;
				break;
			}
			print("Не верные данные! Вводите значения от 1 до 9 \n");
		}
	}

	void Set_sub_count() {
		sub_count = new int[*sesion_count];
		bool flag = true;
		for (int i = 0; i < *sesion_count; i++) {
			bool flag = true;
			print("Введите количество предметов в ");
			print(i + 1);
			print(" семестре {1-10}: ");
			while (flag) {
				int* buf = new int();
				cin >> *buf;
				cin_cl();
				if (*buf >= 1 && *buf <= 10) {
					*(sub_count + i) = *buf;
					flag = false;
				}
				else {
					print("Не верные данные! Вводите значения от 1 до 9 \n");
				}
			}
		}
	}

	void Set_sub() {
		int* sum = new int(0);
		for (int i = 0; i < *sesion_count; i++) {
			*sum = *sum + *(sub_count + i);
		}
		subject = new Sub[*sum];
		int* session_num = new int(0);
		int* subject_num = new int(0);
		for (int i = 0; i < *sum; i++) {
			if (*subject_num >= sub_count[*session_num]) {
				(*session_num)++;
				*subject_num = 0;
			}
			(*subject_num)++;
			(subject + i)->name = new char[21]();
			(subject + i)->mark = new int(0);
			print("Cессия ");
			print(*session_num + 1);
			print(" предмет ");
			print(*subject_num);
			print(" название предмета {20}: ");
			protect_inp_ch((subject+i)->name, 21);
			cin_cl();
			print("Cессия ");
			print(*session_num + 1);
			print(" предмет ");
			print(*subject_num);
			print(" оценка {[2-5]}: ");
			int buf;
			while (true) {
				cin >> buf;
				cin_cl();
				if (buf >= 2 && buf <= 5) {
					*(subject + i)->mark = buf;
					break;
				}
				print("Не верные данные! Вводите значения от 2 до 5\n");
			}
		}
		delete sum;
		delete session_num;
		delete subject_num;
	}

private:
	int* sesion_count = nullptr;
	int* sub_count = nullptr;
	Sub* subject = nullptr;
};

class File : Program {
public:

	File() {
		length = new int(0);
		len = new int(0);
		pos = new int(0);
		count = new int(0);
		sum = new int(0);
		gbn = new char[21]();
		gbn_t = new char[21]();
		len_rd = nullptr;
		len_stud = nullptr;
	}

	~File() {
		delete length;
		delete len;
		delete pos;
		delete count;
		delete sum;
		delete[] gbn;
		delete[] gbn_t;
	}

	void Stud_count() {
		ifstream File;
		File.open(PATH, ios::binary);

		*len = 0;
		*count = 0;
		File.seekg(0, ios::end);
		*length = File.tellg();
		File.seekg(0, ios::beg);

		while (*length != *len) {
			if (*length == -1) {
				print("ERROR - файл не существует\n");
				*count = -1;
				return;
			}
			if (*length == 0) {
				print("ERROR - В файле нет данных\n");
				*count =  0;
				return;
			}
			File.seekg(192, ios::cur); 
			*len = *len + 192;

			int* session_count = new int(0);
			int* subject_count = new int(0);

			File.read((char*)&*session_count, 4);
			*len = *len + 4;

			*len = *len + *session_count * 4;
			*sum = 0;
			for (int i = 0; i < *session_count; i++) {
				File.read((char*)&*subject_count, 4);
				*sum = *sum + *subject_count;
			}
			File.seekg((*sum * 25), ios::cur);
			*len = *len + (*sum * 25);
			(*count)++;
		}
		File.close();
	}

	void Add_student() {
		ofstream file(PATH, ios::binary | ios::app);
		
		Student* student = new Student;
		Session* session = new Session;
		student->Set();
		session->Set_sesion();

		file.write(student->fam, 31);
		file.write(student->name, 31);
		file.write(student->otc, 31); //93
		file.write((char*)student->day, 4);
		file.write((char*)student->month, 4);
		file.write((char*)student->year, 4);//105
		file.write(student->gen, 1);
		file.write((char*)student->priem_year, 4);//110
		file.write(student->fac, 25);
		file.write(student->kaf, 25);//160
		file.write(student->group, 11);//171
		file.write(student->book, 21);//192

		delete student;

		file.write((char*)session->sesion_count, 4);

		for (int i = 0; i < *session->sesion_count; i++) {
			file.write((char*)(&*(session->sub_count + i)), 4);
		}
		*sum = 0;
		for (int i = 0; i < *session->sesion_count; i++) {
			*sum = *sum + *(session->sub_count + i);
		}
		for (int i = 0; i < *sum; i++) {
			file.write((char*)(session->subject+i)->name, 21);
			file.write((char*)(session->subject + i)->mark, 4);
		}
		
		delete session;
		file.close();
	}

	void Read_student() {
		ifstream File;
		File.open(PATH, ios::binary);

		File.seekg(0, ios::end);
		*length = File.tellg();
		File.seekg(*len_rd, ios::beg);
		if (*len_rd != *length) {
			if (*length == -1) {
				print("[ERROR] файл не существует\n");
				return;
			}
			if (*length == 0) {
				print("[ERROR] В файле нет данных\n");
				return;
			}

			edit_student = new Student();
			edit_session = new Session();

			File.read(edit_student->fam, 31);
			File.read(edit_student->name, 31);
			File.read(edit_student->otc, 31); //93
			File.read((char*)edit_student->day, 4);
			File.read((char*)edit_student->month, 4);
			File.read((char*)edit_student->year, 4);//105
			File.read(edit_student->gen, 1);
			File.read((char*)edit_student->priem_year, 4);//110
			File.read(edit_student->fac, 25);
			File.read(edit_student->kaf, 25);//160
			File.read(edit_student->group, 11);//171
			File.read(edit_student->book, 21);//192

			File.read((char*)edit_session->sesion_count, 4);

			edit_session->sub_count = new int[*edit_session->sesion_count];
			*sum = 0;
			for (int i = 0; i < *edit_session->sesion_count; i++) {
				File.read((char*)(&*(edit_session->sub_count + i)), 4);
				*sum = *sum + *(edit_session->sub_count + i);
			}

			edit_session->subject = new Sub[*sum]();

			for (int i = 0; i < *sum; i++) {
				File.read((char*)(edit_session->subject + i)->name, 21);
				File.read((char*)(edit_session->subject + i)->mark, 4);
			}
			*len_rd = *len_rd + 192;
			*len_rd = *len_rd + 4;
			*len_rd = *len_rd + *edit_session->sesion_count * 4;
			*len_rd = *len_rd + *sum * 25;
		}
		File.close();
	}

	void Edit_student() {
		Stud_count();
		system("cls");
		print("Редактирования информации о студенте\n");
		len_rd = new int(0);
		*pos = -1;
		gbn_t = new char[21]();
		print("Введите номер зачетной книжки >> ");
		cin_cl();
		protect_inp_ch(gbn_t, 21);
		cin_cl();
		for (int i = 0; i < *count; i++) {
			Read_student();
			if (!strcmp(gbn_t, edit_student->Get_book())) {
				*pos = i;
				break;
			}
			delete edit_student;
			delete edit_session;
		}
		if (*pos != -1) {
			int ans;
			system("cls");
			print("Редактирования информации о студенте\n");
			print("1 - Редактировать все данные о студенте\n");
			print("2 - Редактировать сведения о студенте\n");
			print("3 - Редактировать данные о сессии студента\n");
			print("4 - Назад\n");
			cin >> ans;
			switch (ans) {
			case 1:
				*len_rd = 0;
				for (int i = 0; i < *count; i++) {
					Read_student();
					if (i != *pos) {
						Write_NewFile();
					}
					else {
						edit_student->Set();
						edit_session->Set_sesion();
						Write_NewFile();
					}
					delete edit_student;
					delete edit_session;
				}
				remove(PATH);//add error otcladchik
				rename("Students.new.txt", PATH);
				break;
			case 2:
				*len_rd = 0;
				for (int i = 0; i < *count; i++) {
					Read_student();
					if (i != *pos) {
						Write_NewFile();
					}
					else {
						edit_student->Set();
						Write_NewFile();
					}
					delete edit_student;
					delete edit_session;
				}
				remove(PATH);//add error otcladchik
				rename("Students.new.txt", PATH);
				break;
			case 3:
				*len_rd = 0;
				for (int i = 0; i < *count; i++) {
					Read_student();
					if (i != *pos) {
						Write_NewFile();
					}
					else {
						edit_session->Set_sesion();
						Write_NewFile();
					}
					delete edit_student;
					delete edit_session;
				}
				remove(PATH);//add error otcladchik
				rename("Students.new.txt", PATH);
				break;
			case 4:
				return;
			}
		}
		else {
			print("Такой студент не найден\n");
			Wait();
			Delete_student();
		}
	}

	void Delete_student() {
		Stud_count();
		len_rd = new int(0);
		*pos = -1;
		gbn_t = new char[21]();
		print("Введите номер зачетной книжки >> ");
		cin_cl();
		protect_inp_ch(gbn_t, 21);
		cin_cl();
		for (int i = 0; i < *count; i++) {
			edit_student = new Student();
			edit_session = new Session();
			Read_student();
			if (!strcmp(gbn_t, edit_student->Get_book())) {
				*pos = i;
				break;
			}
			delete edit_student;
			delete edit_session;
		}
		if (*pos != -1) {
			*len_rd = 0;
			for (int i = 0; i < *count; i++) {
				Read_student();
				if (i != *pos) {
					Write_NewFile();
				}
				delete edit_student;
				delete edit_session;
			}
			remove(PATH);//add error otcladchik
			rename("Students.new.txt", PATH);
		}
		else {
			print("Такой студент не найден\n");
			Delete_student();
		}
	}

	void Write_NewFile(){
			char newname[] = "Students.new.txt";
			ofstream FILE_NEW;
			FILE_NEW.open(newname, ios::binary | ios::app);

			FILE_NEW.write(edit_student->fam, 31);
			FILE_NEW.write(edit_student->name, 31);
			FILE_NEW.write(edit_student->otc, 31); //93
			FILE_NEW.write((char*)edit_student->day, 4);
			FILE_NEW.write((char*)edit_student->month, 4);
			FILE_NEW.write((char*)edit_student->year, 4);//105
			FILE_NEW.write(edit_student->gen, 1);
			FILE_NEW.write((char*)edit_student->priem_year, 4);//110
			FILE_NEW.write(edit_student->fac, 25);
			FILE_NEW.write(edit_student->kaf, 25);//160
			FILE_NEW.write(edit_student->group, 11);//171
			FILE_NEW.write(edit_student->book, 21);//192

			FILE_NEW.write((char*)edit_session->sesion_count, 4);

			for (int i = 0; i < *edit_session->sesion_count; i++) {
				FILE_NEW.write((char*)(&*(edit_session->sub_count + i)), 4);
			}
			*sum = 0;
			for (int i = 0; i < *edit_session->sesion_count; i++) {
				*sum = *sum + *(edit_session->sub_count + i);
			}
			for (int i = 0; i < *sum; i++) {
				FILE_NEW.write((char*)(edit_session->subject + i)->name, 21);
				FILE_NEW.write((char*)(edit_session->subject + i)->mark, 4);
			}
			FILE_NEW.close(); 
	}

	void Print_students(bool Full) {
		Stud_count();
		if (*count != 0 && *count != -1) {
			len_rd = new int(0);
			for (int i = 0; i < *count; i++) {
				Read_student();
				line;
				print(head1);
				line;
				cout << "| "  << edit_student->Get_fam();
				for (int j = 0; j < 33 - strlen(edit_student->Get_fam()); j++) cout << " ";
				cout << " | " << edit_student->Get_name();
				for (int j = 0; j < 33 - strlen(edit_student->Get_name()); j++) cout << " ";
				cout << " | " << edit_student->Get_otc();
				for (int j = 0; j < 33 - strlen(edit_student->Get_otc()); j++) cout << " ";
				cout << " | "  << edit_student->Get_day() << "." << edit_student->Get_month() << "." << edit_student->Get_year();
				int count = 6;
				if (edit_student->Get_day() < 10 && edit_student->Get_month() < 10) count += 2;
				else if (edit_student->Get_day() > 10 && edit_student->Get_month() < 10) count += 3;
				else if (edit_student->Get_day() < 10 && edit_student->Get_month() > 10) count += 3;
				else if (edit_student->Get_day() > 10 && edit_student->Get_month() > 10) count += 4;
				for (int j = 0; j < 14 - count; j++) print(" ");
				cout << "|       " << edit_student->Get_gender() << "       |\n";
				line;
				print(head2);
				line;
				print("| ");
				print(edit_student->Get_priem_year());
				for (int j = 0; j < 29; j++) print(" ");
				print(" | ");
				print(edit_student->Get_fac());
				for (int j = 0; j < 33 - strlen(edit_student->Get_fac()); j++) print(" ");
				print(" | ");
				print(edit_student->Get_kaf());
				for (int j = 0; j < 33 - strlen(edit_student->Get_kaf()); j++) print(" ");
				print(" | ");
				print(edit_student->Get_book());
				for (int j = 0; j < 29 - strlen(edit_student->Get_book()); j++) print(" ");
				print(" |\n");
				line;
				if (Full) {
					for (int j = 0; j < *edit_session->sesion_count; j++) {
						cout << "| Сессия № " << j + 1;
						for (int k = 0; k < 128; k++) cout << " ";
						print("|\n");
						line;
						if (*edit_session->sub_count + j < 5) {
							int k = 0;
							print("| ");
							for (; k < edit_session->sub_count[j]; k++) {
								cout << ((&edit_session->subject[k])->name);
								for (int l = 0; l < 25 - strlen(((edit_session->subject + k)->name)); l++) print(" ");
								print(" | ");
							}
							for (; k < 5; k++) {
								print("************************* | ");
							}
							print("\n");
							line;
							k = 0;
							print("| ");
							for (; k < *edit_session->sub_count + j; k++) {
								cout << *((edit_session->subject + k)->mark);
								for (int l = 0; l < 24; l++) print(" ");
								print(" | ");
							}
							for (; k < 5; k++) {
								print("************************* | ");
							}
							print("\n");
							line;
						}
						else {
							print("| ");
							for (int k = 0; k < 5; k++) {
								cout << ((edit_session->subject + j)->name + k);
								for (int l = 0; l < 25 - strlen(((edit_session->subject + k)->name)); l++) print(" ");
								print(" | ");
							}
							print("\n");
							line;
							print("| ");
							for (int k = 0; k < 5; k++) {
								cout << *((edit_session->subject + k)->mark);
								for (int l = 0; l < 24; l++) print(" ");
								print(" | ");
							}
							line;
							int k = 5;
							print("| ");
							for (; k < *edit_session->sub_count + j; k++) {
								cout << ((edit_session->subject + k)->name);
								for (int l = 0; l < 25 - strlen(((edit_session->subject + k)->name)); l++) print(" ");
								print(" | ");
							}
							for (; k < 11; k++) {
								print("************************* | ");
							}
							print("\n");
							line;
							k = 5;
							print("| ");
							for (; k < *edit_session->sub_count + j; k++) {
								cout << *((edit_session->subject + k)->mark);
								for (int l = 0; l < 24; l++) print(" ");
								print(" | ");
							}
							for (; k < 11; k++) {
								print("************************* | ");
							}
							print("\n");
							line;
						}
					}
				}
				print("\n");
				delete edit_student;
				delete edit_session;
			}
		}
		else {
			print("Файл пустой или его не существует");
			return;
		}
	}

	void Print_without_3(bool Full) {
		Stud_count();
		if (*count != 0 && *count != -1) {
			len_rd = new int(0);
			for (int i = 0; i < *count; i++) {
				Read_student();
				if (Check_mark()) {
					line;
					print(head1);
					line;
					cout << "| " << edit_student->Get_fam();
					for (int j = 0; j < 33 - strlen(edit_student->Get_fam()); j++) cout << " ";
					cout << " | " << edit_student->Get_name();
					for (int j = 0; j < 33 - strlen(edit_student->Get_name()); j++) cout << " ";
					cout << " | " << edit_student->Get_otc();
					for (int j = 0; j < 33 - strlen(edit_student->Get_otc()); j++) cout << " ";
					cout << " | " << edit_student->Get_day() << "." << edit_student->Get_month() << "." << edit_student->Get_year();
					int count = 6;
					if (edit_student->Get_day() < 10 && edit_student->Get_month() < 10) count += 2;
					else if (edit_student->Get_day() > 10 && edit_student->Get_month() < 10) count += 3;
					else if (edit_student->Get_day() < 10 && edit_student->Get_month() > 10) count += 3;
					else if (edit_student->Get_day() > 10 && edit_student->Get_month() > 10) count += 4;
					for (int j = 0; j < 14 - count; j++) print(" ");
					cout << "|       " << edit_student->Get_gender() << "       |\n";
					line;
					print(head2);
					line;
					print("| ");
					print(edit_student->Get_priem_year());
					for (int j = 0; j < 29; j++) print(" ");
					print(" | ");
					print(edit_student->Get_fac());
					for (int j = 0; j < 33 - strlen(edit_student->Get_fac()); j++) print(" ");
					print(" | ");
					print(edit_student->Get_kaf());
					for (int j = 0; j < 33 - strlen(edit_student->Get_kaf()); j++) print(" ");
					print(" | ");
					print(edit_student->Get_book());
					for (int j = 0; j < 29 - strlen(edit_student->Get_book()); j++) print(" ");
					print(" |\n");
					line;
					if (Full) {
						for (int j = 0; j < *edit_session->sesion_count; j++) {
							cout << "| Сессия № " << j + 1;
							for (int k = 0; k < 128; k++) cout << " ";
							print("|\n");
							line;
							if (*edit_session->sub_count + j < 5) {
								int k = 0;
								for (; k < *edit_session->sub_count + j; k++) {
									cout << "| " << ((edit_session->subject + k)->name );
									for (int l = 0; l < 25 - strlen(((edit_session->subject + k)->name)); l++) print(" ");
									print(" |");
								}
								for (; k < 5; k++) {
									print(" ************************* |");
								}
								print("\n");
								line;
								k = 0;
								for (; k < *edit_session->sub_count + j; k++) {
									cout << "| " << *((edit_session->subject + k)->mark );
									for (int l = 0; l < 24; l++) print(" ");
									print(" |");
								}
								for (; k < 5; k++) {
									print(" ************************* |");
								}
								print("\n");
								line;
							}
							else {
								for (int k = 0; k < 5; k++) {
									cout << "| " << ((edit_session->subject + k)->name);
									for (int l = 0; l < 25 - strlen(((edit_session->subject + k)->name)); l++) print(" ");
									print(" |");
								}
								print("\n");
								line;
								for (int k = 0; k < 5; k++) {
									cout << "| " << *((edit_session->subject + k)->mark);
									for (int l = 0; l < 24; l++) print(" ");
									print(" |");
								}
								line;
								int k = 5;
								for (; k < *edit_session->sub_count + j; k++) {
									cout << "| " << ((edit_session->subject + k)->name);
									for (int l = 0; l < 25 - strlen(((edit_session->subject + k)->name)); l++) print(" ");
									print(" |");
								}
								for (; k < 11; k++) {
									print(" ************************* |");
								}
								print("\n");
								line;
								k = 5;
								for (; k < *edit_session->sub_count + j; k++) {
									cout << "| " << *((edit_session->subject + k)->mark);
									for (int l = 0; l < 24; l++) print(" ");
									print(" |");
								}
								for (; k < 11; k++) {
									print(" ************************* |");
								}
								print("\n");
								line;
							}
						}
					}
					print("\n");
					delete edit_student;
					delete edit_session;
				}
			}
		}
		else {
			print("Файл пустой или его не существует");
			return;
		}
	}

	bool Check_mark() {
		for (int i = 0; i < *edit_session->sesion_count; i++) {
			for (int j = 0; j < *(edit_session->sub_count + i); j++) {
				if (*((edit_session->subject + j)->mark) == 3) {
					return false;
				}
			}
		}
		return true;
	}

private:
	Student* edit_student = nullptr;
	Session* edit_session = nullptr;
	int* length;
	int* len;
	int* len_rd;
	int* len_stud;
	int* pos;
	int* count;
	int* sum;
	char* gbn;
	char* gbn_t;
};

class Menu : Program {
public:

	Menu() {
		ans = new int;
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		system("cls");
		file = new File;
		hub();
	}

	~Menu() {
		delete file;
		delete ans;
	}

	void hub() {
		file = new File;
		system("cls");
		print("Выберите вариант\n");
		print("1 - Добавить студента\n");
		print("2 - Удалить студента\n");
		print("3 - Изменить данные студента\n");
		print("4 - Вывести всю базу студентов\n");
		print("5 - Вывести всех студентов, не имеющих оценки 3\n");
		print("6 - Очистить экран\n");
		print("7 - Выйти из программы\n");
		print(" >>>> ");
		cin >> *ans;
		cin_cl();
		switch (*ans) {
		case 1: {
			system("cls");
			print("Добавление нового студента\n");
			file->Add_student();
			break; 
			}
		case 2: {
			system("cls");
			print("Удаление студента\n");
			file->Delete_student();
			break;
			}
		case 3: {
			file->Edit_student();
			break;
		}
		case 4: {
			system("cls");
			print("Вывод всех студентов\n");
			print("1 - Вывод всей информации\n");
			print("2 - Вывод части информации\n");
			print("3 - Назад\n");
			print(">>> ");
			cin >> *ans;
			switch (*ans) {
			case 1: {
				file->Print_students(true);
				Wait();
				break;
				}
			case 2:
			{
				file->Print_students(false);
				Wait();
				break;
			}
			case 3:
				break;
			}
			break;
		}
		case 5:
			system("cls");
			print("Вывод всех студентов, не имеющих оценки 3\n");
			print("1 - Вывод всей информации\n");
			print("2 - Вывод части информации\n");
			print("3 - Назад\n");
			print(">>> ");
			cin >> *ans;
			switch (*ans) {
			case 1: {
				file->Print_without_3(true);
				Wait();
				break;
			}
			case 2:
			{
				file->Print_without_3(false);
				Wait();
				break;
			}
			case 3:
				break;
			}
			break;
		case 6:
			system("cls");
			break;
		case 7:
			return;
		}
		delete file;
		hub();
	}

private:
	File* file = nullptr;
	int* ans = nullptr;
};

int main() {
	
	Menu* menu = new Menu();
	delete menu;
	return 1;
}