[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Prime World Trailer](PW_trailer.png)](https://youtu.be/Fkd-zva4npI)
[Prime World](https://wikipedia.org/wiki/Prime_World)は、2014年にリリースされたマルチプレイヤーオンラインバトルアリーナ（MOBA）ゲームです。このゲームは[Nival](http://nival.com/)社の自社製ゲームエンジン上で開発され、主にC++で書かれています。

ゲームは「キャッスル」と「バトルパート」の2つの部分から構成されています。プレイヤーはロードまたはレディとしてプレイします。キャッスルでは、プレイヤーは建物を建設し、ヒーローを雇い、各ヒーローのためにタレントを選びます。バトルパートでは、プレイヤーはヒーローを操作し、タレントを使って他のプレイヤーとチーム戦を行います。

2024年、ゲームのバトルパートのソースコードが[特別ライセンス](LICENSE.md)の下で公開され、商業利用は禁止されていますが、ゲームコミュニティ、学習、研究目的には完全に開放されています。
利用する前に、必ず[ライセンス契約](LICENSE.md)の条件をよく読んでください。

## このリポジトリに含まれているもの
- `pw` ― バトルパートの主なコード
- `pw_publish` ― チートコードおよびクライアントエディタ付きのバトルパートのコンパイル済みクライアント
- `pw/branches/r1117/Bin/PF_Editor.exe` ― ゲームデータエディタ

## 準備
本リポジトリからデータをダウンロードし、`Bin`フォルダをゲームのメインデータと統合する必要があります。手順は以下の通りです：

1. `pw_publish/branch/Client/PvP/Bin`フォルダを`pw/branches/r1117`にコピーし、既存のファイルを上書きしてください。
2. チートコード付きクライアント`pw/branches/r1117/Bin/PW_Game.exe`を実行します。
3. 正常に動作していれば、画像のない黒い画面のローディングウィンドウが表示されます。
4. `Profiles -> game.cfg`フォルダ内で、`local_game 0`の値を`local_game 1`に変更します。
5. 再度チートコード付きクライアントを起動します。今度はマップやヒーローを選んでバトルを開始できるロビー画面が表示されるはずです。
6. ゲーム中にキーボードのチルダ（~）キーを押すと、チートコード入力用のコンソールが表示されます。

エラーが発生した場合は、`pw/branches/r1117/Bin/logs`内のログファイルを確認してください。

## ゲームデータ
データはエディタで編集でき、`pw/branches/r1117/Data`に格納されています。

データを編集することで以下が可能です：
1. ヒーローのタレントやアビリティの説明文を変更する
2. ヒーローのタレントやアビリティ自体を変更する
3. クリープやタワーのロジックを編集する
4. 新しいヒーローやアビリティを追加する
5. 新しいタレントを追加する
6. エフェクトの追加や変更
7. モデルやアニメーションの追加や変更

データを変更した場合、新たにクライアントをコードからビルドし直す必要はありません。`File -> Save`をクリックすれば、全ての変更が即座にゲームクライアント`PW_Game`に反映されます。例として、特定のタレントやヒーローアビリティの説明を変更してみてください。

## ゲームデータエディタ
ゲームデータエディタは`pw/branches/r1117/Bin/PF_Editor.exe`にあります。

初めてエディタを開く際は、`Data`へのパスを設定してください：
1. `Tools -> File System Configuration`を選択
2. `Add -> WinFileSystem`をクリック
3. system rootとして`pw/branches/r1117/Data`フォルダを設定
4. ウィンドウを閉じる
5. エディタ内で`Views -> Object Browser`と`Views -> Properties Editor`を開く（これがデータ編集の主な2つのパネルとなります）

エディタのタブは移動・ドッキングが可能です。

## チートコード付きゲームクライアント
リポジトリ内にはチートコード内蔵のコンパイル済みゲームクライアント`pw_publish/branch/Client/PvP/Bin/PW_Game.exe`があります。

`Bin`フォルダの隣に`Localization`、`Profiles`、`Data`の各フォルダが必要です。そのため、準備時には`pw`フォルダ内へ移動してください。コードを変更した場合は、クライアントの再ビルドが必要です。

## PvPの起動方法
1. `Profiles -> game.cfg`で`local_game 0`を変更
2. `login_adress <server address>`を追加
3. パラメータ`-dev_login MyNickname`でゲームを起動

## ボット戦での起動方法
1. `Profiles -> private.cfg_example`ファイル名を`private.cfg`に変更
2. テキストエディタで開く
3. `AT BEGINNING GAME`を探す
4. 新しい行として`add_ai bots`を追加（これで各ヒーローにAIボットが割り当てられます）

## 発生しうるエラーの対処法
1. `Profiles -> private.cfg_example`を`private.cfg`にリネーム
2. テキストエディタで開く
3. `performance section`セクションを探す
4. `setvar gfx_fullscreen = 0`の行を探す―これでウィンドウモードで起動でき、より安定する場合があります
5. 他の最適化設定も`performance section`内で変更可能です

## 謝辞
**Prime World: Nova**コミュニティの皆様、ドキュメントへの貢献やエラー修正に感謝します。
