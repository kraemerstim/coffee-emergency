#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import configparser

#Konstanten

def getFilePath(aFilePath):
  return os.path.join(os.path.dirname(__file__), aFilePath)
    
def setIniFile(aFilePath='config.ini'):
  if os.path.isfile(getFilePath(aFilePath)):
    config.read(os.path.join(os.path.dirname(__file__), aFilePath))
  
def initialize():
  global config
  config = configparser.ConfigParser()
  setIniFile()
  
def getIniValue(aSection, aKey):
  return config.get(aSection, aKey, fallback='')
  