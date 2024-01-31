#include <iostream>
#include <vector>
#include <string>

template <class T>
class IRepository   //1. Template UI
{
public:
    virtual void Add(T* item) {};
    virtual void Update(T* item) {};
    virtual void Delete(T* item) {};
    std::vector<T*> Get(const std::string& where, const std::string& orderBy) {};
};

enum Gender
{
    Male,
    Female
};

class User  //2. User class
{
private:
    int mid;
    std::string mName;
    std::string mEmail;
    std::string mPhone;
    std::string mCity;
    Gender mGender;
public:
    //--------------------------------------getters 
    int getId() const 
    {
        return mid; 
    }
    std::string getName() const 
    {
        return mName; 
    }
    std::string getEmail() const 
    {
        return mEmail; 
    }
    std::string getPhone() const 
    {
        return mPhone; 
    }
    std::string getCity() const 
    {
        return mCity; 
    }
    Gender getGender() const 
    {
        return mGender; 
    }
    //--------------------------------------setters
    void setId(int id) 
    {
        mid = id; 
    }
    void setName(const std::string name) 
    {
        mName = name; 
    }
    void setEmail(const std::string email) 
    {
        mEmail = email; 
    }
    void setPhone(const std::string phone) 
    {
        mPhone = phone; 
    }
    void setCity(const std::string city) 
    {
        mCity = city; 
    }
    void setGender(Gender Gender) 
    {
        mGender = Gender; 
    }
};

class IUserRepository   //3. User repository UI
{
public:
    virtual User* getById(int id) = 0;
    virtual User* getByName(const std::string name) = 0;
    virtual User* getByEmail(const std::string email) = 0;
    virtual std::vector<User*> getByCity(const std::string city) = 0;
    virtual std::vector<User*> getByGender(Gender Gender) = 0;
};

template <class T>
class MemoryRepository : public virtual IRepository<T>  //4. Class for RAM operations with objects
{
protected:
    std::vector<T*> mObjects;
public:
    void Add(T* object) override
    {
        mObjects.push_back(object);
    }

    void Update(T* object) override
    {
        for (int i = 0; i < mObjects.size(); i++)
        {
            if (mObjects[i] == object)
            {
                mObjects[i] = object;
                break;
            }
        }
    }

    void Delete(T* object) override
    {
        for (int i = 0; i < mObjects.size(); i++)
        {
            if (mObjects[i] == object)
            {
                mObjects.erase(mObjects.begin() + i);
                break;
            }
        }
    }

    std::vector<T*> Get()
    {
        return mObjects;
    }
};

class MemoryUserRepository : public MemoryRepository<User>, public IUserRepository  //5. Class for RAM operations with User objects
{
public:
    User* getById(int id) override 
    {
        for (User* user : mObjects) 
        {
            if (user->getId() == id) 
            {
                return user;
            }
        }
        return nullptr;  //if no such id
    }

    User* getByName(const std::string name) override 
    {
        for (User* user : mObjects) 
        {
            if (user->getName() == name) 
            {
                return user;
            }
        }
        return nullptr;  //if no such name
    }

    User* getByEmail(const std::string email) override 
    {
        for (User* user : mObjects) 
        {
            if (user->getEmail() == email) 
            {
                return user;
            }
        }
        return nullptr; //if no such email
    }

    std::vector<User*> getByCity(const std::string city) override
    {
        std::vector<User*> result;
        for (User* user : mObjects)
        {
            if (user->getCity() == city)
            {
                result.push_back(user);
            }
        }
        return result;
    }

    std::vector<User*> getByGender(Gender Gender) override
    {
        std::vector<User*> result;
        for (User* user : mObjects)
        {
            if (user->getGender() == Gender)
            {
                result.push_back(user);
            }
        }
        return result; 
    }
};

int main() 
{
    //establish repository for working with objects
    MemoryUserRepository repository;

    //create users
    User* user1 = new User();
    user1->setId(1591);
    user1->setName("Romeo");
    user1->setEmail("RomeoMontague@olditaly.com");
    user1->setPhone("264872648");
    user1->setCity("Verona");
    user1->setGender(Male);

    User* user2 = new User();
    user2->setId(1592);
    user2->setName("Juliet");
    user2->setEmail("JulietCapulet@olditaly.com");
    user2->setPhone("141424255");
    user2->setCity("Verona");
    user2->setGender(Female);

    //add those users to repository
    repository.Add(user1);
    repository.Add(user2);

    std::vector<User*> users = repository.Get();

    std::cout << "Users in repository:\n";
    for (User* user : users) 
    {
        std::cout << user->getId() << " " 
        << user->getName() << " "
        << user->getEmail() << " " 
        << user->getPhone() << " "
        << user->getCity() << " "
        << user->getGender() << "\n";
    }

    user2->setName("Rosaline");
    repository.Delete(user1);

    users = repository.Get();

    std::cout << "Users in repository:\n";
    for (User* user : users)
    {
        std::cout << user->getId() << " "
            << user->getName() << " "
            << user->getEmail() << " "
            << user->getPhone() << " "
            << user->getCity() << " "
            << user->getGender() << "\n";
    }

}