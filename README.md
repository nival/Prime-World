## Prime World
Исходный код боевой части игры Prime World.
Внимательно ознакомтесь с условиями лицензионного соглашения.

## Содержимое
- pw - основной код боевой части
- pw_publish - собранный клиент боевой части с читами и редактор для клиента

## Подготовка. 
Нужно выкачать ветку pw и объеденить Bin папку с основными данными игры.
1. Переключитесь на ветку `pw`
2. Скопируйте папку `Prime-World\pw_publish\branch\Client\PvP\Bin в PW-Battle\pw\branches\r1117` с заменой файлов.
2. Запустите клиент с читами `Prime-World\pw\branches\r1117\Bin\PW_Game.exe`

Если клиент запущен успешно - все сделано правильно.

В случе возникновения ошибок - смотрите в логи `Prime-World\pw\branches\r1117\Bin\logs`.

## Данные игры
Данные редактируются через редактор.
Расположены в:
`Prime-World\pw\branches\r1117\Data`

## Редактор
Находится в:
`Prime-World\pw\branches\r1117\Bin\PF_Editor.exe`

При первом открытии редактора, нужно настроить путь к `Data`:
1. Tools -> File System Configuration
2. Add -> WinFileSystem
3. В качестве system root устанавливаем папку Data `Prime-World\pw\branches\r1117\Data`
4. Закрываем окна
5. В редакторе Views -> Object Browser и Views -> Properties Editor. Это две основные панели для редактирования данных.

Вкладки редактора можно перемещеать и закреплять.

## Клиент с читами
В репозитории собран и лежит клиент с читами:
`Prime-World\pw\branches\r1117\Bin\PW_Game.exe`