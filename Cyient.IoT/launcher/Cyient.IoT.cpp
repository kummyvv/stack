//============================================================================
// Name        : IoT.cpp
// Author      : Cyient
// Version     :
// Copyright   : Authorized only for Cyient
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
using namespace std;


class BaseClass{
public:
    virtual int funk() {
        return 0;
    }
};

class i2c : public BaseClass
{
private:
    static short ID;
    virtual int funk() {

        return 42;
    }

public:
    i2c(){};
    virtual ~i2c(){};
};



class gpio : public BaseClass
{
private:
    static short ID;
    virtual int funk() {

        return 63;
    }

public:
    gpio(){};
    virtual ~gpio(){};
};

template<typename Type> BaseClass* createType() {
    cout << "creating type \n";
    return new Type;
}

class TemplatedFactory
{
public:
    typedef BaseClass* (*ComponentFactoryFuncPtr)();
    typedef map<const char*, ComponentFactoryFuncPtr> map_type;

    map_type m_Map;

public:


    template<typename Type>
    short AddType(const char* componentName){
          ComponentFactoryFuncPtr function = &createType<Type>;
        m_Map.insert(std::make_pair(componentName, function));

    return 0;
    };
};




int main(int argc, char ** argv)
{

    TemplatedFactory * factory_p = new TemplatedFactory();
    factory_p->AddType<i2c>("i2c");
    factory_p->AddType<gpio>("gpio");

    cout << "Done registering\n";

    TemplatedFactory::map_type::iterator iterA = factory_p->m_Map.find("i2c");
    TemplatedFactory::map_type::iterator iterB = factory_p->m_Map.find("gpio");
    cout << "i2c: " << iterA->second()->funk() << "\n";
    cout << "gpio: " << iterB->second()->funk() << "\n";
    return 0;
}
