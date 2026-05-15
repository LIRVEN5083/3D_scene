#include "load_GLSL.hpp"

MyFile::file_read::file_read(std::string& file_path){
	std::stringstream buffer;
	std::ifstream file(file_path);

	if (!file.is_open()) {
		std::cout << "ERROR: file is not opened\n";
	}

	buffer << file.rdbuf();
	sourceCode = buffer.str();
}

const char* MyFile::file_read::getSource() const{
	return sourceCode.c_str();
}