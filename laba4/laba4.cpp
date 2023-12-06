#include <iostream>
#include <functional>

class INotifyPropertyChanged
{
public:
	virtual void AddPropertyChangedListener(std::function<void()> listener) = 0;
	virtual void RemovePropertyChangedListener(std::function<void()> listener) = 0;
	virtual ~INotifyPropertyChanged() = default;
};

class INotifyPropertyChanging {
public:
	virtual void AddPropertyChangingListener(std::function<void(int index, const std::string&, bool)> listener) = 0;
	virtual void RemovePropertyChangingListener(std::function<void(int index, const std::string&, bool)> listener) = 0;
	virtual ~INotifyPropertyChanging() = default;
};

class INotifyCollectionChanged
{
public:
	enum class CollectionChangedEnum
	{
		Added,
		Removed,
		ItemChanged
	};

	virtual void AddCollectionChangedListener(std::function<void(CollectionChangedEnum)> listener) = 0;
	virtual void RemoveCollectionChangedListener(std::function<void(CollectionChangedEnum)> listener) = 0;
	virtual ~INotifyCollectionChanged() = default;
};

class ObjectWithProperties : public INotifyPropertyChanged, public INotifyPropertyChanging, public INotifyCollectionChanged
{
private:
    std::vector<std::string> objProperty = {"property1"};
    std::vector<int> objCollection;    

    std::vector<std::function<void()>> propertyChangedListeners;
    std::vector<std::function<void(int index, const std::string&, bool)>> propertyChangingListeners;
    std::vector<std::function<void(CollectionChangedEnum)>> collectionChangedListeners;

public:
    virtual ~ObjectWithProperties()
    {
        objProperty.clear();
    }

    void AddPropertyChangedListener(std::function<void()> listener) override {
        propertyChangedListeners.push_back(listener);
    }

    void AddPropertyChangingListener(std::function<void(int index, const std::string&, bool)> listener) override {
        propertyChangingListeners.push_back(listener);
    }

    void AddCollectionChangedListener(std::function<void(CollectionChangedEnum)> listener) override {
        collectionChangedListeners.push_back(listener);
    }

    void RemovePropertyChangedListener(std::function<void()> listener) override {
        propertyChangedListeners.erase(
            std::remove_if(propertyChangedListeners.begin(), propertyChangedListeners.end(),
                [&](const auto& func) 
                {return &func == &listener; }),
            propertyChangedListeners.end());
    }

    void RemovePropertyChangingListener(std::function<void(int index, const std::string&, bool)> listener) override {
        propertyChangingListeners.erase(
            std::remove_if(propertyChangingListeners.begin(), propertyChangingListeners.end(),
                [&](const auto& func) 
                {return &func == &listener; }),
            propertyChangingListeners.end());
    }

    void RemoveCollectionChangedListener(std::function<void(CollectionChangedEnum)> listener) override {
        collectionChangedListeners.erase(
            std::remove_if(collectionChangedListeners.begin(), collectionChangedListeners.end(),
                [&](const auto& func) 
                {return &func == &listener; }),
            collectionChangedListeners.end());
    }

    void addProperty(const std::string newValue) {
        objProperty.push_back(newValue);
        
        for (auto& listener : propertyChangedListeners)
        {
            listener();
        }
        for (auto& listener : propertyChangingListeners)
        {
            listener(objProperty.size(), newValue, 0);
            return;
        }
    }

    //we change a property and then notify the end of changing
    //we need to notify 2 listeners
    void setProperty(const std::string newValue, int itemIndex) {        
        objProperty[itemIndex] = newValue;
        for (auto& listener : propertyChangedListeners) 
        {
            listener();
        }
        for (auto& listener : propertyChangingListeners) 
        {
            listener(itemIndex, newValue, 0);
            return;
        }
    }

    void AddToCollection(int value) {
        objCollection.push_back(value);

        for (auto& listener : collectionChangedListeners) 
        {
            listener(CollectionChangedEnum::Added);
        }
    }

    void ChangeInCollection(int value) {
        objCollection.push_back(value);

        for (auto& listener : collectionChangedListeners)
        {
            listener(CollectionChangedEnum::ItemChanged);
        }
    }

};

int main()
{
    ObjectWithProperties obj;

    //defining the function which listens for a change in property
    auto propertyChangedListener = [&]()
    {
        std::cout << "Property is changing." << "\n";
    };

    //defining the function which tells which property chages
    auto propertyChangingListener = [&](int index, const std::string& newValue, bool cancel)
    {
        std::cout << "Property changing: Property" << index + 1 << " to " << newValue << "\n";
        std::cout << "Property stopped changing" << "\n";
    };

    //defining the function which informs of states of items in collection
    auto collectionChangedListener = [&](INotifyCollectionChanged::CollectionChangedEnum status)
    {
        std::cout << "Collection changed: ";
        switch (status)
        {
        case INotifyCollectionChanged::CollectionChangedEnum::Added:
            std::cout << "Item has been added.";
            break;
        case INotifyCollectionChanged::CollectionChangedEnum::Removed:
            std::cout << "Item has been removed.";
            break;
        case INotifyCollectionChanged::CollectionChangedEnum::ItemChanged:
            std::cout << "Item has changed.";
            break;
        }
        std::cout << "\n";
    };

    obj.AddPropertyChangedListener(propertyChangedListener);
    obj.AddPropertyChangingListener(propertyChangingListener);
    obj.AddCollectionChangedListener(collectionChangedListener);

    int value;

    obj.addProperty("property2");    
    std::cout << "Enter a value for a new property: ";
    std::cin >> value;
    obj.AddToCollection(value);

    obj.setProperty("value", 0);
    std::cout << "Enter a value for an old property: ";
    std::cin >> value;
    obj.ChangeInCollection(value);

    obj.RemovePropertyChangedListener(propertyChangedListener);
    obj.RemovePropertyChangingListener(propertyChangingListener);
    obj.RemoveCollectionChangedListener(collectionChangedListener);
    obj.~ObjectWithProperties();
    return 0;
}


