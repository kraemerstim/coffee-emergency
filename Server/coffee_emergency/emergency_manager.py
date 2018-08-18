from models import Device, Button

class EmergencyManager:
    @staticmethod
    def get_status(device_id):
        return Device.get_or_create_device_by_id(device_id).status

    @staticmethod
    def button_pressed(device_id, button_id):
        Device.button_pressed_on_device(device_id, button_id)
        return Device.get_device_by_id(device_id).status

    @staticmethod
    def set_button_type(device_id, button_id, button_type):
        button = Button.get_button_by_id(device_id, button_id)
        if button_type == 'reset':
            button.is_reset_button = True
            button.reset()
            button.save()
        else:
            button.is_reset_button = False
            button.save()

    @staticmethod
    def get_button_type(device_id, button_id):
        button = Button.get_button_by_id(device_id, button_id)
        if button.is_reset_button:
            return 'reset'
        return 'normal'