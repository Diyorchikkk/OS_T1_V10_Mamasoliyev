# 2-topshiriq: Pointerlar va dinamik xotira

Operatsion tizimlar — 2-topshiriq (Pointerlar va dinamik xotira), 10-variant.
Bajardi: Mamasoliyev Diyorbek

Muhit: Kali Linux (aarch64), GCC 15.2.0, Valgrind 3.27.1

## Topshiriq

Dinamik massivdan juft va toq sonlarni ikkita yangi, aniq o'lchamli dinamik massivga ajratish.

## Fayllar

| Fayl | Tavsif |
|---|---|
| `main.c` | Dastur manba kodi |
| `valgrind.txt` | Oddiy ishga tushirishdagi valgrind natijasi |
| `valgrind_xato.txt` | Xato kiritishdagi valgrind natijasi (xotira baribir bo'shatiladi) |

## Kompilyatsiya va ishga tushirish

    gcc -Wall -Wextra main.c -o main
    ./main

## Valgrind bilan tekshirish

    valgrind --leak-check=full --log-file=valgrind.txt ./main
    cat valgrind.txt
