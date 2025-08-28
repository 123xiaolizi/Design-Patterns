#include <iostream>
#include <vector>
#include <string>
#include <map>
class SunnyShip
{
public:
	//��Ӳ���
	void addpart(std::string name)
	{
		m_parts.push_back(name);
	}
	//չʾ��������
	void showparts()
	{
		for (const auto &it : m_parts)
		{
			std::cout << it << " " << std::endl;
		}
		std::cout << std::endl;
	}

private:
	std::vector<std::string> m_parts;
};

class MerryShip
{
public:
	//��Ӳ���
	void addpart(std::string name, std::string part)
	{
		m_parts.insert(std::make_pair(name, part));
	}
	//չʾ��������
	void showparts()
	{
		for (const auto &it : m_parts)
		{
			std::cout << it.first <<it.second << std::endl;
		}
		std::cout << std::endl;
	}

private:
	std::map<std::string, std::string> m_parts;
};


//����������
class ShipBuilder
{
public:
	virtual void reset() = 0;
	virtual void buildBody() = 0;
	virtual void buildWeapon() = 0;
	virtual void buildEngine() = 0;
	virtual void buildInterior() = 0;
	virtual ~ShipBuilder() {}
};


// ɣ���������
class SunnyBuilder : public ShipBuilder
{
public:
    SunnyBuilder()
    {
        reset();
    }
    ~SunnyBuilder()
    {
        if (m_sunny != nullptr)
        {
            delete m_sunny;
        }
    }
    // �ṩ���ú���, Ŀ�����ܹ�ʹ���������������ɶ����Ʒ
    void reset() override
    {
        m_sunny = new SunnyShip;
    }
    void buildBody() override
    {
        m_sunny->addpart("�����ǵ�������");
    }
    void buildWeapon() override
    {
        m_sunny->addpart("ʨ����");
    }
    void buildEngine() override
    {
        m_sunny->addpart("��������");
    }
    void buildInterior() override
    {
        m_sunny->addpart("�������Ҿ�װ");
    }
    SunnyShip* getSunny()
    {
        SunnyShip* ship = m_sunny;
        m_sunny = nullptr;
        return ship;
    }
private:
    SunnyShip* m_sunny = nullptr;
};


// ÷����������
class MerryBuilder : public ShipBuilder
{
public:
    MerryBuilder()
    {
        reset();
    }
    ~MerryBuilder()
    {
        if (m_merry != nullptr)
        {
            delete m_merry;
        }
    }
    // �ṩ���ú���, Ŀ�����ܹ�ʹ���������������ɶ����Ʒ
    void reset() override
    {
        m_merry = new MerryShip;
    }
    void buildBody() override
    {
        m_merry->addpart("����","����ľ��");
    }
    void buildWeapon() override
    {
        m_merry->addpart("����","���Ŵ���");
    }
    void buildEngine() override
    {
        m_merry->addpart("����","������");
    }
    void buildInterior() override
    {
        m_merry->addpart("����", "��װ����");
    }
    MerryShip* getMerry()
    {
        MerryShip* ship = m_merry;
        m_merry = nullptr;
        return ship;
    }
private:
    MerryShip* m_merry = nullptr;
};

//������ ---- ���Ǳ�Ҫ
class Director
{
public:
    void setBuilder(ShipBuilder* builder)
    {
        m_builder = builder;
    }
    // ��Լ��
    void builderSimpleShip()
    {
        m_builder->buildBody();
        m_builder->buildEngine();
    }
    // ��׼��
    void builderStandardShip()
    {
        builderSimpleShip();
        m_builder->buildWeapon();
    }
    // ������
    void builderRegalShip()
    {
        builderStandardShip();
        m_builder->buildInterior();
    }
private:
    ShipBuilder* m_builder = nullptr;
};

#if 0
int main()
{
    MerryBuilder* merrybuilder = new MerryBuilder();
    Director* director = new Director();
    director->setBuilder(merrybuilder);
    //��Լ��
    director->builderSimpleShip();
    MerryShip* merryship = merrybuilder->getMerry();
    merryship->showparts();

    //������
    merrybuilder->reset();
    director->builderStandardShip();
    merryship = merrybuilder->getMerry();
    merryship->showparts();
    delete merrybuilder;
    delete director;
    return 0;

}
#endif