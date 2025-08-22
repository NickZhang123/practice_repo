#include <iomanip>
#include <iostream>
#include "cpp17_test.h"
#include <map>
#include <optional>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <chrono>
#include <filesystem>

using namespace std;

#ifdef CPP17
// 解包tuple
std::tuple<int, double, std::string> get_values() 
{
    return {1, 3.14, "hello"};
}

// 解包pair
std::pair<int, std::string> get_pair() 
{
    return {42, "answer"};
}

// 解包自定义类型
struct Person {
    std::string name;
    int age;
};

std::tuple<std::string, int> to_tuple(const Person& p) 
{
    return std::make_tuple(p.name, p.age);
}

map<string, int> get_map()
{
    return {
        { "hello", 1 },
        { "world", 2 },
        { "it's",  3 },
        { "me",    4 },
    };
}

std::optional<int> get_value(bool should_return) 
{
    if (should_return) {
        return 42;
    } else {
        return std::nullopt; // 表示无值
    }
}

template<typename T>
void func(T value) 
{
    if constexpr (std::is_same_v<T, int>) {
        std::cout << "Type is int\n";
    } else if constexpr (std::is_same_v<T, double>) {
        std::cout << "Type is double\n";
    } else {
        std::cout << "Type is something else\n";
    }
}

// 折叠表达式
template<bool f, class... T>
constexpr auto sub_func(const T& ...args)
{
    if (f) {
        return (... - args);
    } else {
        return (args - ...);
    }
}

template <typename... Args>
void print_var1(Args... args) 
{
    (cout << ... << args) << endl;   // == (((cout << arg1) << arg2) << arg3 ...) << endl;
}

template <typename... Args>
void print_var2(Args... args) 
{
    // 逗号运算符的一元左折叠
    (..., (cout << " " << args));  // (cout << " " << arg1), (cout << " " << arg12)
    cout << endl;
}

template <class Func, class... Args>
void print_var3(Func func, Args ...args)
{
    (... , func(args));
}

void cpp17_test()
{
    /*
    auto [x, y, z] = get_values();
    std::cout << x << ' ' << y << ' ' << z << std::endl; // 输出: 1 3.14 hello
    auto [num, str] = get_pair();
    std::cout << num << ' ' << str << std::endl; // 输出: 42 answer

    Person person{"Alice", 30};
    auto [name, age] = to_tuple(person);
    std::cout << name << ' ' << age << std::endl; // 输出: Alice 30

    for (auto&& [k, v] : get_map())  // 结合 for-each
        cout << "k=" << k << " v=" << v << endl;
    
    cout << "-----------------" << endl;
    */

    std::string str = "Hello, World!";
    std::string_view sv1(str);          // 从 std::string 创建
    std::string_view sv2("Hello");      // 从字符串字面量创建
    cout << sv1.substr(0, 5) << "   " << sv2 << endl;   // 从0开始，后面5个
    cout << sv1.substr(5) << "   " << sv2 << endl;      // 从5个开始，后面所有

    std::optional<int> res = get_value(true);
    auto res2 = get_value(false);

    if (res) {
        // operator*, value()
        std::cout << "Value1: " << *res << "----" << res.value() << std::endl;  
    } else {
        std::cout << "Value1 has no value" << std::endl;
    }

    if (res2) {
        std::cout << "Value2: " << *res2 << std::endl;
    } else {
        std::cout << "Value2 has no value" << std::endl;
    }


    namespace fs = std::filesystem;
    fs::path p1 = "example.txt";
    fs::path p2 = "/home/user/example";

    // 路径组成
    cout << "Filename: " << p1.filename() << endl;          // example.txt
    cout << "Extension: " << p1.extension() << endl;        // .txt
    cout << "Parent path: " << p2.parent_path() << endl;    // /home/user

    // 路径拼接
    fs::path p = "/home/user";
    fs::path full_path = p / "example.txt";
    cout << full_path << endl;                  // /home/user/example.txt

    // 文件操作
    if (fs::exists(full_path)) {
        cout << "file exists" << endl;
    } else {
        cout << "file not exists" << endl;   
    }

    // 创建文件
    ofstream("example.txt"); 
    if (fs::remove("example.txt")) {
        cout << "File deleted" << endl;
    }

    // 创建目录
    fs::create_directory("example_dir"); 
    if (fs::remove_all("example_dir")) {  // 删除目录及其内容
        cout << "Directory deleted" << endl;
    }

    // 遍历目录中的所有文件和子目录
    for (const auto& entry : fs::directory_iterator(".")) {
        cout << entry.path() << endl;
    }

    // 获取文件大小
    auto size = fs::file_size("./main.cpp");
    cout << "File size: " << size << " bytes" << endl;

    // 获取文件的最后修改时间
    auto ftime = fs::last_write_time("./main.cpp");
    // 将 file_time_type 转换为 std::time_t
    //std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime)
    // 将 std::time_t 转换为本地时间
    //std::cout << "Last write time: " << std::asctime(std::localtime(&cftime)) << std::endl;

    func(10);       // 输出: Type is int
    func(3.14);     // 输出: Type is double
    func("Hello");  // 输出: Type is something else

    cout << sub_func<true>(1,2,3,4) << endl;   // ((1-2)-3)-4 = -8
    cout << sub_func<false>(1,2,3,4) << endl;  // 1-(2-(3-4)) = -2

    print_var1(1, 2, 'f', "fd");
    print_var2(1, 2, 'f', "fd");


    print_var3([](auto x) {cout << " " << x;}, 1, 2, 'f', "fd");
}

#endif