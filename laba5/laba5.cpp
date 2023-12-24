#include <iostream>
#include <vector>

class Control {
public:
    virtual void setPosition(int x, int y) = 0;
    virtual std::pair<int, int> getPosition() const = 0;    //std::pair allows us to pair to integers together
    virtual ~Control() = default;
};

class Form : public Control {
public:
    void setPosition(int x, int y) override {
        std::cout << "setPosition of Form\n";
    }

    std::pair<int, int> getPosition() const override {
        std::cout << "getPosition of Form\n";
        return std::make_pair(0, 0);
    }

    void addControl(Control* control) {
        std::cout << "addControl of Form\n";
    }
};

class Label : public Control {
public:
    void setPosition(int x, int y) override {
        std::cout << "setPosition of Label\n";
    }

    std::pair<int, int> getPosition() const override {
        std::cout << "getPosition of Label\n";
        return std::make_pair(0, 0);
    }

    void setText(const std::string& text) {
        std::cout << "setText  Label\n";
    }

    std::string getText() const {
        std::cout << "getText  Label\n";
        return "";
    }
};

class TextBox : public Control {
public:
    void setPosition(int x, int y) override {
        std::cout << "setPosition of TextBox\n";
    }

    std::pair<int, int> getPosition() const override {
        std::cout << "getPosition of TextBox\n";
        return std::make_pair(0, 0);
    }

    void setText(const std::string& text) {
        std::cout << "setText of TextBox\n";
    }

    std::string getText() const {
        std::cout << "getText of TextBox\n";
        return "";
    }
};

class Button : public Control {
public:
    void setPosition(int x, int y) override {
        std::cout << "setPosition of Button\n";
    }

    std::pair<int, int> getPosition() const override {
        std::cout << "getPosition of Button\n";
        return std::make_pair(0, 0);
    }

    void setTxt(const std::string& text) {
        std::cout << "setTxt of Button\n";
    }

    std::string getText() const {
        std::cout << "getText of Button\n";
        return "";
    }

    void Click() {
        std::cout << "Click of Button\n";
    }
};

class AbstractFactory {
public:
    virtual Form* createForm() = 0;
    virtual Label* createLabel() = 0;
    virtual TextBox* createTextBox() = 0;
    virtual Button* createButton() = 0;
};

class WindowsFactory : public AbstractFactory {
public:
    Form* createForm() override {
        return new Form();
    }

    Label* createLabel() override {
        return new Label();
    }

    TextBox* createTextBox() override {
        return new TextBox();
    }

    Button* createButton() override {
        return new Button();
    }
};

class LinuxFactory : public AbstractFactory {
public:
    Form* createForm() override {
        return new Form();
    }

    Label* createLabel() override {
        return new Label();
    }

    TextBox* createTextBox() override {
        return new TextBox();
    }

    Button* createButton() override {
        return new Button();
    }
};

class MacOSFactory : public AbstractFactory {
public:
    Form* createForm() override {
        return new Form();
    }

    Label* createLabel() override {
        return new Label();
    }

    TextBox* createTextBox() override {
        return new TextBox();
    }

    Button* createButton() override {
        return new Button();
    }
};

int main() {
    AbstractFactory* factory = nullptr;
    std::string os;

    std::cout << "Enter your OS: ";
    std::cin >> os;

    if (os == "Windows") {
        factory = new WindowsFactory();
    }
    else if (os == "Linux") {
        factory = new LinuxFactory();
    }
    else if (os == "MacOS") {
        factory = new MacOSFactory();
    }
    else {
        std::cout << "This OS is unavailable.\n";
        return 0;
    }

    Form* form = factory->createForm();
    Label* label = factory->createLabel();
    TextBox* textBox = factory->createTextBox();
    Button* button = factory->createButton();

    form->setPosition(500, 500);
    label->setPosition(0, 0);
    label->setText("label text");
    textBox->setPosition(100, 100);
    textBox->setText("text");
    button->setPosition(100, 100);
    button->setTxt("click button");

    delete form;
    delete label;
    delete textBox;
    delete button;
    delete factory;

    return 0;
}