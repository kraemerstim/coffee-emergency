from flask_restful import Resource, reqparse
from emergency_manager import EmergencyManager


parser = reqparse.RequestParser()
parser.add_argument('type')

class ButtonPressedResource(Resource):
    def put(self, device_id, button_id):
        return {'status' : EmergencyManager.button_pressed(device_id, button_id)}

class DeviceStatusResource(Resource):
    def get(self, device_id):
        return {'status' : EmergencyManager.get_status(device_id)}

class ButtonTypeResource(Resource):
    def put(self, device_id, button_id):
        args = parser.parse_args()
        return EmergencyManager.set_button_type(device_id, button_id, args['type'])
    
    def get(self, device_id, button_id):
        return {'type' : EmergencyManager.get_button_type(device_id, button_id)}