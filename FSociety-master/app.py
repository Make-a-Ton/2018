from flask import Flask, send_from_directory,  render_template, flash, redirect, url_for,request,session,logging
from data import Users

app = Flask(__name__, static_url_path='')


Users=Users()

@app.route('/')
def index():
    return render_template('home.html')

@app.route('/about')
def about():
    return render_template('about.html')

@app.route('/login')
def login():
    return render_template('login.html')


@app.route('/signup')
def signup():
    return render_template('signup.html')

@app.route('/authors')
def authors():
    return render_template('authors.html')


@app.route('/tojob')
def tojob():
    return render_template('tojob.html')

@app.route('/img')
def send_js(path):
    return send_from_directory('img',path)


@app.route('/maths')
def maths():
    return render_template('maths.html')


@app.route('/menu')
def menu():
    return render_template('menu.html')


@app.route('/sub')
def sub():
    return render_template('sub.html')


@app.route('/profile')
def profile():
    return render_template('profile.html')


@app.route('/hire')
def hire():
    return render_template('hire.html')


@app.route('/search')
def search():
    return render_template('search.html')




if __name__ == "__main__":
   app.run(debug=True)
