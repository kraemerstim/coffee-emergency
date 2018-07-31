import datetime

class Button:
    
    def __init__(self):
        self._state = 0
        self._last_pressed = datetime.datetime(1,1,1)

    @property
    def state(self):
        return self._state

    def reset_state(self):
        self._state = 0
        self._last_pressed = datetime.datetime.now()

    def pressed(self):
        time_now = datetime.datetime.now()
        
        if self._last_pressed + datetime.timedelta(hours=5) > time_now:
            self._state += 1
        else: 
            self._state = 1

        self._last_pressed = datetime.datetime.now()
