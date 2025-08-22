#include <iostream>
#include <string>
#include<memory>
using namespace std;

class Icar {
public:
	virtual void run_car() = 0;
};

class NormalCar : public Icar {
public:
	void run_car() {
		cout << "Normal car running";
	}

};
class SportsCar : public Icar {
public:
	void run_car() {
		cout << "SportsCar car running";
	}

};
class factory {
public:
	static unique_ptr<Icar> make_car(const string& carType) {
		if (carType == "Normal")
		{
			return std::make_unique<NormalCar>();
		}
		else {
			return  std::make_unique<SportsCar>();
		}
	}
	
};

int main() {
	unique_ptr<Icar>car= factory::make_car("Normal");
	car->run_car();

	return 0;
}