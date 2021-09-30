import os
from selenium import webdriver

browser = webdriver.Edge()

result = os.popen('arp -a')
target_str = ''
for i in result:
    if 'c4-5b-be-4c-aa-ab' in i:
        target_str = str(i)

target_url = ''

for i in range(2, len(target_str)):
    target_url += target_str[i]
    if target_str[i] == ' ':
        break

target_url = target_url.rstrip()
target_url = 'http://' + target_url + '/'
print(target_url)
page = browser.get(target_url)
