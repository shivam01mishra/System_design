#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<memory>

using namespace std;

class Observer {
	int key;
public:
	Observer(int key) {
		this->key = key;
	}
	int get_key() {
		return key;
	}
	void notify(const string msg) {
		cout<<"observer ("<<get_key()<< ") group have sent a message :" << msg << "\n";
	}
};

class Group {
	map<int, shared_ptr<Observer>>observer_list;
public:
	void add_observer(shared_ptr<Observer>obj)
	{
		observer_list[obj->get_key()] = obj;
}

	void remove_observer(int key)
	{
		observer_list.erase(key);
	}
	void noity_observer(const string msg) {
		for (auto& obj : observer_list) {
			obj.second->notify(msg);
		}
	}
};




int main()
{
	unique_ptr<Group>grp = make_unique<Group>();
	auto obj1 = make_shared<Observer>(1);
	auto obj2 = make_shared<Observer>(2);
	grp->add_observer(obj1);
	grp->add_observer(obj2);
	grp->noity_observer("this is new message");
	return 0;
}
