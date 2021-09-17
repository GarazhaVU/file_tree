#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cctype>
#include <stdlib.h>
using namespace std;




struct File //Структура "Файл"
{
	string name;
	int size;
};




struct Folder // Структура "Папка"
{
	string name;
	list <Folder> folders;
	list <File> files;
};




string* Split(string str, int length) { //Метод для разделения строки на подстроки
	string* string_array = new string[length];
	string buffer = "";
	int counter = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] != '\n') {
			buffer += str[i];
		}
		else {
			string_array[counter] = buffer;
			buffer = "";
			counter++;
		}
	}
	return string_array;
}




list<Folder> increase(string one_str, list<Folder> folders) { //Метод для построение дерева
	int counter = 0; string name = "";

	if (one_str[0] >= 'A' && one_str[0] <= 'Z') {

		while (one_str[counter] != '\\' && one_str[counter] != '\0') {
			name += one_str[counter];
			counter++;
		}

		bool flag = false; int counter_2 = 0;
		for (auto& fr : folders) {
			if (fr.name == name) {
				string string_reserv = "";
				for (int i = counter + 1; i < one_str.length(); i++) {
					string_reserv += one_str[i];
				}
				flag = true; File file; bool flag2 = false;
				if (one_str[counter] != '\0' && (one_str[counter + 1] < 'A' || one_str[counter + 1] > 'Z')) {
					string reserv_name = "";
					counter++;
					string size_reserv = "";
					while (one_str[counter] != ' ') {
						reserv_name += one_str[counter];
						counter++;
					}
					counter++;
					while (one_str[counter] != '\0') {
						size_reserv += one_str[counter];
						counter++;
					}
					File file;
					file.name = reserv_name;
					file.size = atoi(size_reserv.c_str());
					fr.files.push_back(file);
				}
				else if (one_str[counter] != '\0') {
					string string_reserv = "";
					for (int i = counter + 1; i < one_str.length(); i++) {
						string_reserv += one_str[i];
					}
					fr.folders = increase(string_reserv, fr.folders);
				}
				break;
			}
			counter_2++;
		}
		if (flag == false) {

			Folder fr;
			fr.name = name;
			if (one_str[counter] != '\0' && (one_str[counter + 1] < 'A' || one_str[counter + 1] > 'Z')) {
				string reserv_name = "";
				counter++;
				string size_reserv = "";
				while (one_str[counter] != ' ') {
					reserv_name += one_str[counter];
					counter++;
				}
				counter++;
				while (one_str[counter] != '\0') {
					size_reserv += one_str[counter];
					counter++;
				}
				File file;
				file.name = reserv_name;
				file.size = atoi(size_reserv.c_str());
				fr.files.push_back(file);
			}
			else if (one_str[counter] != '\0') {
				string string_reserv = "";
				for (int i = counter + 1; i < one_str.length(); i++) {
					string_reserv += one_str[i];
				}
				fr.folders = increase(string_reserv, fr.folders);
			}
			folders.push_front(fr);
		}
	}
	return folders;
}




list<string> output(list<Folder> catalog, int level, list<string> output_list) { //Формирование list для дальнейшей записи в файл
	for (auto& fr : catalog) {
		string reserv_string = "";
		for (int i = 0; i < level; i++) {
			reserv_string += ' ';
		}
		reserv_string += fr.name;
		output_list.push_back(reserv_string);
		int next_uroven = level + 2;
		output_list = output(fr.folders, next_uroven, output_list);
		for (auto& fl : fr.files) {
			string reserv_string_2 = "";
			for (int i = 0; i < level + 2; i++) {
				reserv_string_2 += ' ';
			}
			reserv_string_2 += fl.name;
			output_list.push_back(reserv_string_2);
		}

	}
	return output_list;
}




list<Folder> sorting(list<Folder> catalog) { //Сортировка
	for (auto& fr : catalog) {
		for (auto& fr_2 : catalog) {
			if (fr.name < fr_2.name) {
				Folder fr_reserv = fr;
				fr = fr_2;
				fr_2 = fr_reserv;
			}
		}
	}
	for (auto& fr : catalog) {
		fr.folders = sorting(fr.folders);
		for (auto& fl : fr.files) {
			for (auto& fl_2 : fr.files) {
				if (fl.size == fl_2.size) {
					if (fl.name < fl_2.name) {
						File fl_reserv = fl;
						fl = fl_2;
						fl_2 = fl_reserv;
					}
				}
				else {
					if (fl.size > fl_2.size) {
						File fl_reserv = fl;
						fl = fl_2;
						fl_2 = fl_reserv;
					}
				}
			}
		}
	}
	return catalog;
}




int main()
{
	string path = "puth.txt"; //Считывание данных с файла

	ifstream open_file;
	open_file.open(path);
	if (open_file.is_open()) {
		string str;
		string b = "";
		int length = 0;

		while (getline(open_file, str))
		{
			b = b + str + "\n";
			length++;
		}

		string* str_array = Split(b, length);

		list <Folder> catalog;
		for (int i = 0; i < length; i++) {   // Построение дерева
			catalog = increase(str_array[i], catalog);
		}
		catalog = sorting(catalog);          //Сортировка
		list<string> output_list;
		output_list = output(catalog, 0, output_list);//Формирование list для записи


		ofstream fout;
		fout.open("output_file.txt", ofstream::app);//Запись в файл
		if (fout.is_open()) {
			for (auto output : output_list) {
				fout << output << '\n';
			}
		}
		else
		{
			cout << "Ошибка! Файл не открывается" << endl;
		}
		fout.close();
	}
	else
	{
		cout << "Ошибка! Файл не открывается" << endl;
	}
	open_file.close();
}


