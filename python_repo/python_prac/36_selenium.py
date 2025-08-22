from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
import time
import os
import urllib.request

'''
# 1. 使用功能edge访问百度
driver = webdriver.Edge()
url = 'http://www.baidu.com'
driver.get(url)
driver.save_screenshot("test1.png")	# 保存网页截图
time.sleep(1)

my_input = driver.find_element(By.ID, 'kw')
my_input.send_keys('python')
driver.save_screenshot("test2.png")	# 保存网页截图
time.sleep(1)

button = driver.find_elements(By.CLASS_NAME, 's_btn')[0]   # 注意：class name在网页源码中可能有多个，通过空格隔开，选一个就好
button.click()
time.sleep(1)
driver.save_screenshot("test3.png")	# 保存网页截图

driver.quit()	# 关闭浏览器


# 2. 直接唤醒edge，打开网页，然后关闭
driver = webdriver.Edge()
driver.get('https://bbs.fengniao.com/forum/11750036.html')
time.sleep(3)
driver.save_screenshot('test.png')
time.sleep(5)
driver.close()

'''
# 3. 使用headless chrome
# 配置Chrome的headless模式
chrome_options = Options()
chrome_options.add_argument("--headless")                   # 启用headless模式，使Chrome在后台运行，没有GUI界面
chrome_options.add_argument("--no-sandbox")                 # 解决某些系统上的运行问题, 特别是在 CI/CD 环境中。
chrome_options.add_argument("--disable-dev-shm-usage")

# 设置 ChromeDriver 的路径（如果未将其添加到 PATH 中）
# chrome_driver_path = r'/path/to/chromedriver'  

# 创建 Chrome 驱动实例
# service = Service(chrome_driver_path)
driver = webdriver.Chrome(options=chrome_options)

# 打开网页
url = 'https://bbs.fengniao.com/forum/11750036.html'
driver.get(url)
time.sleep(1)
#driver.save_screenshot('test.png')

# 打印网页标题
#print(driver.title)

# 打印网页源码
#print(driver.page_source)
#print(type(driver.page_source))
#with open('test.txt', 'w', encoding='utf-8') as f:
#    f.write(driver.page_source)

# 提取img，并下载
# li = driver.find_element(By.XPATH, '//div[@class="cont"]/div[@class="img"]/a/img')
li = driver.find_elements(By.XPATH, '//div[@class="cont"]/div[@class="img"]/a/img')
if not os.path.exists('testdir'):
    os.mkdir('testdir')
for i in li:
    addr = i.get_attribute('src')
    addr_prex = str(addr).split('?')[0]
    file_name = os.path.basename(str(addr_prex))
    file_name = 'testdir/' + file_name
    # print(file_name)
    urllib.request.urlretrieve(addr, file_name)
    time.sleep(1)
    
#print(li.get_attribute('src'))

# 关闭驱动
driver.quit()

