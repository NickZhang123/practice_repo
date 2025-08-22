
###################################################################
class CLA(object):
    def __init__(self, name, age) -> None:
        self.__name = name
        self.__age = age

    def get_name(self):
        return self.__name
    
    def set_age(self, age):
        self.__age = age

    def get_age(self):
        return self.__age
    
    # 类属性, property封装内部私有变量的get和set方法
    name = property(get_name)
    age = property(get_age, set_age)

obj = CLA("zhangsan", 20)

print(obj.get_name())   # 通过函数接口访问内部属性
print(obj.name)         # 通过属性访问内部属性，相当于调用了get_name函数
print(obj.age)          # 20
obj.age = 333           # 相当于调用了set_age函数
print(obj.age)          # 333

###################################################################
# 简化形式
#   get方法使用@property修饰
#   set方法使用@xxx.setter修饰
#   类中get和set方法同名，指示修饰方式不一样；通过对象访问属性obj.xxx的方式进行set和get操作
class CLA2(object):
    def __init__(self, name, age) -> None:
        self.__name = name
        self.__age = age

    @property  # 直接用属性的方式访问
    def name(self):
        return self.__name

    @property
    def age(self):
        return self.__age

    @age.setter    # 需要和get方法同名，形式为xxx.setter(不是property.setter)
    def age(self, age):
        self.__age = age
    
obj = CLA2("lsii", 30)
print(obj.name)  # 直接用属性的方式访问
print(obj.age)
obj.age = 23123
print(obj.age)