import urllib.request
from lxml import etree

# 1. 获取网页
url = 'http://www.baidu.com'
res = urllib.request.urlopen(url)
#print(res.read().decode())

# 2. 将网页转化为etree对象
tree = etree.HTML(res.read())
#print(tree)

# 3. xpath路径查找
ret = tree.xpath('//input[@id="su"]')
print(type(ret))        # 返回列表
print(ret[0].items())   # 返回第一个元素的所有内容
'''
lxml.etree._Element常用接口:
    items() 获取元素的所有属性及其值
    keys() 获取所有属性名
    text 获取或设置元素的文本内容
    get(key, default=None) 获取元素的属性值
    set(key, value) 设置元素的属性值
'''

# 直接返回属性
print(tree.xpath('//input[@id="su"]/@value'))
print(tree.xpath('//input[@id="su"]/text'))

# 4. 嵌套查找
ret = tree.xpath('//form[@id="form"]')
ret = ret[0].xpath('//input[@name="rsv_t"]')
print(ret[0].get('value'))


'''
tree = etree.parse('xxx.html')
print(type(tree))

# 属性定位
ret = tree.xpath('//div[@class="xxx"]/ul/li[1]/text()')  # ret是一个列表， 取文本
ret = tree.xpath('//div[@class="xxx"]/ul/li[last()]/a/@href')  # ret是一个列表，  取属性
ret = tree.xpath('//div[@class="xxx"]/ul/li[@class="love" and @name="yang"]')  #  取属性交集
ret = tree.xpath('//li[contains(@class, "l")]')  # 带l的属性class的li
ret = tree.xpath('//li[contains(text(), "爱")]')  # 带爱的文本的li
ret = tree.xpath('//li[starts-with(@class, "ve")]')  # 带爱的文本的li


# 拼接所有text
ret = tree.xpath('//div[@class="xxx"]')
string = ret[0].xpath('string(.)')                  # 取所有text
print(string.replace('\n', '').replace('\t', ''))   # 替换换行和table
'''