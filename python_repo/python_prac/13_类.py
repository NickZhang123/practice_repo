import copy

########################################
# 类声明
class Dog(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def bark(self, n):
        for i in range(n):
            print('Won...')


# 设计一个人类
class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age
        self.__name = 'zhangsan'

    def get_name(self):
        return self.__name

    # 为人添加一个拥有宠物方法
    def add_pet(self, pet):
        self.pet = pet

    # 人想听狗叫
    def listen_dog_bark(self, n):
        self.pet.bark(n)

    def listen_dog_bark2(self, n):
        print(self.pp)

    def __priFunc(self):
        print("私有方法")

    def pPriFunc(self):
        self.__priFunc()


# 测试
# 实例一个人类对象
tom = Person('Tom', 23)
# 为人的对象添加一条狗
tom.add_pet(Dog('glof', 1))

# 人调用 想听狗叫的方法
tom.listen_dog_bark(3)
tom.pp = 'pp'

print(tom.get_name())
tom.pPriFunc()

########################################
# 继承
class Phone(object):
    def __init__(self):
        self.name = '电话'
        self.__age = 32

    def call(self, number):
        print(f'正在给 {number} 打电话')

class iPhone(Phone):
    def carmera(self):
        print('正在拍照')
        #print(self.__age)    # 子类不能使用父类的私有属性和私有方法


# 当发生继承后，子类会继承父类中的属性和方法，可以直接 使用
iphonex = iPhone()
iphonex.call('13800138000')  # 正在给 13800138000 打电话
iphonex.carmera()  # 正在拍照
print(iphonex.name)  # 电话

dgd = Phone()
dgd.call('13800138000')  # 正在给 13800138000 打电话
print(dgd.name)  # 电话
# dgd.carmera()
print("***************")

########################################
# 父类构造函数调用
class Father(object):
    def __init__(self, name):
        print("Father init")
        self.name = name
        self.__name = name

    def func1(self):
        print("father func1")


class Son(Father):
    def __init__(self, name, age):
        Father.__init__(self, name)
        print("Son init")
        self.age = age

    def __str__(self):
        return f"name={self.name}, age={self.age}"


s = Son('zhangsan', 32)
print(s)


########################################
# 重写
class Father1(object):
    def func1(self):
        print("Father1 func1")


class Son1(Father1):
    def func1(self):
        Father1.func1(self)  # 调用父类被重写的方法
        print("Son1 func1")


s = Son1()
s.func1()
print("***************")

########################################
# x. 多重继承(砖石继承)
class Person(object):
    def __init__(self, aaa):
        print('Person Init ...')
        self.aaa = aaa


class Father(Person):
    def __init__(self, name, *args):  # 参数顺序，优先本类，后续*args
        super(Father, self).__init__(*args)
        print('Father Init ...')
        self.name = name


class Mother(Person):
    def __init__(self, age, *args):  # 参数顺序，优先本类，后续*args
        super(Mother, self).__init__(*args)
        print('Mother Init ...')
        self.age = age


class Son(Father, Mother):  # 顺序从左往右初始化
    def __init__(self, gender, name, age, aaa):  # 参数顺序，优先本类，后续*args
        super(Son, self).__init__(name, age, aaa)  # 根据Father->Mother->Person的顺序填参数
        print('Son Init ...')
        self.gender = gender


# 测试
print(
    Son.__mro__)  # (<class '__main__.Son'>, <class '__main__.Father'>, <class '__main__.Mother'>, <class '__main__.Person'>, <class 'object'>)
s = Son('男', 'Tom', 12, 1)
print(s.aaa)
print(s.name)
print(s.age)
print(s.gender)


# super简化版
class A(object):
    def show(self):
        print('A _ Show Run ...')

    def info(self):
        print('A - Info run ...')

class B(A):
    def show(self):
        print('B _ Show Run ...')

class C(A):
    def show(self):
        print('C _ Show Run ...')

    def info(self):
        # super().info()
        # A.info(self)
        print('C - Info run ...')

class D(B, C):
    def show(self):
        super().show()
        # A.show(self)
        print('D _ Show Run ...')

d = D()
d.show()


#d.info()


########################################
# 类属性
class TA(object):
    cls_name = 'Class_name'  # 类的属性

    def __init__(self, name):
        self.name = name  # 类对象属性

    def func(self):  # 类对象函数
        print("func")


# print(TA.name) 不能调用对象属性
# TA.func() 不能调用对象方法
print(TA.cls_name)  # Class_name, 可以访问类属性
TA.cls_name = "new cls name"
print(TA.cls_name)  # 通过类修改

ta = TA("name")
print(ta.cls_name)  # 对象访问
ta.cls_name = "new cls name 2"
print(ta.cls_name)  # 修改的是对象的类属性 new cls name 2
print(TA.cls_name)  # new cls name  


########################################
# __dict__
class Cat(object):
    def __init__(self, name):
        self.name = name
        self.__xxx = 1

    def public_method(self):
        print('公有的对象方法')

    def __private_method(self):
        print('私有的对象方法')


tom = Cat('Tom')
jack = Cat('Jack')
# __dict__ 是一个魔法属性，用来保存当前对象的所有的成员
print(Cat.__dict__)
print(tom.__dict__)
print(jack.__dict__)

'''
{'__module__': '__main__', '__init__': <function Cat.__init__ at 0x000001C14DFEA8E0>, 'public_method': <function Cat.public_method at 0x000001C14DFEA980>, '_Cat__private_method': <function Cat.__private_method at 0x000001C14DFEAA20>, '__dict__': <attribute '__dict__' of 'Cat' objects>, '__weakref__': <attribute '__weakref__' of 'Cat' objects>, '__doc__': None}
{'name': 'Tom', '_Cat__xxx': 1}
{'name': 'Jack', '_Cat__xxx': 1}
'''

########################################
# 继承初始化
class Father(object):
    def __init__(self, name):
        print("Father init", name)
        self.name = name
        
class Son(Father):
    def __init__(self, name, age):
        super().__init__(name)
        # 初始化父类构造函数，主动调用父类__init__函数，参数self为子类对象
        # Father.__init__(self, name)	
        print("Son init", name, age)
        self.age = age
    def __str__(self):
        return f"name={self.name}, age={self.age}"

s = Son('zhangsan', 32)
print(s)    
print("xxxxxxx", s.__class__)   # <class '__main__.Son'>

########################################
# 字典属性
class FooBar:
    def __init__(self):     # 构造函数，可携带其他参数
        print("FooBar")

    def __getitem__(self, key):  # 可以继承dick/list/str后重写__getitem__函数，达到重载[]的效果
        print("__getitem__", key)

    def __setitem__(self, key, value):
        print("__setitem__", key, value)
        
    def __delitem__(self, key):
        print("__delitem__", key)

fb = FooBar()
fb[2]               # __getitem__ 2
fb[2] = 'a'         # __setitem__ 2 a
del fb[2]           # __delitem__ 2

########################################
# 函数覆盖顺序
class A(object):
    def printS(self):
        print("A")
class B(object):
    def printS(self):
       print("B")
class C(A, B):
    def test(self):
        self.printS()
c = C()
c.test()    # A


rst = [n for n in dir(copy) if not n.startswith('_')]
print(rst)  # ['Error', 'copy', 'deepcopy', 'dispatch_table', 'error']