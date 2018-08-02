from coffee_emergency import Button, Device
from datetime import datetime
from peewee import SqliteDatabase
import unittest


MODELS = [Button, Device]

# use an in-memory SQLite for tests.
temp_db = SqliteDatabase(':memory:')

class ButtonTestCase(unittest.TestCase):
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
    
    def test_get_state(self):
        my_device = Device.create(internal_id='get_state_device')
        my_button1 = Button.create(id_in_device=0, device=my_device)
        my_button2 = Button.create(id_in_device=1, device=my_device)
        my_button3 = Button.create(id_in_device=2, device=my_device)
        self.assertEqual(my_device.status, 0)
        my_button2.pressed()
        self.assertEqual(my_device.status, 1)
        my_button3.pressed()
        my_button3.pressed()
        self.assertEqual(my_device.status, 2)
        my_button3.reset()
        self.assertEqual(my_device.status, 1)
    
    def test_button_by_id(self):
        my_device = Device.create(internal_id='device1')
        my_button1 = Button.create(id_in_device=0, device=my_device)
        my_button2 = Button.create(id_in_device=1, device=my_device)
        get_button = Button.get_button_by_id('device1', 0)
        self.assertEqual(my_button1, get_button)
        self.assertNotEqual(my_button2, get_button)

    def test_button_pressed(self):
        my_device = Device.create(internal_id='button_pressed_device')
        my_button = Button.create(id_in_device=0, device=my_device)
        my_button._pressed_internal(datetime(2000,1,1,5))
        self.assertEqual(my_button.emergency_state, 1)
        my_button._pressed_internal(datetime(2000,1,1,6))
        self.assertEqual(my_button.emergency_state, 2)
        my_button._pressed_internal(datetime(2000,1,2,0))
        self.assertEqual(my_button.emergency_state, 1)
        my_button.reset()
        self.assertEqual(my_button.emergency_state, 0)

    def test_button_get(self):
        id = 'id1'
        self.assertIsNone(Button.get_button_by_id(id, 0))
        Device.button_pressed_on_device(id, 0)
        self.assertIsNotNone(Button.get_button_by_id(id, 0))
