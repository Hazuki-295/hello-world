from flask import Flask
from flask import request

miniApp = Flask(__name__)


@miniApp.route("/")
def hello_world():
    return "Hello, World!"


@miniApp.route("/name", methods=['GET', 'POST'])
def get_name():
    if request.method == 'GET':
        return "Hazuki-295 from GET"
    elif request.method == 'POST':
        return "Hazuki-295 from POST"


@miniApp.route("/profile", methods=['GET', 'POST'])
def get_profile():
    if request.method == 'GET':
        name = request.args.get("name", "None")
        if name == "Hazuki-295":
            return dict(name="Hazuki-295 from GET", fans=1000)
        else:
            return dict(name="luotuo from GET", fans=100000)
    elif request.method == 'POST':
        # assert request body is in json format
        name = request.json.get("name")
        if name == "Hazuki-295":
            return dict(name="Hazuki-295 from POST", fans=1000)
        else:
            return dict(name="luotuo from POST", fans=100000)
