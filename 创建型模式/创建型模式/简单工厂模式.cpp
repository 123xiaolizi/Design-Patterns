#include <iostream>



// ��Ʒ��ĸ��� - �����ħ��ʵ
class AbstractSmile
{
public:
    virtual void transform() = 0;
    virtual void ability() = 0;
    virtual ~AbstractSmile() {}
};
//��ħ��ʵ-������̬
class SheepSmile : public AbstractSmile
{
public:
    void transform()
    {
        std::cout << "������� -- ɽ������̬..." << std::endl;
    }
    void ability()
    {
        std::cout << "���ֱ۱������ǵ���ʽ -- �����" << std::endl;
    }
};
//��ħ��ʵ-ʨ����̬
class LionSmile : public AbstractSmile
{
public:
    void transform()
    {
        std::cout << "������� -- ʨ������̬..." << std::endl;
    }
    void ability()
    {
        std::cout << "�����---===����������===---" << std::endl;
    }
};
//��ħ��ʵ-������̬
class BatSmile : public AbstractSmile
{
public:
    void transform()
    {
        std::cout << "������� -- ��������̬..." << std::endl;
    }
    void ability()
    {
        std::cout << "��������������" << std::endl;
    }
};

//����һ��ö������ʾ���ֲ�ͬ�Ĺ�ʵ
enum class FruitType:char
{
	SHEEP,
	LION,
	BAT
};

//������
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