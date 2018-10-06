from flask import Flask
from flask_restful import Resource, Api
from emergency_endpoint import ButtonPressedResource, DeviceStatusResource, ButtonTypeResource
from emergency_manager import EmergencyManager
import config_reader

EmergencyManager.initialize()
config_reader.initialize()

app = Flask(__name__)
api = Api(app)
api.add_resource(DeviceStatusResource, '/emergency/rest/device/<device_id>/status')
api.add_resource(ButtonPressedResource, '/emergency/rest/device/<device_id>/button/<button_id>/pressed')
api.add_resource(ButtonTypeResource, '/emergency/rest/device/<device_id>/button/<button_id>/type')

if __name__ == '__main__':
    app.run(debug=True, host="0.0.0.0")