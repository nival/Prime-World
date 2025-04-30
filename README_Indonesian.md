[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Prime World Trailer](PW_trailer.png)](https://youtu.be/Fkd-zva4npI)
[Prime World](https://wikipedia.org/wiki/Prime_World) adalah permainan multiplayer online battle arena (MOBA) yang dirilis pada tahun 2014. Game ini dikembangkan menggunakan game engine internal oleh perusahaan [Nival](http://nival.com/), yang sebagian besar ditulis dalam bahasa C++.

Permainan ini terdiri dari dua bagian: Kastil dan Pertempuran. Pemain berperan sebagai Lord atau Lady. Di Kastil, pemain membangun bangunan, merekrut Hero, dan memilih Talent untuk mereka. Pada bagian Pertempuran, pemain mengendalikan Hero dan menggunakan Talent untuk bertarung melawan pemain lain dalam pertempuran tim.

Pada tahun 2024, kode sumber bagian Pertempuran dari game ini dirilis di bawah [lisensi khusus](LICENSE.md), yang melarang penggunaan komersial namun sepenuhnya terbuka bagi komunitas game, untuk studi, dan tujuan penelitian.
Harap baca syarat [perjanjian lisensi](LICENSE.md) dengan seksama sebelum menggunakan.

## Apa yang ada di repositori ini
- `pw` — kode utama bagian pertempuran
- `pw_publish` — klien bagian pertempuran yang sudah dikompilasi dengan kode curang dan editor klien
- `pw/branches/r1117/Bin/PF_Editor.exe` — editor data game

## Persiapan
Anda perlu mengunduh data dari repositori ini dan menggabungkan folder `Bin` dengan data utama game. Berikut caranya:

1. Salin folder `pw_publish/branch/Client/PvP/Bin` ke `pw/branches/r1117`, ganti file yang sudah ada.
2. Jalankan klien dengan kode curang `pw/branches/r1117/Bin/PW_Game.exe`.
3. Jika berhasil, Anda akan melihat jendela loading, namun tanpa gambar dan layar hitam.
4. Pada folder `Profiles -> game.cfg`, ubah nilai `local_game 0` menjadi `local_game 1`.
5. Jalankan klien dengan kode curang. Sekarang Anda akan melihat lobi di mana Anda dapat memilih peta, hero, dan memulai pertempuran.
6. Dalam game, tekan tombol Tilde (~) pada keyboard, dan Anda akan melihat konsol untuk memasukkan kode curang.

Jika terjadi kesalahan, periksa file log di `pw/branches/r1117/Bin/logs`.

## Data Game
Data dapat diedit melalui editor dan terletak di `pw/branches/r1117/Data`

Dengan mengedit data, Anda dapat:
1. Mengubah deskripsi talent dan kemampuan hero.
2. Mengubah talent dan kemampuan hero.
3. Mengubah logika creep dan tower.
4. Menambahkan hero dan kemampuan baru.
5. Menambahkan talent baru.
6. Mengubah dan menambahkan efek.
7. Mengubah dan menambahkan model serta animasi.

Ketika mengubah data, Anda tidak perlu membangun klien baru dari kode. Cukup tekan `File -> Save`, dan semua perubahan langsung muncul di klien game `PW_Game`. Sebagai contoh, Anda dapat mencoba mengubah deskripsi talent atau kemampuan hero tertentu.

## Editor Data Game
Editor data game berada di `pw/branches/r1117/Bin/PF_Editor.exe`

Saat pertama membuka editor, Anda perlu mengatur path ke `Data`:
1. `Tools -> File System Configuration`.
2. `Add -> WinFileSystem`.
3. Atur folder Data sebagai system root: `pw/branches/r1117/Data`.
4. Tutup jendela.
5. Di editor: `Views -> Object Browser` dan `Views -> Properties Editor`. Ini adalah dua panel utama untuk mengedit data.

Tab editor dapat dipindahkan dan ditempatkan sesuai keinginan.

## Klien Game dengan Kode Curang
Di repositori, Anda dapat menemukan klien game yang sudah dikompilasi dengan kode curang `pw_publish/branch/Client/PvP/Bin/PW_Game.exe`

Anda harus memiliki folder `Localization`, `Profiles`, dan `Data` di samping folder `Bin`. Oleh karena itu, saat persiapan, perlu dipindahkan ke folder `pw`. Jika ada perubahan pada kode, klien harus dikompilasi ulang.

## Cara Menjalankan PvP
1. Pada `Profiles -> game.cfg`, ubah `local_game 0`.
2. Tambahkan `login_adress <server address>`.
3. Jalankan game dengan parameter `-dev_login MyNickname`.

## Cara Menjalankan Game dengan Bot
1. Ganti nama file `Profiles -> private.cfg_example` menjadi `private.cfg`.
2. Buka file tersebut dengan Notepad.
3. Cari `AT BEGINNING GAME`.
4. Tambahkan baris baru: `add_ai bots` — ini akan menetapkan bot AI untuk setiap hero dalam game.

## Pemecahan Masalah yang Mungkin Terjadi
1. Ganti nama file `Profiles -> private.cfg_example` menjadi `private.cfg`.
2. Buka file dengan Notepad.
3. Cari bagian `performance section`.
4. Temukan baris `setvar gfx_fullscreen = 0` — ini akan membuat game berjalan dalam mode windowed, biasanya lebih stabil.
5. Pengaturan optimasi lain juga dapat diubah di bagian `performance section`.

## Ucapan Terima Kasih
Untuk komunitas **Prime World: Nova** atas kontribusi mereka pada dokumentasi dan perbaikan bug.
