// 引入所需的头文件。这些头文件提供了程序中使用的各种功能和数据结构。  
#include <iostream>  
#include <fstream> // 用于文件操作  
#include <sstream> // 用于字符串流操作  
#include <string>  // 用于字符串操作  
#include <unordered_map> // 用于哈希表操作  
#include <vector> // 用于向量操作  
#include <cassert>
using namespace std;
// 使用标准命名空间，这样就可以直接使用标准库中的类型和函数，而不需要每次都写 std::。  

// 主函数，程序的入口点。  
int main() {
    // 指定要读取的文件路径。  
    string filename = "D:\\作业\\文学研究助手\\text.txt";
    // 创建一个输入文件流对象，用于读取文件。  
    ifstream infile(filename); // 打开文件  
    if (!infile) { // 如果文件打开失败（例如文件不存在）  
        cout << "Error: file not found!" << endl; // 输出错误信息  
        return 0; // 返回0表示程序异常结束  
    }

    // 创建一个哈希表（unordered_map），用于存储单词、频数和行数。键是单词，值是一个pair，包含频数和行数向量。  
    unordered_map<string, pair<int, vector<int>>> wordMap;
    wordMap.reserve(10000); // 根据需要调整预分配的大小  
    // 读取文件的每一行，直到文件末尾。  
    string line, word;
    int lineNumber = 1; // 当前行号，初始化为1  
    while (getline(infile, line)) { // 逐行读取文件内容  
        stringstream ss(line); // 将每一行内容转换为字符串流对象，以便进行分割。  
        while (ss >> word) { // 从字符串流中读取单词，直到字符串流结束或读取到空格。  
            // 创建一个新的字符串来存储处理后的单词。只保留字母字符，并将其转换为小写。  
            string cleanedWord;
            for (char c : word) {
                 if (isalpha(c)) {
                    cleanedWord += tolower(c);
                 }
              
            }
            if (!cleanedWord.empty()) { // 如果处理后的单词不为空（即不是空白字符或标点符号）  
                // 在哈希表中更新单词的频数和行数。如果单词已存在，则增加频数并将行号添加到行数向量中；如果不存在，则添加新条目。  
                wordMap[cleanedWord].first++; // 更新频数  
                wordMap[cleanedWord].second.push_back(lineNumber); // 将当前行号添加到行数向量中  
            }
        }
        lineNumber++; // 增加行号，以在下一次循环中处理下一行。  
    }

    // 提示用户输入要查询的单词，并读取输入。这里使用getline函数来读取整行，包括空格。  
    string queryWords;
    cout << "Enter one or more words to search (separated by spaces): "; // 输出提示信息  
    getline(cin, queryWords); // 从标准输入读取用户输入的单词（使用空格分隔）  

    stringstream querySS(queryWords); // 将用户输入的字符串转换为字符串流对象，以便进行分割。  
    string queryWord; // 存储当前处理的查询单词。  
    while (querySS >> queryWord) { // 从字符串流中读取查询单词，直到字符串流结束或读取到空格。  
        // 检查哈希表中是否包含查询单词。如果包含，则输出该单词的频数和出现的行号；否则，输出未找到的信息。  
        if (wordMap.count(queryWord) > 0) { // 检查哈希表中是否包含查询单词。如果包含，则返回1；否则返回0。  
            auto result = wordMap[queryWord]; // 获取查询单词在哈希表中的值（频数和行数向量）。  
            cout << "Word: " << queryWord << endl; // 输出查询单词。  
            cout << "Frequency: " << result.first << endl; // 输出频数。  
            cout << "Lines: "; 
            for (int line : result.second)
            {
                cout << line << " ";
            }// 输出对应行数
            cout << endl;
        }
        else
        {
            cout << "Word not found: " << queryWord << endl;
        }
        cout << endl;
    }

    return 0;
}
