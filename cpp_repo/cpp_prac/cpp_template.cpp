#include <iostream>
using namespace std;

//两个标签类
struct brain_worker{};              //脑力劳动
struct physical_worker{};           //体力劳动

// 不同类中有相同worker_type类型
class Worker{
public:
	typedef physical_worker worker_type;

};

class Farmer{
public:
	typedef physical_worker worker_type;

};

class Teacher{
public:
	typedef brain_worker worker_type;
	
};

class Doctor{
public:
	typedef brain_worker worker_type;
	
};

template<typename T>
void __distinction(const T &t, brain_worker){
	cout<<"脑力劳动者"<<endl;
}

template<typename T>
void __distinction(const T &t, physical_worker){
	cout<<"体力劳动者"<<endl;
}

template<typename T>
void distinction(const T &t){
	typename T::worker_type _type;        //为了实现重载
	__distinction(t, _type);
}

void test_template()
{
    Worker w;
	Farmer f;
	Teacher t;
	Doctor d;
	
	distinction(w);
	distinction(f);
	distinction(t);
	distinction(d);
}