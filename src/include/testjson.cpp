#include <iostream>
#include <fstream>
#include "json.hpp"  // 引入 nlohmann/json 库

using json = nlohmann::json;

int main() {
    // 打开并读取 JSON 文件
    std::ifstream file("test.json");
    if (!file.is_open()) {
        std::cerr << "无法打开文件 test.json" << std::endl;
        return 1;
    }

    json data;
    file >> data;  // 解析 JSON 文件
    file.close();

    // 输出 tiles 数据
    std::cout << "Tiles 数据：" << std::endl;
    for (const auto& row : data["tiles"]) {
        for (const auto& tile : row) {
            std::cout << tile << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
