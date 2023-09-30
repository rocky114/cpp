#include <iostream>
#include <sstream>
#include <map>


struct element {
	std::string tag {};
	std::map<std::string, std::string> attributes {};
	std::map<std::string, element> children {};
};

void extract(std::map<std::string, struct element>& root, const std::string& line) 
{
	std::string::size_type start = line.find('<');
	std::string::size_type end = line.find('>');

	std::cout << start << end << std::endl;

	std::string tagContent = line.substr(start + 1, end - start - 1);

	std::cout << tagContent << std::endl;

	return ;
}

int main() 
{	
	std::map<std::string, struct element> root {};

	std::string str {"<tag1 value = \"HelloWorld\">"};
	extract(root, str);

	return 0;
	
	/* 
	int number {}, query {};

	std::cin >> number >> query;

	std::cin.ignore();

	// std::map<std::string, struct element> root {};

	for (int i = 0; i < number; i++) {
		std::string line {};
		std::getline(std::cin, line);

		extract(root, line);

		std::cout << line << std::endl;
	}

	return 0;*/
}