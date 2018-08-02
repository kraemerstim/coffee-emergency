from datetime import datetime, timedelta
from peewee import SqliteDatabase, Model, CharField, IntegerField, DateTimeField, ForeignKeyField, BooleanField

DATABASE = 'coffee_emergency.db'
db = SqliteDatabase(DATABASE)

class BaseModel(Model):
    class Meta:
        database = SqliteDatabase(DATABASE)

class Device(BaseModel):
    internal_id = CharField()
    external_name = CharField(default='name me!')
    responsible_hipchat_user = CharField(default='insert hipchat username!')
    
    @property
    def button_count(self):
        return Button.select().where(Button.device == self).count()

    @property
    def status(self):
        highest_emergency_state = 0
        for button in Button.select().where(Button.device == self):
            if button.emergency_state > highest_emergency_state:
                highest_emergency_state = button.emergency_state
        return highest_emergency_state

    @staticmethod
    def button_pressed_on_device(device_id, button_id):
        device = Device.get_or_create_device_by_id(device_id)
        device.button_pressed(button_id)

    @staticmethod
    def get_device_by_id(device_id):
        return Device.get_or_none(Device.internal_id == device_id)
   
    @staticmethod
    def get_or_create_device_by_id(device_id):
        device = Device.get_device_by_id(device_id)
        if device == None:
            device = Device.create(internal_id=device_id)
        return device

    def button_pressed(self, button_id):
        pressed_button = self.get_or_create_button_by_id(button_id)
        if (pressed_button.is_reset_button):
            for button in Button.select().where(Button.device == self):
                button.reset()
            return 0
        else:
            pressed_button.pressed()
            return self.status

    def get_button_by_id(self, button_id):
        return Button.get_or_none((Button.device == self) & (Button.id_in_device == button_id))
    
    def get_or_create_button_by_id(self, button_id):
        button = self.get_button_by_id(button_id)
        if not button:
            button = Button.create(id_in_device=button_id, device=self)
        return button


class Button(Model):
    id_in_device = IntegerField()
    is_reset_button = BooleanField(default=False)
    emergency_state = IntegerField(default=0)
    last_pressed = DateTimeField(default=datetime.now())
    device = ForeignKeyField(Device, backref='buttons')

    class Meta:
        database = SqliteDatabase(DATABASE)

    def reset(self):
        self.emergency_state = 0
        self.last_pressed = datetime.now()
        self.save()

    def _pressed_internal(self, press_time):
        if self.last_pressed + timedelta(hours=5) > press_time:
            self.emergency_state += 1
        else: 
            self.emergency_state = 1

        self.last_pressed = press_time
        self.save()

    def pressed(self):
        if (self.is_reset_button):
            return 0
        self._pressed_internal(datetime.now())
        return self.emergency_state
    
    @staticmethod
    def get_button_by_id(device_id, button_id):
        try:
            button = Button.select().join(Device).where(
                (Device.internal_id == device_id) & 
                (Button.id_in_device == button_id)
            ).get()
        except Button.DoesNotExist:
            button = None

        return button