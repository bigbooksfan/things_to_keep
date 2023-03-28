#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iomanip>

class File_read {

public:		// constructors
	File_read();
	File_read(std::string fname);
	~File_read();

public:		// methods
	void Parse_first_row();

private:	// methods
	void Open_file(std::string fname);
	template <typename T>
	void Print_vector(std::vector<T>& to_print);
	template <typename T, typename U>
	void Print_map(std::map<T, U>& to_print);

private:	// fields
	std::string					fname_			;
	std::fstream				file_			;
	std::string					str_curr_		;
	std::vector<std::string>	vec_curr_		;
	std::map<int, std::string>	structure_		;		// < column number , title > of first row
};

//------------------------------------ Template methods --------------------------------------//

template<typename T>
inline void File_read::Print_vector(std::vector<T>& to_print) {
	std::cout << "Vector content: ";
	bool is_first = true;
	for (T i : to_print) {
		if (!is_first) 
			std::cout << " ";
		is_first = false;
		std::cout << i;
	}
	std::cout << std::endl;
}

template<typename T, typename U>
inline void File_read::Print_map(std::map<T, U>& to_print) {
	std::cout << "Map content:\n";
	for (std::pair<T, U> i : to_print) {
		std::cout << std::setw(3) << i.first << "   " << i.second << std::endl;
	}
	std::cout << "End of map.\n";
}

//------------------------------------ Common methods --------------------------------------//

File_read::File_read() {
	Open_file("");
}

File_read::File_read(std::string fname) {
	Open_file(fname);
}

void File_read::Open_file(std::string fname) {
	bool is_open = false;
	do {
		fname_ = fname;
		std::cout << "Enter name of file: ";
		if (fname_.length() != 0) {
			std::cout << fname_ << std::endl;
		}
		else {
			std::cin >> fname_;
		}
		file_.open(fname_, std::ios::in);

		is_open = file_.is_open();
		if (!is_open)
			std::cout << "Invalid file name. Try again.\n";

	} while (!is_open);

	std::cout << "File open: SUCCESS\n";
}

File_read::~File_read() {
	file_.close();
	std::cout << "File " << fname_ << " closed.";
	fname_.clear();
}

void File_read::Parse_first_row() {
	std::getline(file_, str_curr_);
	std::cout << "First row parse:\n";
	//std::cout << "Row: " << str_curr_ << std::endl;
	int delimeter_counter = 0;

	const char delimeter = ';';
	size_t pos = 0;
	std::string cell;
	while ((pos = str_curr_.find(delimeter)) != std::string::npos) {
		++delimeter_counter;
		cell = str_curr_.substr(0, pos);
		if (cell.length() > 1 || (cell.length() == 1 && cell[0] != ' ')) {
			vec_curr_.push_back(cell);
			structure_.emplace(delimeter_counter, cell);
			cell.clear();
		}
		str_curr_.erase(0, pos + 1);
	}
	//Print_vector(vec_curr_);
	Print_map(structure_);
}