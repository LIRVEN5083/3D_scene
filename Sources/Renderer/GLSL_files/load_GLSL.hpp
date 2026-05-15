#ifndef _LOAD_GLSL_HPP
#define _LOAD_GLSL_HPP

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

namespace MyFile {
	class file_read {
	public:
		file_read(std::string& file_path);

		const char* getSource() const;
	private:
		std::string sourceCode;
	};
}

#endif