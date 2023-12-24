#include <iostream>

//The Hash table stores elements in key-value pairs where
//key - unique integer that is used for indexing the values
//value - data that are associated with keys.

#include <unordered_map>    //c++ library for hash tables
#include <vector>
#include <functional>
#include <chrono>   //for timing
#include <thread>   //to control threads

class VirtualKeyboard 
{
private: 
    std::unordered_map<char, std::function<void()>> keyToOperations;
    std::vector<char> traceback;
public:    
    
    void assignKey(char key, std::function<void()> operation)
    {
        keyToOperations[key] = operation;
    }

    void pressKey(char key) 
    {
        if (keyToOperations.find(key) != keyToOperations.end()) 
        {
            keyToOperations[key]();
            traceback.push_back(key);
        }
        else 
        {
            std::cout << "'" << key << "' key is unavailable.\n";
        }
    }

    void undo() 
    {
        if (!traceback.empty()) 
        {
            char lastKeyPressed = traceback.back();    //last element in the vector
            traceback.pop_back();
            std::cout << "Undone the '" << lastKeyPressed << "' key.\n";
        }
        else 
        {
            std::cout << "No keys to undo!\n";
        }
    }

    void workflow(const std::vector<char>& keys) 
    {
        std::cout << "Workflow:\n";
        for (int i = 0; i < keys.size(); i++) 
        {
            pressKey(keys[i]);
            std::this_thread::sleep_for(std::chrono::milliseconds(600)); // to create key pressing delay
        }
    }

    std::vector<char> getTraceback() const
    {
        return traceback;
    }
};

void operationQ() 
{
    std::cout << "Pressed Q key. Q operation happened.\n";
}

void operationW() 
{
    std::cout << "Pressed W key. W operation happened.\n";
}

void operationE() 
{
    std::cout << "Pressed E key. E operation happened.\n";
}

void operationR() 
{
    std::cout << "Pressed R key. R operation happened.\n";
}

void operationT() 
{
    std::cout << "Pressed T key. T operation happened.\n";
}

void operationY() 
{
    std::cout << "Pressed Y key. Y operation happened.\n";
}

int main() 
{
    VirtualKeyboard keyboard;

    keyboard.assignKey('q', operationQ);
    keyboard.assignKey('w', operationW);
    keyboard.assignKey('e', operationE);
    keyboard.assignKey('r', operationR);
    keyboard.assignKey('t', operationT);
    keyboard.assignKey('y', operationY);

    std::vector<char> workflow = { 'q', 'w', 'e', 'r', 't', 'y'};
    keyboard.workflow(workflow);

    std::cout << "\nPressing 'u':\n";
    keyboard.pressKey('u');

    std::cout << "\nUndoing last action:\n";
    keyboard.undo();

    std::cout << "\nUpdated Workflow:\n";
    keyboard.workflow(keyboard.getTraceback());

    return 0;
}