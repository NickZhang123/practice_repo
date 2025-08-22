import json
import jsonpath

data = '''
{
"store": {
        "book": [
            {"category": "reference", "author": "Nigel Rees", "title": "Sayings of the Century", "price": 18.95},
            {"category": "fiction", "author": "Evelyn Waugh", "title": "Sword of Honour", "price": 12.99},
            {"category": "fiction33", "author": "Herman Melville", "title": "Moby Dick", "price": 8.99},
            {"category": "fiction44", "author": "J. R. R. Tolkien", "title": "The Lord of the Rings", "price": 22.99}
        ],
        "book1" : {"category": "fiction-1", "author": "J. R. R. Tolkien1", "title": "The Lord of the Rings1", "price": 22.991},
        "bicycle": {"color": "red", "price": 19.95}
    }
}
'''

json_obj = json.loads(data)                 # 将json字符串转化为python字典或者列表
print(type(json_obj))                       # <class 'dict'>

json_str = json.dumps(json_obj, indent=2)   # 将python字典或者列表转化为json字符串
print(type(json_str))                       # <class 'str'>



# 参数是load后的python对象； 匹配成功后返回匹配到的内容，失败返回False
# 任意位置
print(jsonpath.jsonpath(json_obj, '$..author'))         # 匹配所有author的value值
print(jsonpath.jsonpath(json_obj, '$..color'))          # 匹配所有color的value值, ['red']
# print(jsonpath.jsonpath(json_obj, '$..author'[2]))      # 匹配所有author中的的value值

# 指定位置
print(jsonpath.jsonpath(json_obj, '$.store.bicycle.price'))     # [19.95]
print(jsonpath.jsonpath(json_obj, '$.store..price'))            # [8.95, 12.99, 8.99, 22.99, 19.95]

# 通配符（下标位置从0开始）
print(jsonpath.jsonpath(json_obj, '$.store.book[2].category'))  # 根目录下store下book下第三个项的category
print(jsonpath.jsonpath(json_obj, '$.store.book[2:].category'))  # 根目录下store下book下第三个以后的项的category
print(jsonpath.jsonpath(json_obj, '$.store.book[0,1].category'))  # 根目录下store下book下第1,2个项的category
print(jsonpath.jsonpath(json_obj, '$.store.book[*].category'))  # 根目录下store下所有的category

# @当前元素
# 取根目录下store下book列表中，价格小于10的项，输出项的category
print(jsonpath.jsonpath(json_obj, '$.store.book[?(@.price < 10)].category'))  

# 嵌套
ret = jsonpath.jsonpath(json_obj, '$.store.book[0]')
print(ret)
ret = jsonpath.jsonpath(ret, '$..category')
print(ret)