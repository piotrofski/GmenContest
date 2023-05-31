import requests

x = requests.get('https://mazing.pythonanywhere.com/10')
print(x.text)