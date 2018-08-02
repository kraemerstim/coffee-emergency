from coffee_emergency import Button, Device
from datetime import datetime
from peewee import SqliteDatabase
import unittest


MODELS = [Button, Device]

# use an in-memory SQLite for tests.
temp_db = SqliteDatabase(':memory:')

class DeviceTestCase(unittest.TestCase):
    def setUp(self):
        # Bind model classes to test db. Since we have a complete list of
        # all models, we do not need to recursively bind dependencies.
        temp_db.bind(MODELS, bind_refs=False, bind_backrefs=False)

        temp_db.connect()
        temp_db.create_tables(MODELS)

    def tearDown(self):
        # Not strictly necessary since SQLite in-memory databases only live
        # for the duration of the connection, and in the next step we close
        # the connection...but a good practice all the same.
        temp_db.drop_tables(MODELS)

        # Close connection to db.
        temp_db.close()
    
    def test_device_manager(self):
        self.assertEquals(Device.select().count(), 0)
        self.assertEquals(Button.select().count(), 0)
        Device.button_pressed_on_device('dev_id1', 0)
        self.assertEquals(Device.select().count(), 1)
        self.assertEquals(Button.select().count(), 1)
        self.assertEquals(Device.get_device_by_id('dev_id1').status, 1)

    def test_device_button_count(self):
        Device.button_pressed_on_device('dev_id1', 0)
        my_device = Device.get_device_by_id('dev_id1')
        self.assertEquals(my_device.button_count, 1)
        my_device.button_pressed(1)
        self.assertEquals(my_device.button_count, 2)

