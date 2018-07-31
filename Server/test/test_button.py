from coffee_emergency import button

def test_button():
    my_button = button.Button()
    my_button.pressed()
    assert 1 == my_button.state
    my_button.pressed()
    assert 2 == my_button.state
    my_button.reset_state()
    assert 0 == my_button.state