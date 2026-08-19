# Сторонние компоненты UniFlash

Ниже перечислено всё стороннее, что входит в состав UniFlash, с указанием авторства и лицензий. Файл носит информационный характер и не отменяет условий перечисленных лицензий.

Текст GNU General Public License версии 2 (официальный, с gnu.org) лежит в `Deps/Libs/LICENSE-GPL-2.0.txt` — он относится к обеим библиотекам ниже.

## Библиотеки в `Deps/Libs`

### SharpZipLib 0.81.0.1407 (`SharpZipLib.dll`)

- Правообладатель: Mike Krueger, 2001–2004 (`LegalCopyright` сборки), проект `#ZipLibrary` / ICSharpCode.
- Лицензия: GNU General Public License v2 с исключением для линковки — исключение прямо разрешает связывать библиотеку с независимыми модулями и распространять полученный исполняемый файл на любых условиях. На MIT проект перешёл начиная с версии 1.0, к версии 0.81 это не относится.
- Источники: <https://github.com/icsharpcode/SharpZipLib>, <http://icsharpcode.github.io/SharpZipLib/legacy.html>

### SwfDotNet.IO 0.9.0.42093 (`SwfDotNet.IO.dll`)

- Автор: Olivier Carpentier (SwfDotNet) для Adelina foundation; включает наработки библиотеки SwfOp, Florian Krüsch, 2004.
- Лицензия: заголовки исходных файлов библиотеки ссылаются на GNU General Public License, называя при этом «version 2.1 of the License, or (at your option) any later version». Номер 2.1 принадлежит LGPL, а не GPL, поэтому формулировка первоисточника внутренне противоречива; полный текст лицензии распространялся в файле `Licence.cs` библиотеки.
- Источник: <https://sourceforge.net/projects/swfdotnet/>

Та же сборка `SwfDotNet.IO.dll` (идентичная побайтово) уже входит в состав каталога `FlashUI` этого репозитория.

## Алгоритмы в исходном коде

### Easing equations, Robert Penner

- Файл: `Core/Src/Tweens/Easing.cs`, ссылка на первоисточник сохранена в комментарии к классу.
- Правообладатель: Robert Penner, 2001.
- Лицензия: MIT и 3-Clause BSD (на выбор). Оба варианта требуют сохранения указания авторства при распространении исходного кода и в сопроводительных материалах бинарных сборок.
- Источник: <https://robertpenner.com/easing_terms_of_use.html>

## Внешние спецификации, на которые ссылается код

Ссылки оставлены в комментариях как указание на первоисточник алгоритмов и не являются включённым в состав кодом:

- `Core/Src/Display/TextField/FontDataTTF.cs` — спецификация TrueType (Microsoft) и TrueType Reference Manual (Apple).
- `Core/Src/Tweens/Tween.cs` — описание класса Tween из AS3.
- `Core/Src/Events/FlashInput.cs` — ответ на Unity Answers про обработку модификаторов клавиатуры.
