#include <iostream>
#include <sstream>
#include <map>
#include <vector>


struct element {
	std::string tag {};
	std::map<std::string, std::string> attributes {};
	std::map<std::string, element> children {};
	bool is_closing_tag {false};
};

struct element append_child(struct element node, struct element current);

void extract(struct element& root, const std::string line) 
{
	std::string::size_type start = line.find('<');
	std::string::size_type end = line.find('>');
	std::string tagContent = line.substr(start + 1, end - start - 1);

	struct element current {};

	if (tagContent[0] == '/') {
		tagContent = tagContent.substr(1);
	}

	std::stringstream ss(tagContent);
	std::string word;

	std::string key {};
	std::string val {};
	bool is_equal_operator {false};

	for (int i = 0; ss >> word; i++) {
		if (i == 0) {
			current.tag = word;
		}

		if (word == "=") {
			is_equal_operator = true;

			continue;
		}

		if (is_equal_operator) {
			val = word.substr(1, word.size() - 2);
		} else {
			key = word;

			continue;
		}

		is_equal_operator = false;
		current.attributes[key] = val;
	}

	if (root.tag == "") {
		root.tag = current.tag;
		root.attributes = current.attributes;

		return;
	}

	if (root.tag == current.tag) {
		root.is_closing_tag = true;
		return;
	}

	root = append_child(root, current);
}

struct element append_child(struct element node, struct element current) 
{
	for (auto& pair : node.children) {		
		if (!pair.second.is_closing_tag) {
			pair.second = append_child(pair.second, current);

			return node;
		}
	}
	
	if (node.tag == current.tag) {
		node.is_closing_tag = true;
		return node;
	}

	node.children[current.tag] = current;

	return node;
}

void echo (struct element current) 
{
	std::cout << "echo tag: " << current.tag << " attribute: ";
	for (auto& pair : current.attributes) {
		std::cout << pair.first << " = " << pair.second;
	}
	std::cout << std::endl;

	for (auto& pair : current.children) {
		echo(pair.second);
	}
}

std::string parse(struct element root, std::string line) {
	std::vector<std::string> result {};

	size_t pos {};
    size_t last_pos {};
    while ((pos = line.find_first_of(".~", last_pos)) != std::string::npos) {
        result.push_back(line.substr(last_pos, pos - last_pos));
        last_pos = pos + 1;
    }
    result.push_back(line.substr(last_pos));

	auto length = result.size() - 1;

	std::string attr = result[length];

	struct element current_node = root;

	int cout {0};
	for (int i = 1; i < length; i++) {
		for (auto pair : current_node.children) {
			if (pair.first == result[i]) {
				cout++;
				current_node = pair.second;
				break;
			}
		}
	}

	if (cout + 1 < length) {
		return "Not Found!";
	}

	auto it = current_node.attributes.find(attr);
	if (it != current_node.attributes.end()) {
		return current_node.attributes[attr];
	}

	return "Not Found!";
}

int main() 
{		
	int number {6}, query {4};

	std::cin >> number >> query;

	std::cin.ignore();

	struct element root {};

	for (int i = 0; i < number; i++) {
		std::string line {};
		std::getline(std::cin, line);

		// switch (i)
		// {
		// case 0:
		// 	line = "<a>";
		// 	break;
		// case 1:
		// 	line = "<b name = \"tag_one\">";
		// 	break;
		// case 2:
		// 	line = "<c name = \"tag_two\" value = \"val_907\">";
		// 	break;
		// case 3:
		// 	line = "</c>";
		// 	break;
		// case 4:
		// 	line = "</b>";
		// 	break;
		// case 5:
		// 	line = "</a>";
		// 	break;
		// default:
		// 	break;
		// }

		extract(root, line);
	}

	for (int i = 0; i < query; i++) {
		std::string line {};
		std::getline(std::cin, line);

		// switch (i)
		// {
		// case 0:
		// 	line = "a.b~name";
		// 	break;
		// case 1:
		// 	line = "a.b.c~value";
		// 	break;
		// case 2:
		// 	line = "a.b.c~src";
		// 	break;
		// case 3:
		// 	line = "a.b.c.d~name";
		// 	break;
		// default:
		// 	break;
		// }

		std::cout << parse(root, line) << std::endl;
	}

	return 0;
}