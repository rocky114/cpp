#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main() {
    std::string input = "tag1.tag2.tag3~name";
    std::vector<std::string> tokens;
    
    std::istringstream iss(input);
    std::string token;

    size_t pos {};
    size_t last_pos {};
    while ((pos = input.find_first_of(".~", last_pos)) != std::string::npos) {
        tokens.push_back(input.substr(last_pos, pos - last_pos));
        last_pos = pos + 1;
    }
    tokens.push_back(input.substr(last_pos));
    
    // 打印分隔后的结果
    for (const std::string& t : tokens) {
        std::cout << t << std::endl;
    }
    
    return 0;
}
