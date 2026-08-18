Библиотеки, удалённые из этой папки

Это каталог собранного клиента. Рядом с исполняемыми файлами игры лежали
сторонние рантайм-библиотеки; часть из них удалена из публикации.

FMOD Ex (Firelight Technologies) — 12 файлов
    fmodex.dll, fmodex64.dll, fmodexL.dll, fmodexL64.dll
    fmod_event.dll, fmod_event64.dll, fmod_eventL.dll, fmod_eventL64.dll
    fmod_event_net.dll, fmod_event_net64.dll, fmod_event_netL.dll,
    fmod_event_netL64.dll
    Звуковой движок игры: воспроизведение эффектов и музыки, событийная
    система, сетевой аудит звука (варианты с суффиксом L — с логированием,
    с 64 — 64-разрядные).
    Удалены: коммерческое middleware, требует лицензии Firelight.
    Игровые звуковые банки (.fev/.fsb) остаются в Data/Audio — это контент
    проекта. Подробности: pw/branches/r1117/Vendor/fmod/README.txt

detoured.dll (Microsoft Detours)
    Перехват вызовов Win32 API. Удалён: проприетарная библиотека Microsoft
    Research. Подробности: pw/branches/r1117/Vendor/Detour/README.txt

dbghelp.dll (Microsoft)
    Разбор аварийных дампов и стеков вызовов при падениях клиента.
    Удалён: компонент Debugging Tools for Windows.
    Подробности: pw/branches/r1117/Vendor/DTW/README.txt

Что осталось в папке
    Распространяемые компоненты, которые Microsoft и NVIDIA разрешают
    поставлять вместе с приложением: Microsoft.VC90.CRT (msvcr90, msvcp90,
    msvcm90), D3DCompiler_43.dll, d3dx9_43.dll, cudart32_40_17.dll,
    а также nvtt.dll (NVIDIA Texture Tools, открытая лицензия).

Как собрать работоспособного клиента
    Вернуть FMOD нужной версии по своей лицензии с fmod.com; без него
    клиент запустится, но звука не будет. Detours и dbghelp нужны только
    для отладки и сбора отчётов о падениях.
