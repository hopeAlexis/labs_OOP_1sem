//#include <iostream>
//#include <memory>
//
//
//// Базовый класс для контролов
//class Control {
//public:
//    virtual void setPosition(int x, int y) = 0;
//    virtual std::pair<int, int> getPosition() const = 0;
//    virtual void setText(const std::string& text) = 0;
//    virtual std::string getText() = 0;
//    virtual ~Control() = default;
//};
//
//// Классы контролов
//class Form : public Control {
//public:
//    void setPosition(int x, int y) override
//    {
//        std::cout << "Form: setPosition at (" << x << ", " << y << ")" << std::endl;
//    }
//    std::pair<int, int> getPosition() const override
//    {
//        return { 0, 0 };
//    }
//    void setText(const std::string& text) override
//    {
//        std::cout << "Установка текста для формы " << text << std::endl;
//    }
//    std::string getText() override
//    {
//        std::cout << "Вызван метод возрата текста формы у контролла" << std::endl;
//    }
//};
//
//class Label : public Control {
//public:
//    void setPosition(int x, int y) override
//    {
//        std::cout << "Label: setPosition at (" << x << ", " << y << ")" << std::endl;
//    }
//    std::pair<int, int> getPosition() const override
//    {
//        return { 0, 0 };
//    }
//    void setText(const std::string& text) override
//    {
//        std::cout << "Label: setText - \"" << text << "\"" << std::endl;
//    }
//    std::string getText() override {
//        return "Sample Text";
//    }
//};
//
//// Абстрактная фабрика для создания контролов
//class ControlFactory {
//public:
//    virtual std::unique_ptr<Control> createForm() = 0;
//    virtual std::unique_ptr<Control> createLabel() = 0;
//    virtual ~ControlFactory() = default;
//};
//
//// Фабрики для различных операционных систем
//class WindowsControlFactory : public ControlFactory {
//public:
//    std::unique_ptr<Control> createForm() override
//    {
//        return std::make_unique<Form>();
//    }
//    std::unique_ptr<Control> createLabel() override
//    {
//        return std::make_unique<Label>();
//    }
//};
//
//class LinuxControlFactory : public ControlFactory {
//public:
//    std::unique_ptr<Control> createForm() override
//    {
//        return std::make_unique<Form>();
//    }
//    std::unique_ptr<Control> createLabel() override
//    {
//        return std::make_unique<Label>();
//    }
//};
//
//class MacOSControlFactory : public ControlFactory {
//public:
//    std::unique_ptr<Control> createForm() override
//    {
//        return std::make_unique<Form>();
//    }
//    std::unique_ptr<Control> createLabel() override
//    {
//        return std::make_unique<Label>();
//    }
//};
//
//int main() {
//
//    system("chcp 65001");
//    std::string os = "MacOS";
//    std::unique_ptr<ControlFactory> factory;
//    if (os == "Windows")
//    {
//        factory = std::make_unique<WindowsControlFactory>();
//    }
//    else if (os == "Linux")
//    {
//        factory = std::make_unique<LinuxControlFactory>();
//    }
//    else if (os == "MacOS")
//    {
//        factory = std::make_unique<MacOSControlFactory>();
//    }
//    if (factory)
//    {
//        auto form = factory->createForm();
//        auto label = factory->createLabel();
//        form->setPosition(100, 50);
//        form->setText("Hi");
//        auto position = label->getPosition();
//        std::cout << "Label position: (" << position.first << ", " << position.second << ")" << std::endl;
//        label->setText("Hello, World!");
//        auto text = label->getText();
//        std::cout << "Label text: " << text << std::endl;
//    }
//    return 0;
//}


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