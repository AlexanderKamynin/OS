#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <syscall.h>


void create_directory(std::string directory_path) {
	directory_path = "mkdir " + directory_path;
	const char *cstr = directory_path.c_str();
	std::system(cstr);
}

void create_files(const std::string& dicrectory_path, int count_files) {
	std::ofstream file;
	for (int i = 1; i < count_files + 1; i++) {
		std::string file_name = dicrectory_path + "/file" + std::to_string(i) + ".txt";
		file.open(file_name);
		file.close();
	}
}

void delete_directory(std::string directory_path) {
	directory_path = "rm -r " + directory_path;
	const char *cstr = directory_path.c_str();
	std::system(cstr);
}

void check_size(std::string directory_path){
	directory_path = "du -hs " + directory_path;
	const char *cstr = directory_path.c_str();
	std::system(cstr);
}

int main() {
	//init the main directory
	create_directory("task7");

	std::vector<std::string> paths;

	//int max_files = 0;
	int command = -1;
	std::cout << "Commands:" << std::endl;
	std::cout << "\t1 - create directory" << std::endl;
	std::cout << "\t2 - create files in the directory" << std::endl;
	std::cout << "\t3 - clear the directory" << std::endl;
	std::cout << "\t4 - check size the directory" << std::endl;
	std::cout << "\t-1 - end the program and get the max files values" << std::endl;
	while (true) {
		paths.clear();
		std::cout << "Enter your command" << std::endl;
		std::cin >> command;
		if (command > 4 || command <= 0) {
			//std::cout << "Max files is " << max_files;
			break;
		}

		std::string directory;
		int count = 0;

		switch (command)
		{
		case 1: {
			std::cout << "Enter the directory path" << std::endl;
			
			std::cin >> directory;
			create_directory(directory);
			break;
		}
		case 2: {
			std::cout << "Enter the count files, that will create" << std::endl;
			std::cin >> count;
			std::cout << "Enter the directory path, there you want to create the files" << std::endl;
			std::cin >> directory;
			create_files(directory, count);
			//get_files(paths, "task7");
			//max_files = std::max(max_files, int(paths.size()));
			//std::cout << "Current size is " << paths.size();
			break;
		}
		case 3: {
			std::cout << "Enter the directory path, that you want to delete" << std::endl;
			std::cin >> directory;
			delete_directory(directory);
			//get_files(paths, "task7");
			//std::cout << "Current size is " << paths.size();
			break;
		}
		case 4: {
			std::cout << "Enter the directory path, that size you want to see" << std::endl;
			std::cin >> directory;
			check_size(directory);
			break;
		}
		default:
			break;
		}
		std::cout << std::endl;
		std::system("du -hs task7");
		//std::system("tree task7/");
		std::cout << std::endl;
	}

	delete_directory("task7");
	return 0;
}
