from models import Device

class EmergencyManager:
    @staticmethod
    def get_status(device_id):
        return Device.get_or_create_device_by_id(device_id).status

    @staticmethod
    def button_pressed(device_id, button_id):
        Device.button_pressed_on_device(device_id, button_id)
        return Device.get_device_by_id(device_id).status