// ���������ͷ�ļ�����Щͷ�ļ��ṩ�˳�����ʹ�õĸ��ֹ��ܺ����ݽṹ��  
#include <iostream>  
#include <fstream> // �����ļ�����  
#include <sstream> // �����ַ���������  
#include <string>  // �����ַ�������  
#include <unordered_map> // ���ڹ�ϣ�����  
#include <vector> // ������������  
#include <cassert>
using namespace std;
// ʹ�ñ�׼�����ռ䣬�����Ϳ���ֱ��ʹ�ñ�׼���е����ͺͺ�����������Ҫÿ�ζ�д std::��  

// ���������������ڵ㡣  
int main() {
    // ָ��Ҫ��ȡ���ļ�·����  
    string filename = "D:\\��ҵ\\��ѧ�о�����\\text.txt";
    // ����һ�������ļ����������ڶ�ȡ�ļ���  
    ifstream infile(filename); // ���ļ�  
    if (!infile) { // ����ļ���ʧ�ܣ������ļ������ڣ�  
        cout << "Error: file not found!" << endl; // ���������Ϣ  
        return 0; // ����0��ʾ�����쳣����  
    }

    // ����һ����ϣ��unordered_map�������ڴ洢���ʡ�Ƶ�������������ǵ��ʣ�ֵ��һ��pair������Ƶ��������������  
    unordered_map<string, pair<int, vector<int>>> wordMap;
    wordMap.reserve(10000); // ������Ҫ����Ԥ����Ĵ�С  
    // ��ȡ�ļ���ÿһ�У�ֱ���ļ�ĩβ��  
    string line, word;
    int lineNumber = 1; // ��ǰ�кţ���ʼ��Ϊ1  
    while (getline(infile, line)) { // ���ж�ȡ�ļ�����  
        stringstream ss(line); // ��ÿһ������ת��Ϊ�ַ����������Ա���зָ  
        while (ss >> word) { // ���ַ������ж�ȡ���ʣ�ֱ���ַ������������ȡ���ո�  
            // ����һ���µ��ַ������洢�����ĵ��ʡ�ֻ������ĸ�ַ���������ת��ΪСд��  
            string cleanedWord;
            for (char c : word) {
                 if (isalpha(c)) {
                    cleanedWord += tolower(c);
                 }
              
            }
            if (!cleanedWord.empty()) { // ��������ĵ��ʲ�Ϊ�գ������ǿհ��ַ�������ţ�  
                // �ڹ�ϣ���и��µ��ʵ�Ƶ������������������Ѵ��ڣ�������Ƶ�������к���ӵ����������У���������ڣ����������Ŀ��  
                wordMap[cleanedWord].first++; // ����Ƶ��  
                wordMap[cleanedWord].second.push_back(lineNumber); // ����ǰ�к���ӵ�����������  
            }
        }
        lineNumber++; // �����кţ�������һ��ѭ���д�����һ�С�  
    }

    // ��ʾ�û�����Ҫ��ѯ�ĵ��ʣ�����ȡ���롣����ʹ��getline��������ȡ���У������ո�  
    string queryWords;
    cout << "Enter one or more words to search (separated by spaces): "; // �����ʾ��Ϣ  
    getline(cin, queryWords); // �ӱ�׼�����ȡ�û�����ĵ��ʣ�ʹ�ÿո�ָ���  

    stringstream querySS(queryWords); // ���û�������ַ���ת��Ϊ�ַ����������Ա���зָ  
    string queryWord; // �洢��ǰ����Ĳ�ѯ���ʡ�  
    while (querySS >> queryWord) { // ���ַ������ж�ȡ��ѯ���ʣ�ֱ���ַ������������ȡ���ո�  
        // ����ϣ�����Ƿ������ѯ���ʡ����������������õ��ʵ�Ƶ���ͳ��ֵ��кţ��������δ�ҵ�����Ϣ��  
        if (wordMap.count(queryWord) > 0) { // ����ϣ�����Ƿ������ѯ���ʡ�����������򷵻�1�����򷵻�0��  
            auto result = wordMap[queryWord]; // ��ȡ��ѯ�����ڹ�ϣ���е�ֵ��Ƶ����������������  
            cout << "Word: " << queryWord << endl; // �����ѯ���ʡ�  
            cout << "Frequency: " << result.first << endl; // ���Ƶ����  
            cout << "Lines: "; 
            for (int line : result.second)
            {
                cout << line << " ";
            }// �����Ӧ����
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
