Файлы Autodesk, удалённые из этой папки

Что здесь лежало
    blindDataShader/blindDataMesh.cpp, blindDataMesh.h, blindDataShader.mel
    cvColorShader/CVCS.cpp
    Все четыре несут шапку "Copyright (C) 1995 - 2006 Autodesk, Inc.
    and/or its licensors. All rights reserved. The coded instructions,
    statements, computer programs, and/or related material ... contain
    unpublished information proprietary to Autodesk" — это примеры
    из состава Maya devkit, а не код проекта.

Для чего использовалось
    Основа плагинов-шейдеров для Maya: отображение blind data на меше
    и раскраска вершин по цвету. Плагины применялись при подготовке
    геометрии уровней и персонажей.

Почему удалено
    Это код Autodesk с явной пометкой о проприетарности, а не код Nival.
    Правило чистки, записанное в pw/branches/r1117/Vendor/Maya/README.txt,
    гласит: остаются исходники плагинов Nival, удаляется всё, что
    принадлежит Autodesk. Эти четыре файла ему не отвечали.

Что осталось
    Остальной код MayaExtension — разработки проекта: bindFile (чтение
    и запись собственных бинарных форматов), экспортёры и вспомогательные
    утилиты. Для сборки понадобятся примеры devkit нужной версии Maya,
    доступные обладателю лицензии Autodesk.
