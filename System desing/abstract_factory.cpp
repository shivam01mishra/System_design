#include<iostream>
#include<string>
#include<memory>
using namespace std;
class Icar {
public:
	virtual void run() = 0;
};

class hondacar :public Icar {
	void run() {
		cout << "honda car running\n";
	}
};

class suzukicar :public Icar {
	void run() {
		cout << "suzukiCar car running\n";
	}
};

class Ibike {
public:
	virtual void run() = 0;
};

class hondabike :public Ibike{
	void run() {
		cout << "honda bike running\n";
	}
};

class suzukibike :public Ibike {
	void run() {
		cout << "suzukiCar bike running\n";
	}
};

class Ifactory {
public:
	virtual unique_ptr<Icar>create_car() = 0;
	virtual unique_ptr<Ibike>create_bike() = 0;
};


class honda_factory :public Ifactory
{ public:
	unique_ptr<Icar> create_car()
	{
		return make_unique<hondacar>();
	}
	unique_ptr<Ibike> create_bike()
	{
		return make_unique<hondabike>();
	}
};

class suzuki_factory :public Ifactory
{public:
	unique_ptr<Icar> create_car()
	{
		return make_unique<suzukicar>();
	}
	unique_ptr<Ibike> create_bike()
	{
		return make_unique<suzukibike>();
	}
};


class factory_creater{
public: 
static unique_ptr<Ifactory> create_factory(const string& type) {
	if (type == "suzuki") return make_unique<suzuki_factory>();

	else return make_unique<honda_factory>();
}
};







int main() {
	unique_ptr < Ifactory > factory= factory_creater::create_factory("honda");
	unique_ptr<Icar>car = factory->create_car();
	unique_ptr<Ibike>bike = factory->create_bike();
	bike->run();
	car->run();


}