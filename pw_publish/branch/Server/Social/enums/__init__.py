#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Генератор кода создаёт отдельный .py файлик под каждый enum, который используется в соответствующем C# файле.
# Для каждого файла, из которого мы генерим данные, автоматически создаётся свой импорт-файл (_init<имя .cs файла>.py).
# Чтобы можно было импортировать все enums просто через "from enums import * ", надо в текущий файл включить все автогенерённые _init<имя .cs файла>.py

from ._initModelData import *
from ._initGuildData import *
from ._initGuildMapData import *
from ._initGuildWarsData import *
