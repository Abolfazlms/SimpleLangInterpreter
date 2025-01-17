#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>
#include <cmath>

using namespace std;

// Function to handle binary operations
int handleBinaryOperation(const string& input1, const string& input2, const string& operation, const map<string, int>& variables) {
    int val1 = 0, val2 = 0;

    // Resolve first input
    if (input1[0] == '$') {
        auto it = variables.find(input1.substr(1));
        if (it != variables.end()) {
            val1 = it->second;
        } else {
            throw runtime_error("Undefined variable: " + input1);
        }
    } else {
        val1 = stoi(input1);
    }

    // Resolve second input
    if (input2[0] == '$') {
        auto it = variables.find(input2.substr(1));
        if (it != variables.end()) {
            val2 = it->second;
        } else {
            throw runtime_error("Undefined variable: " + input2);
        }
    } else {
        val2 = stoi(input2);
    }

    // Perform the operation
    if (operation == "add") {
        return val1 + val2;
    } else if (operation == "minus") {
        return val1 - val2;
    } else if (operation == "multiply") {
        return val1 * val2;
    } else if (operation == "divide") {
        if (val2 == 0) throw runtime_error("Division by zero");
        return val1 / val2;
    } else if (operation == "modulus") {
        if (val2 == 0) throw runtime_error("Division by zero");
        return val1 % val2;
    } else if (operation == "power") {
        return pow(val1, val2);
    } else {
        throw runtime_error("Unknown operation: " + operation);
    }
}

// Function to handle unary operations (increase, decrease)
int handleUnaryOperation(const string& input, const string& operation, map<string, int>& variables) {
    int val = 0;

    // Resolve input
    if (input[0] == '$') {
        auto it = variables.find(input.substr(1));
        if (it != variables.end()) {
            val = it->second;
        } else {
            throw runtime_error("Undefined variable: " + input);
        }
    } else {
        val = stoi(input);
    }

    // Perform the operation
    if (operation == "increase") {
        val += 1;
        variables[input.substr(1)] = val; // Update the variable after increasing
        return val;
    } else if (operation == "decrease") {
        val -= 1;
        variables[input.substr(1)] = val; // Update the variable after decreasing
        return val;
    } else {
        throw runtime_error("Unknown operation: " + operation);
    }
}

// Function to handle conditional jumps
bool processConditionalJump(const string& tag, const string& input1, const string& input2, const string& operation,
                            map<string, int>& variables, map<string, int>& tags, int& lineNumber) {
    int val1 = 0, val2 = 0;

    // Resolve first input
    if (input1[0] == '$') {
        auto it = variables.find(input1.substr(1));
        if (it != variables.end()) {
            val1 = it->second;
        } else {
            throw runtime_error("Undefined variable: " + input1);
        }
    } else {
        val1 = stoi(input1);
    }

    // Resolve second input
    if (input2[0] == '$') {
        auto it = variables.find(input2.substr(1));
        if (it != variables.end()) {
            val2 = it->second;
        } else {
            throw runtime_error("Undefined variable: " + input2);
        }
    } else {
        val2 = stoi(input2);
    }

    // Perform the conditional jump operation
    if ((operation == "jump_if_equal" && val1 == val2) ||
        (operation == "jump_if_not_equal" && val1 != val2) ||
        (operation == "jump_if_greater" && val1 > val2) ||
        (operation == "jump_if_less" && val1 < val2)) {
        auto tagIt = tags.find(tag);
        if (tagIt != tags.end()) {
            lineNumber = tagIt->second - 1; // Update line number to the tag's line
            return true;
        } else {
            throw runtime_error("Undefined tag: " + tag);
        }
    }

    return false;
}
// Function to clean up spaces
string cleanSpaces(const string& input) {
    // Remove all spaces (including leading and trailing)
    string result = regex_replace(input, regex("\\s+"), "");
    return result;
}

// Main function
int main() {
    string filename = "input.txt";
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file: " << filename << endl;
        return 1;
    }

   // Regex patterns
    regex binaryOpRegex(R"(([$a-zA-Z0-9_]+)\s*,\s*([$a-zA-Z0-9_]+)\s*->\s*(add|minus|multiply|divide|modulus|power)\s*->\s*\$([a-zA-Z_][a-zA-Z0-9_]*)\s*;)");
    regex unaryOpRegex(R"(([$a-zA-Z0-9_]+)\s*->\s*(increase|decrease)\s*;)");
    regex assignmentRegex(R"((\d+)\s*->\s*\$([a-zA-Z_][a-zA-Z0-9_]*)\s*;)");
    regex printRegex(R"(([$a-zA-Z0-9_]+)\s*->\s*print\s*;)");
    regex tagRegex(R"(@([a-zA-Z_][a-zA-Z0-9_]*)\s*;)");
    regex jumpRegex(R"(@([a-zA-Z_][a-zA-Z0-9_]*)\s*->\s*jump\s*;)");
    regex conditionalJumpRegex(R"(@([a-zA-Z_][a-zA-Z0-9_]*)\s*,\s*([$a-zA-Z0-9_]+)\s*,\s*([$a-zA-Z0-9_]+)\s*->\s*(jump_if_equal|jump_if_not_equal|jump_if_greater|jump_if_less)\s*;)");
    regex exitRegex(R"(exit\s*;)");

    string line;
    map<string, int> variables;
    map<string, int> tags;  // Map to store the positions of the tags
    map<int, string> lines; // Map to store all lines for reprocessing jumps
    bool isExit = false;
    bool shouldJump = false;
    int lineNumber = 0;

    // Pass 1: Read the file and store all lines
    while (getline(inputFile, line)) {
        lineNumber++;
        lines[lineNumber] = cleanSpaces(line);

        // Automatically register tags during first appearance
        smatch match;
        if (regex_match(line, match, tagRegex)) {
            string tagName = match[1].str();
            tags[tagName] = lineNumber; // Record the line number of the tag
        }
    }
    inputFile.close();

    // Pass 2: Execute the instructions
    lineNumber = 0;
    while (lineNumber < lines.size() && !isExit) {
        lineNumber++;
        line = lines[lineNumber];
        smatch match;

        // Match tags (skip, as they are already registered)
        if (regex_match(line, match, tagRegex)) {
            continue;
        }

        if (regex_match(line, match, conditionalJumpRegex)) {
            string tag = match[1].str();
            string input1 = match[2].str();
            string input2 = match[3].str();
            string operation = match[4].str();

            try {
                if (processConditionalJump(tag, input1, input2, operation, variables, tags, lineNumber)) {
                    continue; // Skip the remaining lines and jump
                }
            } catch (const runtime_error& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }

        // Match jump
        else if (regex_match(line, match, jumpRegex)) {
            string tag = match[1].str();
            if (tags.find(tag) != tags.end()) {
                lineNumber = tags[tag] - 1; // Jump to the tag line
                continue;
            } else {
                cerr << "Error: Undefined tag " << tag << endl;
            }
        }
        // Match binary operations
        else if (regex_match(line, match, binaryOpRegex)) {
            string input1 = match[1].str();
            string input2 = match[2].str();
            string operation = match[3].str();
            string outputVar = match[4].str();

            try {
                int result = handleBinaryOperation(input1, input2, operation, variables);
                variables[outputVar] = result;
            } catch (const runtime_error& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
        // Match unary operations
        else if (regex_match(line, match, unaryOpRegex)) {
            string input = match[1].str();
            string operation = match[2].str();

            try {
                int result = handleUnaryOperation(input, operation, variables);
                variables[input.substr(1)] = result;
            } catch (const runtime_error& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
        // Match variable assignments
        else if (regex_match(line, match, assignmentRegex)) {
            int value = stoi(match[1].str());
            string varName = match[2].str();

            variables[varName] = value;
        }
        // Match print statements
        else if (regex_match(line, match, printRegex)) {
            string input = match[1].str();

            if (input[0] == '$') {
                auto it = variables.find(input.substr(1));
                if (it != variables.end()) {
                    cout << it->second << endl;
                } else {
                    cerr << "Error: Undefined variable " << input << endl;
                }
            } else {
                cout << input << endl;
            }
        }
        // Match exit command
        else if (regex_match(line, match, exitRegex)) {
            isExit = true;
            break;
        }
    }

    return 0;
}
