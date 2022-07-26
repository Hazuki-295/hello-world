from flask import Flask

miniApp = Flask(__name__)


@miniApp.route("/")
def hello_world():
    return "<p>Hello, World!</p>"
