#include <iostream>

//工厂模式解决了简单工厂模式中违背了开放封闭原则

// 产品类的父类 - 人造恶魔果实
class AbstractSmile
{
public:
    virtual void transform() = 0;
    virtual void ability() = 0;
    virtual ~AbstractSmile() {}
};
//恶魔果实-绵羊形态
class SheepSmile : public AbstractSmile
{
public:
    void transform()
    {
        std::cout << "变成人兽 -- 山羊人形态..." << std::endl;
    }
    void ability()
    {
        std::cout << "将手臂变成绵羊角的招式 -- 巨羊角" << std::endl;
    }
};
//恶魔果实-狮子形态
class LionSmile : public AbstractSmile
{
public:
    void transform()
    {
        std::cout << "变成人兽 -- 狮子人形态..." << std::endl;
    }
    void ability()
    {
        std::cout << "会喷火---===三三三二二===---" << std::endl;
    }
};
//恶魔果实-蝙蝠形态
class BatSmile : public AbstractSmile
{
public:
    void transform()
    {
        std::cout << "变成人兽 -- 蝙蝠人形态..." << std::endl;
    }
    void ability()
    {
        std::cout << "音波攻击哔哔哔" << std::endl;
    }
};
//工厂基类
class AbstractFactory
{
public:
    virtual AbstractSmile* createSmile() = 0;
    virtual ~AbstractFactory() {}
};
//山羊恶魔果实工厂
class SheepFactory : public AbstractFactory
{
public:
    AbstractSmile* createSmile()
	{
		return new SheepSmile();
	}
};
//狮子恶魔果实工厂
class LionFactory : public AbstractFactory
{
public:
	AbstractSmile* createSmile()
	{
		return new LionSmile();
	}
};
//蝙蝠恶魔果实工厂
class BatFactory : public AbstractFactory
{
public:
	AbstractSmile* createSmile()
	{
		return new BatSmile();
	}
};

#if 0
int main(char* agrc, char** agrv)
{
    AbstractFactory* factory = new SheepFactory();
	AbstractSmile* sheep_smile = factory->createSmile();
    sheep_smile->transform();
    sheep_smile->ability();
	delete sheep_smile;
	delete factory;

    AbstractFactory* lion_factory = new LionFactory();
    AbstractSmile* lion_smile = lion_factory->createSmile();
    lion_smile->transform();
    lion_smile->ability();
    delete lion_smile;
    delete lion_factory;

    return 0;
}
#endif