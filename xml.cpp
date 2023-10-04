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

using custom = std::map<std::string, struct element>;

custom append_xml_element(custom nodes, struct element current);

void extract(custom& root, const std::string line) 
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

	/*if (root.tag == "") {
		root.tag = current.tag;
		root.attributes = current.attributes;

		return;
	}

	if (root.tag == current.tag) {
		root.is_closing_tag = true;
		return;
	}*/

	root = append_xml_element(root, current);
}

custom append_xml_element(custom nodes, struct element current) 
{
	for (auto& root_pair : nodes) {
		if (!root_pair.second.is_closing_tag) {
			for (auto& pair : root_pair.second.children) {		
				if (!pair.second.is_closing_tag) {
					custom temp = append_xml_element({{pair.first, pair.second}}, current);
					pair.second = temp[pair.first];

					return nodes;
				}
			}
			
			if (root_pair.second.tag == current.tag) {
				root_pair.second.is_closing_tag = true;
				return nodes;
			}

			root_pair.second.children[current.tag] = current;

			return nodes;
		}
	}

	nodes[current.tag] = current;

	return nodes;
}

void echo (custom nodes) 
{
	for (auto root_pair : nodes) {
		std::cout << "echo tag: " << root_pair.second.tag << " attribute: ";
		for (auto pair : root_pair.second.attributes) {
			std::cout << pair.first << " = " << pair.second << " ";
		}
		std::cout << std::endl;

		for (auto pair : root_pair.second.children) {
			echo({{pair.first, pair.second}});
		}
	}
}

std::string parse(custom root, std::string line) {
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

	custom current_node = root;

	for (int i = 0; i < length - 1; i++) {
		for (auto pair : current_node) {
			if (pair.first == result[i]) {
				current_node = pair.second.children;
				break;
			}
		}
	}

	for (auto pair : current_node) {
		if (pair.second.tag == result[length - 1]) {
			auto it = pair.second.attributes.find(attr);
			if (it != pair.second.attributes.end()) {
				return pair.second.attributes[attr];
			}
		}
	}
	
	return "Not Found!";
}

int main() 
{		
	int number {10}, query {10};

	std::cin >> number >> query;

	std::cin.ignore();

	custom root {};

	for (int i = 0; i < number; i++) {
		std::string line {};
		std::getline(std::cin, line);

		/*switch (i)
		{
		case 0:
			line = "<a value = \"GoodVal\">";
			break;
		case 1:
			line = "<b value = \"BadVal\" size = \"10\">";
			break;
		case 2:
			line = "</b>";
			break;
		case 3:
			line = "<c height = \"auto\">";
			break;
		case 4:
			line = "<d size = \"3\">";
			break;
		case 5:
			line = "<e strength = \"2\">";
			break;
		case 6:
			line = "</e>";
			break;
		case 7:
			line = "</d>";
			break;
		case 8:
			line = "</c>";
			break;
		case 9:
			line = "</a>";
			break;
		default:
			break;
		}*/

		extract(root, line);
	}

	for (int i = 0; i < query; i++) {
		std::string line {};
		std::getline(std::cin, line);

		/*switch (i)
		{
		case 0:
			line = "a~value";
			break;
		case 1:
			line = "b~value";
			break;
		case 2:
			line = "a.b~size";
			break;
		case 3:
			line = "a.b~value";
			break;
		case 4:
			line = "a.b.c~height";
			break;
		case 5:
			line = "a.c~height";
			break;
		case 6:
			line = "a.d.e~strength";
			break;
		case 7:
			line = "a.c.d.e~strength";
			break;
		case 8:
			line = "d~sze";
			break;
		case 9:
			line = "a.c.d~size";
			break;
		default:
			break;
		}*/

		std::cout << parse(root, line) << std::endl;
	}

	return 0;
}