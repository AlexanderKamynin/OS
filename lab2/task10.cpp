#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[]){
	if (argc < 1){
		std::cout << argv[0] << " no argument\n";
		return 0;
	}
	FILE* file;
	file = fopen(argv[1], "r");
	if (file){
		char line[100];
		while (fgets(line, sizeof(line), file)){
			std::cout << line;
		}
		fclose(file);
	}
	else {
		std::cout << argv[1] << " can't open\n";
	}
	return 0;
}