#include<iostream>
#include<string>
#include<vector>
#include<mutex>
using namespace std;



class Logger{
	vector<string>data;
	static Logger* logger_ptr;
	static int inst_count;
	static std::mutex m_mutex;
	Logger() {
		cout << "Logger Initialized" << endl;
	}
	void operator=(const Logger& obj) = delete;
	Logger(const Logger& obj) = delete;
	
public:
	
	void insert_data(string s)
	{
		data.push_back(s);
	}
	void print_data() {
		for (auto& s : data) {
			cout << s << endl;
		}
	}
	static Logger* creat_instance() {
		if (logger_ptr == nullptr) {
			m_mutex.lock();
			if (logger_ptr == nullptr) {
				logger_ptr = new Logger();

			}
			m_mutex.unlock();
		}
		
		return logger_ptr;
	}


};

Logger* Logger::logger_ptr = nullptr;
int Logger::inst_count = 0;
std::mutex Logger::m_mutex;

int main()
{	
	Logger* obj_ptr1 = Logger::creat_instance();
	Logger* obj_ptr2 = Logger::creat_instance();

	obj_ptr1->insert_data("this id first inst");
	obj_ptr2->insert_data("this id first inst");

	 
	obj_ptr1->print_data();
	 
	return 0;
}