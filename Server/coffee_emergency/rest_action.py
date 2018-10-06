#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from datetime import datetime, time
import requests
import config_reader
from models import Device, Button

def CallHipchatRestApi (device, button):
  if button.is_reset_button:
    message = 'Hey, ' + device.responsible_hipchat_user + '! Die Kaffeemaschine ' + device.external_name + ' ist wieder Einsatzbereit'
    color = 'green'
  elif device.status <= 1:
    message = 'Hey, ' + device.responsible_hipchat_user + '! Die Kaffeemaschine ' + device.external_name + ' hat ein Problem'
    color = 'yellow'
  else:
    message = 'Hey, ' + device.responsible_hipchat_user + '! Die Kaffeemaschine ' + device.external_name + ' sollte dringend begutachtet werden!'
    color = 'red'
  lChannelUrl = config_reader.getIniValue('Hipchat', 'url') + config_reader.getIniValue('Hipchat', 'channel') + '/notification?auth_token=' + config_reader.getIniValue('Hipchat', 'key')  

  lParams = {'message': message,
            'notify': 'true',
            'message_format': 'text',
            'color': color
  }

  print('Sending restcall to ' + lChannelUrl + ' Message: ' + message)

  response = requests.post(lChannelUrl, lParams, timeout=3)


def CallSlackRestApi (device, button):
  if button.is_reset_button:
    message = 'Hey, <@' + device.responsible_slack_user_id + '>! Die Kaffeemaschine ' + device.external_name + ' ist wieder Einsatzbereit'
  elif device.status <= 1:
    message = 'Hey, <@' + device.responsible_slack_user_id + '>! Die Kaffeemaschine ' + device.external_name + ' hat ein Problem'
  else:
    message = 'Hey, <@' + device.responsible_slack_user_id + '>! Die Kaffeemaschine ' + device.external_name + ' sollte dringend begutachtet werden!'
    
  lChannelUrl = config_reader.getIniValue('Slack', 'url') + config_reader.getIniValue('Slack', 'channel') + '/' + config_reader.getIniValue('Slack', 'key')  
  headers = {
    "content-type": "application/json"
  }
  lParams = {
      'text': message
  }

  print('Sending restcall to ' + lChannelUrl + ' Message: ' + message)

  response = requests.post(url=lChannelUrl, headers=headers, json=lParams, timeout=3)

  print(response)
