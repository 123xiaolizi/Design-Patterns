#include <iostream>
#include <vector>
#include <string>
#include <map>
class SunnyShip
{
public:
	//添加部件
	void addpart(std::string name)
	{
		m_parts.push_back(name);
	}
	//展示各个部件
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
	//添加部件
	void addpart(std::string name, std::string part)
	{
		m_parts.insert(std::make_pair(name, part));
	}
	//展示各个部件
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


//抽象生成器
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


// 桑尼号生成器
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
    // 提供重置函数, 目的是能够使用生成器对象生成多个产品
    void reset() override
    {
        m_sunny = new SunnyShip;
    }
    void buildBody() override
    {
        m_sunny->addpart("神树亚当的树干");
    }
    void buildWeapon() override
    {
        m_sunny->addpart("狮吼炮");
    }
    void buildEngine() override
    {
        m_sunny->addpart("可乐驱动");
    }
    void buildInterior() override
    {
        m_sunny->addpart("豪华内室精装");
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


// 梅丽号生成器
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
    // 提供重置函数, 目的是能够使用生成器对象生成多个产品
    void reset() override
    {
        m_merry = new MerryShip;
    }
    void buildBody() override
    {
        m_merry->addpart("船体","优质木材");
    }
    void buildWeapon() override
    {
        m_merry->addpart("武器","四门大炮");
    }
    void buildEngine() override
    {
        m_merry->addpart("动力","蒸汽机");
    }
    void buildInterior() override
    {
        m_merry->addpart("内饰", "精装内饰");
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

//主管类 ---- 不是必要
class Director
{
public:
    void setBuilder(ShipBuilder* builder)
    {
        m_builder = builder;
    }
    // 简约型
    void builderSimpleShip()
    {
        m_builder->buildBody();
        m_builder->buildEngine();
    }
    // 标准型
    void builderStandardShip()
    {
        builderSimpleShip();
        m_builder->buildWeapon();
    }
    // 豪华型
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
    //简约型
    director->builderSimpleShip();
    MerryShip* merryship = merrybuilder->getMerry();
    merryship->showparts();

    //豪华型
    merrybuilder->reset();
    director->builderStandardShip();
    merryship = merrybuilder->getMerry();
    merryship->showparts();
    delete merrybuilder;
    delete director;
    return 0;

}
#endif