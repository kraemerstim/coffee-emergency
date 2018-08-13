from flask import Flask
from flask_restful import Resource, Api
from emergency_endpoint import ButtonPressedResource, DeviceStatusResource, ButtonTypeResource
from models import Database

Database.initialize()
app = Flask(__name__)
api = Api(app)
api.add_resource(DeviceStatusResource, '/emergency/rest/device/<device_id>/status')
api.add_resource(ButtonPressedResource, '/emergency/rest/device/<device_id>/button/<button_id>/pressed')
api.add_resource(ButtonTypeResource, '/emergency/rest/device/<device_id>/button/<button_id>/type')

if __name__ == '__main__':
    app.run(debug=True)