#include <iostream>

//The Hash table stores elements in key-value pairs where
//key - unique integer that is used for indexing the values
//value - data that are associated with keys.

#include <unordered_map>    //c++ library for hash tables
#include <vector>
#include <functional>
#include <chrono>   //for timing
#include <thread>   //to control threads

class Command //parent class for all types of commands
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Command1 : public Command 
{
    void execute() override 
    {
        std::cout << "First command.\n\n";
    }
    void undo() override 
    {
        std::cout << "Undo first command.\n";
    }
};

class Command2 : public Command 
{
    void execute() override 
    {
        std::cout << "Second command.\n\n";
    }
    void undo() override 
    {
        std::cout << "Undo second command.\n";
    }
};

class Command3 : public Command 
{
    void execute() override 
    {
        std::cout << "Third command.\n\n";
    }
    void undo() override 
    {
        std::cout << "Undo third command.\n";
    }
};

class VirtualKeyboard 
{
private:
    std::unordered_map<std::string, Command*> keyActions;   //hash table
    std::vector<std::string> traceback;

public:
    using Action = std::function<void()>;

    void pressKey(const std::string& key) 
    {
        if (keyActions.find(key) != keyActions.end()) 
        {
            keyActions[key]->execute();
            traceback.push_back(key);
        }
        else 
        {
            std::cout << "Key is not assigned: " << key << "\n";
        }
    }

    void assignKey(const std::string& key, Command* action) 
    {
        if (keyActions.find(key) != keyActions.end()) 
        {
            delete keyActions[key];
        }
        keyActions[key] = action;
    }

    void undo() 
    {
        if (!traceback.empty())
        {
            std::string lastKey = traceback.back();
            traceback.pop_back();
            if (keyActions.find(lastKey) != keyActions.end()) 
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(600));
                keyActions[lastKey]->undo();
            }
        }
        else 
        {
            std::cout << "Nothing to undo\n\n";
        }
    }


    void runWorkflow(const std::vector<std::string>& keys) 
    {
        for (auto key : keys)
        {
            pressKey(key);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    ~VirtualKeyboard() 
    {
        for (auto item = keyActions.begin(); item != keyActions.end(); item++)    //deleting all commands from the table
        {
            delete item->second;
        }
    }
};



int main() 
{
    VirtualKeyboard keyboard;

    keyboard.assignKey("a", new Command1());
    keyboard.assignKey("b", new Command2());
    keyboard.assignKey("c", new Command3());

    std::vector<std::string> workflow = { "a","b","c" };
    std::cout << "Executing Workflow:\n";
    keyboard.runWorkflow(workflow);

    std::cout << "\nPressing unassigned key '4':\n";
    keyboard.pressKey("4");

    std::cout << "\nUndoing last action:\n\n";
    keyboard.undo();
    keyboard.undo();
    keyboard.undo();

    keyboard.runWorkflow(workflow);

    std::cout << "\nWorkflow with reassigned keys:\n\n";
    keyboard.assignKey("1", new Command1());    //reassigning new keys
    keyboard.assignKey("2", new Command2());
    keyboard.assignKey("3", new Command3());


    workflow = { "1","2","3" };
    std::cout << "\nExecuting Workflow:\n";
    keyboard.runWorkflow(workflow);

    return 0;
}