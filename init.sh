#!/bin/bash

# Создание папки build
mkdir build

# Переход в папку build
cd build

# Выполнение команды cmake и make
cmake .. && make
