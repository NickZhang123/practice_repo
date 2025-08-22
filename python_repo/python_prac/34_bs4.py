
from bs4 import BeautifulSoup

# 示例 HTML 文档
html_doc = """
<html><head><title>小睡鼠的故事</title></head>
    <body>
        <p class="title"><b>小睡鼠的故事</b></p>
            <a href="http://example.com/title" class="tit" id="titl">titlex</a>,
        <p class="story">从前有三个小妹妹，她们的名字是
            <a href="http://example.com/sys1" class="sister" id="link1">妹妹1</a>,
            <a href="http://example.com/sys2" class="sister2" id="link2">妹妹2</a> 和
            <a href="http://example.com/sys3" class="sister" id="link3">妹妹3</a>;
            她们住在井底。</p>
        <p class="story2">...</p>
        <ul>yyy</ul>
        <li>xxx</li>
    </body>
</html>
"""

soup = BeautifulSoup(html_doc, 'html.parser')

# 1. 打印 HTML 文档的标题
print(soup.title.string)

# 2. 获取第一个a标签
print(soup.find('a').text)

# 获取第一个标签的所有属性
print(soup.a.attrs)    
print(soup.a.attrs['href'])        # 查找标签中的属性 


# 3. 获取指定class的a标签
print(soup.find('a', attrs={'class' : 'sister2'}).get('href'))

# 获取指定id的a标签
print(soup.find('a', attrs={'id' : 'link3'}).get('href'))

# 获取标签内容
res = soup.find('p', attrs={'class' : 'story'})
print(res.text, end='====\n')           # 获取标签p中的内容（会递归标签p中的标签a）
print(res.string, end='====\n')         # 获取标签p中的内容（不会递归标签p中的标签a）
print(res.get_text(), end='====\n')     # 获取标签p中的内容（会递归标签p中的标签a）

# 4. 嵌套
print("res下的a标签:", res.find('a'))   # 返回结果也可以继续查找


# 5. 查找所有链接（find_all返回列表）
for link in soup.find_all('a'):
    print(link.get('href'))

# 查找所有class=sister的链接
print(soup.find_all('a', attrs={'class' : 'sister'}))

# 6. findall同时查找多个标签
print("tt", soup.find_all(['ul', 'li']))

# select
print(soup.select('p.story > a#link2')[0].text) # 标签p且属性class为story下的标签a且属性id为link2的结构第一个的text

res = soup.find('p', attrs={'class' : 'story'})
print(res.select('a.sister')[1].text)   # 妹妹3
'''

soup = BeautifulSoup(open('本地文件', encoding='utf-8'), 'lxml')      # 转化本地文件
soup = BeautifulSoup('字符串、字节类型', 'lxml')    # 转化网络文件

# <a herf='xxx' target='yyy'>test</a>
print(soup)
soup.a  # 通过标签名查找，找到第一个匹配的标签
soup.a['herf']              # 查找标签中的属性
soup.a['target']            # 查找标签中的属性
soup.a.attrs                # 获取所有属性
soup.a.attrs['herf']        # 查找标签中的属性


<div>test<p>inner text</p></div>

soup.a.text         # 获取属性内容（可以递归获取标签内部标签的text）
soup.a.string       # 获取属性内容(只能获取一层text，内部标签返回None)
soup.a.get_txt()    # 获取属性内容（可以递归获取标签内部标签的text）



# find
soup.find('a')      # 找到第一个a标签
soup.find('a', title='xx')      # 匹配title=xx的a标签（也可以用其他属性查找）
soup.find('a', alt='xx')        # 匹配alt=xx的a标签（也可以用其他属性查找）

# find返回的内容可以再次查询
div = soup.find('div', alt='xx')        
print(div.find('a'))        # 查找alt=xx的div中的第一个a标签


# findall
li = soup.findall('a')   # 返回列表，找到所有的a标签
print(len(li))

li = soup.findall(['a', 'b'])       # 返回列表，找到所有的a标签和b标签

li = soup.findall('a', limit=2)     # 返回列表，找到a标签的前两个


# select选择器; 返回列表
# 常见选择器：标签、类、id、组合、层级、属性、伪类
print(soup.select('.tang > ul > li > a')[2])
print(soup.select('#id')[0].text)
print(soup.select('#id')[0]['herf'])
# select结合find结果查询
div = soup.find('div', alt='xx')     
div.select('.du')   # 在div下找
'''



