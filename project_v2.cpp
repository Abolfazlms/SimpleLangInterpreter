#include<bits/stdc++.h>
using namespace std;

// Input file name containing the program instructions
string inputFile = "input.txt";
// store the program, which contains the input split into lines
vector<vector<string>> program;
// Stack for storing operations & values
vector<string> st;
// storing tags & positions
map<string, int> tag;
// Map for storing variables & values
map<string, string> variables;
// split a line of input into separate words
vector<string> sliceLine(string line) {
    vector<string> res;
    string temp = "";
    // Iterate through each character of the line and split based on spaces, commas, dashes, etc.
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ',' || line[i] == ';' || line[i] == '-' || line[i] == ' ') {
            if (!temp.empty()) {
                res.push_back(temp);
                temp = "";
            }
        } else if (line[i] == '>') {
            res.push_back(">");
        } else {
            temp += line[i];
        }
    }
    // If there's any leftover word, add it to the result
    if (!temp.empty()) {
        res.push_back(temp);
    }
    return res;
}
// read input from the file & store it in the 'program' vector
void getInput() {
    string line;
    ifstream input(inputFile);
    while (getline(input, line))
        program.push_back(sliceLine(line));
}
// find all tags & store them in the 'tag' map
void findTags() {
    for (int i = 0; i < program.size(); i++) {
        vector<string> line = program[i];
        if (line.size() == 1 && line[0][0] == '@') tag[line[0]] = i;
    }
}
// retrieve one value from the stack, and return it as a string
string getValue() {
    st.pop_back();
    string res;
    // Check if the top of the stack is a variable (starts with '$')
    if (st[st.size() - 1][0] == '$')
        res = variables[st[st.size() - 1]];
    else
        res = st[st.size() - 1];
    st.pop_back();
    return res;
}
// retrieve two values from the stack, parse them, and return as a pair of integers
pair<int, int> getValues() {
    string a = getValue();
    st.push_back(">");
    string b = getValue();
    int x = stoi(a), y = stoi(b);
    return {y, x};
}
// print the result at the top of the stack
void print() {
    cout << getValue() << endl; // Print the result stored in the stack
}
// add the two values from the stack and push the result into the stack
void add() {
    pair<int, int> p = getValues();
    st.push_back(to_string(p.first + p.second));
}
// subtract the two values from the stack and push the result into the stack
void subtract() {
    pair<int, int> p = getValues();
    st.push_back(to_string(p.first - p.second));
}
// multiply the two values from the stack and push the result into the stack
void multiply() {
    pair<int, int> p = getValues();
    st.push_back(to_string(p.first * p.second));
}
// divide the two values from the stack and push the result into the stack
void divide() {
    pair<int, int> p = getValues();
    st.push_back(to_string(p.first / p.second));
}
// calculate the power of the two values from the stack and push the result into the stack
void power() {
    pair<int, int> p = getValues();
    st.push_back(to_string(pow(p.first, p.second)));
}
// calculate the modulus of the two values from the stack and push the result onto the stack
void mod() {
    pair<int, int> p = getValues();
    st.push_back(to_string(p.first % p.second));
}
// increase the value of the variable (second to last item in the stack) by 1
void increase() {
    string var = st[st.size() - 2];
    int x = stoi(getValue());
    x++;
    string y = to_string(x);
    variables[var] = y;
}
// decrease the value of the variable (second to last item in the stack) by 1
void decrease() {
    string var = st[st.size() - 2];
    int x = stoi(getValue());
    x--;
    string y = to_string(x);
    variables[var] = y;
}
// check if the first value is greater than the second
bool jump_if_greater() {
    pair<int, int> p = getValues();
    return p.first > p.second;
}
// check if the first value is less than the second
bool jump_if_less() {
    pair<int, int> p = getValues();
    return p.first < p.second;
}
// check if the first value is equal to the second
bool jump_if_equal() {
    pair<int, int> p = getValues();
    return p.first == p.second;
}
// Function to check if the first value is not equal to the second
bool jump_if_not_equal() {
    pair<int, int> p = getValues();
    return p.first != p.second;
}
int main() {
    // Ask user for the input file name
    cout << "ENTER FILE NAME: " << endl;
    cin >> inputFile;
    // Get input from the file
    getInput();
    findTags();
    // Process each line in the program
    for (int i = 0; i < program.size(); i++) {
        st.clear();  // Clear the stack for the next line
        vector<string> line = program[i];
        string nextTag = "";  // Store the tag name for jumps
        // Process each word in the current line
        for (auto word : line) {
            if (word == ">") st.push_back(word);  // Handle the '>' operation (Assignment)
            else if (word[0] == '@') {
                nextTag = word;  // Store the tag for future jumps
            }
            else if (word[0] == '$') {
                // If the top of the stack is '>', assign a variable value
                if (st.size() == 0) st.push_back(word);
                else if (st[st.size() - 1] == ">") {
                    string oneNum = getValue();
                    variables[word] = oneNum;
                    st.push_back(oneNum);
                }
                else
                    st.push_back(word);
            }
            else {
                // Handle various operations
                if (word == "decrease") decrease();
                else if (word == "increase") increase();
                else if (word == "power") power();
                else if (word == "add") add();
                else if (word == "minus") subtract();
                else if (word == "divide") divide();
                else if (word == "multiply") multiply();
                else if (word == "jump_if_not_equal") {
                    if (jump_if_not_equal()) i = tag[nextTag];
                }
                else if (word == "jump_if_equal") {
                    if (jump_if_equal()) i = tag[nextTag];
                }
                else if (word == "jump_if_less") {
                    if (jump_if_less()) i = tag[nextTag];
                }
                else if (word == "jump_if_greater") {
                    if (jump_if_greater()) i = tag[nextTag];
                }
                else if (word == "modulus") mod();
                else if (word == "jump") i = tag[nextTag];
                else if (word == "exit") return 0;  // Exit the program
                else if (word == "print") print();  // Print the top of the stack
                else st.push_back(word);  // Push other words to the stack
            }
        }
    }
    return 0;
}
