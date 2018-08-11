from flask import Flask
from flask_restful import Resource, Api
from emergency_endpoint import ButtonPressed, DeviceStatus
from models import Database

Database.initialize()
app = Flask(__name__)
api = Api(app)
api.add_resource(DeviceStatus, '/emergency/rest/device/<device_id>/status')
api.add_resource(ButtonPressed, '/emergency/rest/device/<device_id>/button/<button_id>/pressed')

if __name__ == '__main__':
    app.run(debug=True)