#include <iostream>



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

//定于一个枚举来表示各种不同的果实
enum class FruitType:char
{
	SHEEP,
	LION,
	BAT
};

//工厂类
class SmileFactory
{
public:
    AbstractSmile* createSmile(FruitType type)
    {
        //AbstractSmile* ptr;
        switch (type)
        {
        case FruitType::SHEEP:
            return new SheepSmile();
            break;
        case FruitType::LION:
            return new LionSmile();
            break;
        case FruitType::BAT:
            return new BatSmile();
            break;
        default:
            break;
        }
    }
};

#if 0
int main(char* agrc, char** agrv)
{
    SmileFactory* Factory = new SmileFactory();
    AbstractSmile* Sheep = Factory->createSmile(FruitType::SHEEP);
    Sheep->transform();
    Sheep->ability();
    AbstractSmile* Lion = Factory->createSmile(FruitType::LION);
    Lion->transform();
    Lion->ability();
    AbstractSmile* Bat = Factory->createSmile(FruitType::BAT);
    Bat->transform();
    Bat->ability();

    delete Factory;
    delete Sheep;
    delete Lion;
    delete Bat;
    return 0;
}
#endif