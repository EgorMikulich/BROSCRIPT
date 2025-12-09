#include <iostream>
#include <fstream>
#include <vector>
int main()
{
    std::vector<char> code(0);
    std::ifstream file("Code.bs");
    char cursor;
    if (file.is_open()) { // reading a file, deleting other characters
        while (file.get(cursor))
            for (char i : "broBRO")
                if (cursor == i)
                    code.push_back(cursor);
    };
    file.close();
    for (unsigned int i = 0; i < code.size() - 2; i += 3) { // bf translation
        if (code[i] == 'b') {
            if (code[i + 1] == 'r') {
                if (code[i + 2] == 'o') 
                    code[i / 3] = '>';
                else if (code[i + 2] == 'O') 
                    code[i / 3] = '.';
            }
            else if (code[i + 1] == 'R') {
                if (code[i + 2] == 'o') 
                    code[i / 3] = '+';
                else if (code[i + 2] == 'O') 
                    code[i / 3] = '[';
            }
        }
        else if (code[i] == 'B') {
            if (code[i + 1] == 'r') {
                if (code[i + 2] == 'o') 
                    code[i / 3] = '<';
                else if (code[i + 2] == 'O') 
                    code[i / 3] = ',';
            }
            else if (code[i + 1] == 'R') {
                if (code[i + 2] == 'o') 
                    code[i / 3] = '-';
                else if (code[i + 2] == 'O') 
                    code[i / 3] = ']';
            }
        }
    }

    unsigned int code_size = code.size(), counter = 0;
    for (int i = code_size - 1; i >= 0; i--) { // cleaning up syntax remnants
        switch (code[i]) {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
            case '[':
            case ']':
                break;
            default:
                code.erase(code.begin() + i);
            break;
        }
    }

    //for (int i = 0; i < code.size(); i++)
    //    std::cout << code[i];
    std::vector<unsigned char> vars(30000);
    code_size = code.size();
    unsigned char brackets;
    cursor = 0;

    while (counter < code_size) { // interpretation of bf code
        switch (code[counter]) {
        case '>':
            if (cursor < 29999)
                cursor++;
            break;
        case '<':
            if (cursor > 0)
                cursor--;
            break;
        case '+':
            vars[cursor]++;
            break;
        case '-':
            vars[cursor]--;
            break;
        case '.':
            std::cout << vars[cursor];
            break;
        case ',':
            std::cin >> vars[cursor];
            break;
        case '[':
            if (vars[cursor] == 0) {
                brackets = 1;
                while (brackets > 0) {
                    counter++;
                    if (code[counter] == '[')
                        brackets += 1;
                    else if (code[counter] == ']')
                        brackets -= 1;
                }
            }
            break;
        case ']':
            if (vars[cursor] != 0) {
                brackets = 1;
                while (brackets > 0) {
                    counter--;
                    if (code[counter] == '[')
                        brackets -= 1;
                    else if (code[counter] == ']')
                        brackets += 1;
                }
            }
            break;
        }
        counter++;
    }
    std::cin >> vars[cursor];
}
