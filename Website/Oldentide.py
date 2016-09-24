# Filename:    Oldentide.py
# Author:      Joseph DeVictoria
# Date:        September_19_2016
# Purpose:     Flask web application to host Oldentide game server information.
from flask import Flask
from flask import render_template
app = Flask(__name__)

@app.route('/')
def hello_world():
    return render_template('index.html')

if __name__ == '__main__':
    app.run()
