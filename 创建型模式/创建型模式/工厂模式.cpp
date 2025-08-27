#include <iostream>

//����ģʽ����˼򵥹���ģʽ��Υ���˿��ŷ��ԭ��

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
//��������
class AbstractFactory
{
public:
    virtual AbstractSmile* createSmile() = 0;
    virtual ~AbstractFactory() {}
};
//ɽ���ħ��ʵ����
class SheepFactory : public AbstractFactory
{
public:
    AbstractSmile* createSmile()
	{
		return new SheepSmile();
	}
};
//ʨ�Ӷ�ħ��ʵ����
class LionFactory : public AbstractFactory
{
public:
	AbstractSmile* createSmile()
	{
		return new LionSmile();
	}
};
//�����ħ��ʵ����
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