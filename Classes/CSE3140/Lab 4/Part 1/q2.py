from flask import Flask


app = Flask(__name__)


@app.route('/')
def index():
    return "Team Number: 9, Names: Isaac Piegat, Voelker Kyle"


if __name__ == '__main__':
    app.run(debug=True)
