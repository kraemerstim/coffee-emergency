import button

class Device:
    def __init__(self, name, button_count, responsible_user):
        self._name = name
        self._buttons = []
        for _ in range(button_count):
            self._buttons.append(button.Button())
        self.responsible_user = responsible_user

    @property
    def status(self):
        worst_button_state = 0
        for button in self._buttons:
            if button.state > worst_button_state:
                worst_button_state = button.state
        return worst_button_state

    def addButton(self):
        self._buttons.append(button.Button())
