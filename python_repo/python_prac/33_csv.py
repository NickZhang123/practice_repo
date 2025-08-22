import csv

header = ['姓名', '年纪', '性别']   # 列表形式
data = [('张三', '323', '男'), ('李四', '2', '男'), ('王二狗', '22', '男'), ('翠花', '23', '女')]   # 列表中元组

with open('test.csv', 'w', encoding='utf-8', newline='') as f:    # 编码格式， 新建行
    writer = csv.writer(f)
    writer.writerow(header)     # writerow
    writer.writerows(data)      # writerows


header2 = ['姓名', '年纪', '性别']   # 列表形式
data2 = [
        {'姓名' : '张三', '性别' : '男', '年纪' : '23'},
        {'姓名' : '李四', '性别' : '男', '年纪' : '2'},
        {'姓名' : '王二狗', '性别' : 'nv', '年纪' : '3333'},
    ]

with open('test2.csv', 'w', encoding='utf-8', newline='') as f:
    writer = csv.DictWriter(f, header2)  # 头部数据先传递
    writer.writeheader()                # 手动写入header
    writer.writerow({'姓名' : '翠花', '性别' : 'nv', '年纪' : '3333'})
    writer.writerows(data2)             # 字典方式传递