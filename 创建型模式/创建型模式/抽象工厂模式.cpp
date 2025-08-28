/*
当你发现代码中出现以下情况时，就应该考虑使用抽象工厂模式：
1.存在多个产品族​​：你的系统需要支持多套不同的配置或风格（如不同平台、不同主题、不同数据库）。
2.存在约束关系​​：这些产品必须成组使用，不能混搭。
3.大量硬编码的 new和 if/else​​：你的代码中充满了针对具体类的实例化操作，并且需要根据条件来判断创建哪种对象。
4.需要隐藏创建逻辑​​：你希望将对象的创建过程与使用过程解耦，让客户端代码只依赖于接口。
与简单工厂、工厂方法模式的区别
​​简单工厂​​：一个工厂类，通过传入的参数不同，来创建​​不同类​​的产品（通常不是产品族）。它不属于 GoF 23 种设计模式，更像一种编程习惯。
​​工厂方法​​：针对​​一种​​产品，定义一个创建接口，让子类决定实例化哪一个类。是 ​​“类的”​​ 延迟实例化。
​​抽象工厂​​：针对​​一系列​​相关产品（产品族），定义一个创建接口，让子类决定实例化哪一族产品。是 ​​“族的”​​ 延迟实例化。抽象工厂内部常常会使用工厂方法来实现。
*/

#include <iostream>
#include <string>
//船体-------------------------------------------------------------------------------------------------------
class Abstract_ShipBody
{
public:
	virtual std::string getShipBody() = 0;
	virtual ~Abstract_ShipBody() {}
};
//木头船体
class WoodBody : public Abstract_ShipBody
{
public:
	std::string getShipBody() override
	{
		return "木头做的船体！！！";
	}
};
//钢铁船体
class IronBody : public Abstract_ShipBody
{
public:
	std::string getShipBody() override
	{
		return "钢铁做的船体！！！";
	}
};
//合成金属船体
class MetalBody : public Abstract_ShipBody
{
public:
	std::string getShipBody() override
	{
		return "合成金属做的船体！！！";
	}
};
//动力-------------------------------------------------------------------------------------------------------

//动力基类
class Abstract_Engine
{
public:
	virtual std::string getEngine() = 0;
	virtual ~Abstract_Engine(){}
};
//人力
class Human : public Abstract_Engine
{
public:
	std::string getEngine() override
	{
		return std::string("使用<人力驱动>...");
	}
};
//蒸汽
class Diesel : public Abstract_Engine
{
public:
	std::string getEngine() override
	{
		return std::string("使用<蒸汽驱动>...");
	}
};
//核动力
class Nuclear : public Abstract_Engine
{
public:
	std::string getEngine() override
	{
		return std::string("使用<核动力驱动>...");
	}
};

//武器-------------------------------------------------------------------------------------------------------

//武器基类
class Abstract_Weapon
{
public:
	virtual std::string getWeapon() = 0;
	virtual ~Abstract_Weapon() {}
};

class Gun : public Abstract_Weapon
{
public:
	std::string getWeapon() override
	{
		return std::string("配备的武器是<枪>...");
	}
};

class Cannon : public Abstract_Weapon
{
public:
	std::string getWeapon() override
	{
		return std::string("配备的武器是<自动机关炮>...");
	}
};

class Laser : public Abstract_Weapon
{
public:
	std::string getWeapon() override
	{
		return std::string("配备的武器是<激光>...");
	}
};

//整船类
class Ship
{
public:
	Ship(Abstract_Engine* engine, Abstract_ShipBody* body, Abstract_Weapon* weapon):
		m_body(body), m_engine(engine), m_weapon(weapon){ }
	void ShowDisposition()
	{
		std::cout << m_body->getShipBody() << m_engine->getEngine() << m_weapon->getWeapon() << std::endl;
	}
	~Ship()
	{
		delete m_body;
		delete m_engine;
		delete m_weapon;
	}
private:
	Abstract_Engine* m_engine;
	Abstract_ShipBody* m_body;
	Abstract_Weapon* m_weapon;
};

//工厂类------------------------------------------------------------------------------------------
class Abstract_Factory
{
public:
	virtual Ship* createShip() = 0;
	virtual ~Abstract_Factory() {}
	
};

class BasicFactory : public Abstract_Factory
{
public:
	Ship* createShip() override
	{
		Ship* ship = new Ship(new Human(), new WoodBody(), new Gun());
		std::cout << "基础版海贼船竣工！！！" << std::endl;
		return ship;
	}
	
};

class StandardFactory : public Abstract_Factory
{
public:
	Ship* createShip() override
	{
		Ship* ship = new Ship(new Diesel(), new IronBody(), new Cannon());
		std::cout << "标准版海贼船竣工！！！" << std::endl;
		return ship;
	}

};

class UltimateFactory : public Abstract_Factory
{
public:
	Ship* createShip() override
	{
		Ship* ship = new Ship(new Nuclear(), new MetalBody(), new Laser());
		std::cout << "旗舰海贼船竣工！！！" << std::endl;
		return ship;
	}

};

#if 0
int main()
{
	Abstract_Factory* ultimatefactory = new UltimateFactory();
	Ship* ultiship = ultimatefactory->createShip();
	ultiship->ShowDisposition();

	delete ultimatefactory;
	delete ultiship;

	Abstract_Factory* basicfactory = new BasicFactory();
	Ship* basicship = basicfactory->createShip();
	basicship->ShowDisposition();

	delete basicfactory;
	delete basicship;

	Abstract_Factory* standarfactory = new StandardFactory();
	Ship* standarship = standarfactory->createShip();
	standarship->ShowDisposition();

	delete standarfactory;
	delete standarship;
	return 0;
}
#endif
