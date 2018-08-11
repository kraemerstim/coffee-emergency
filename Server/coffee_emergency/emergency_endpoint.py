from flask_restful import Resource
from emergency_manager import EmergencyManager

class ButtonPressed(Resource):
    def put(self, device_id, button_id):
        return {'status' : EmergencyManager.button_pressed(device_id, button_id)}

class DeviceStatus(Resource):
    def get(self, device_id):
        return {'status' : EmergencyManager.get_status(device_id)}