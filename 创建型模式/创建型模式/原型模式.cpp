/*	克隆可能会在父类和子类之间进行，并且可能是动态的，
	很明显通过父类的拷贝构造函数无法实现对子类对象的拷贝，
	其实这就是一个多态，我们需要给父类提供一个克隆函数并且是一个虚函数
*/


#include <iostream>
using namespace std;

class GermaSoldier
{
public:
    virtual GermaSoldier* clone() = 0;
    virtual string whoAmI() = 0;
    virtual ~GermaSoldier() {}
};

class Soldier66 : public GermaSoldier
{
public:
    //要注意深浅拷贝问题，这里使用的是浅拷贝，因为没有数据成员，所以无所谓
    GermaSoldier* clone() override
    {
        return new Soldier66(*this);
    }
    string whoAmI() override
    {
        return string("我是杰尔马66的超级士兵!!!");
    }
};

class Soldier67 : public GermaSoldier
{
public:
    GermaSoldier* clone()
    {
        return new Soldier67(*this);
    }
    string whoAmI() override
    {
        return string("我是杰尔马67的超级士兵!!!");
    }
};

int main()
{
    GermaSoldier* obj = new Soldier66;
    GermaSoldier* soldier = obj->clone();
    cout << soldier->whoAmI() << endl;
    delete soldier;
    delete obj;

    obj = new Soldier67;
    soldier = obj->clone();
    cout << soldier->whoAmI() << endl;
    delete soldier;
    delete obj;
}

