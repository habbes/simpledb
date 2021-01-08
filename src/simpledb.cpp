#include <iostream>
#include <map>
#include <vector>

class Value {
    int _value;
    bool _has_value;
public:
    Value(int value) : _value(value), _has_value(true) {}
    Value() : _has_value(false) {}

    int value() {
        return _value;
    }

    bool has_value() {
        return _has_value;
    }

    void set_value(int value) {
        _value = value;
        _has_value = true;
    }
};


class MemTable {
    std::map<int, int> table;
public:
    void put(int key, int value) {
        table[key] = value;
    }

    Value get(int key) {
        Value value;
        if (table.count(key) > 0)
        {
            value.set_value(table[key]);
        }

        return value;
    }

    bool remove(int key) {
        auto removed = table.erase(key);
        return removed > 0;
    }
};

// insert key and value
// store key and value in in-memory memtable (sorted map)
// make keys unique
// flush map into SSTable on disk
// merge SSTables into LSM
// read from

void parse_command(const std::string & cmd, std::vector<std::string> & tokens) {
    std::string delimiter = " ";
    std::string token;

    size_t start = 0;
    size_t end = 0;
    while ((end = cmd.find(delimiter, start)) != std::string::npos) {
        token = cmd.substr(start, end);
        tokens.push_back(token);
        start = end + delimiter.length();
    }

    token = cmd.substr(start);
    tokens.push_back(token);
}

int main(int argc, char *argv[])
{
    std::string cmd;
    std::vector<std::string> tokens;
    MemTable table;

    std::cout << "Welcome to simpleDB" << std::endl;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, cmd);

        tokens.erase(tokens.begin(), tokens.end());
        parse_command(cmd, tokens);

        if (tokens[0] == "put") {
            int key = std::atoi(tokens[1].c_str());
            int value = std::atoi(tokens[2].c_str());
            table.put(key, value);
        }
        else if(tokens[0] == "get") {
            int key = std::atoi(tokens[1].c_str());
            Value value = table.get(key);
            if (value.has_value()) {
                std::cout << value.value() << std::endl;
            }
            else
            {
                std::cout << "Key not found: " << key << std::endl;
            }
            
        }
        else if(tokens[0] == "delete") {
            int key = std::atoi(tokens[1].c_str());
            int removed = table.remove(key);
            if (removed)
            {
                std::cout << "Removed key: " <<  key << std::endl;
            }
        }
        else if (tokens[0] == "exit") {
            std::cout << "Exiting... Bye!.\n";
            break;
        }
        else {
            std::cout << "Unknown command" << std::endl;
            std::cout << "Please enter command, e.g. 'put 1 10', 'get 1', 'delete 1', 'exit'\n";
        }
    }

    return 0;
}