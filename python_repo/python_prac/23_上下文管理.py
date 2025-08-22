
# 建立一个可放入with上下文管理的类
class MyOpen(object):
    def __init__(self, file, mode) -> None:
        self.file = file
        self.mode = mode
    
    # 进入上下文函数，准备资源
    def __enter__(self):
        print("enter...")
        self.handle = open(self.file, self.mode)
        return self.handle
    
    # 退出上下文，释放资源
    def __exit__(self, *exc_info):
        # exc_info包含异常类型type，异常值val，异常栈exc_tb
        print("exit...", *exc_info) # exit... None None None
        self.handle.close()
        return True # 正常或者这里处理异常返回true，异常返回False向外抛异常

with MyOpen("file1.txt", 'rb') as f:
    3/0
    print(f.readline())

    