Steamworks SDK и клиент Steam (Valve) — УДАЛЕНО ИЗ ПУБЛИКАЦИИ

Что здесь лежало
    Steam SDK версии 1.23a целиком, 213 файлов:
        redistributable_bin/ — steam_api.dll, Steam.dll, tier0_s.dll и заголовки
        client/ — steam.exe, исполняемый клиент Steam
        tools/goldmaster/ — SteamService.exe, Setup.exe, инструменты выпуска сборок
        public/steam/*.h — заголовки Steamworks API

Для чего использовалось
    Интеграция со Steam: авторизация игрока, достижения, статистика,
    покупки, доставка обновлений через Steam. Код интеграции Prime World
    остаётся в репозитории — удалён только SDK Valve.

Почему удалено
    Steamworks SDK предоставляется разработчикам по отдельному соглашению
    с Valve и не может распространяться публично. Клиент Steam и
    инструменты goldmaster — тем более: это дистрибутив Valve целиком.

Как восстановить для сборки
    Steamworks SDK загружается партнёром Valve из Steamworks Partner Site
    (partner.steamgames.com) и распаковывается в эту папку.
