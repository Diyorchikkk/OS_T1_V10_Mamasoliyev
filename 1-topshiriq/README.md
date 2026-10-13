# 1-topshiriq: C tili asoslari, kompilyatsiya va pointerlar

Operatsion tizimlar — 1-topshiriq, 10-variant.
Bajardi: Mamasoliyev Diyorbek

Muhit: Kali Linux (aarch64), GCC 15.2.0

## Fayllar

| Fayl | Tavsif |
|---|---|
| `hello.c` | A qism: "Hello, World!" manba kodi |
| `hello.i` | A qism: preprotsessor natijasi (`gcc -E`) |
| `hello.s` | A qism: assembly kod (`gcc -S`) |
| `hello.o` | A qism: obyekt fayl (`gcc -c`) |
| `hello` | A qism: bajariluvchi fayl (linking) |
| `masala1.c` | B qism, 1-masala: o'nlik sonni 2, 8, 16 lik sistemalarga o'tkazish |
| `masala2.c` | B qism, 2-masala: xuddi shu, `void otkaz(int n, int asos, char *buf)` va pointerlar bilan |

## A qism: kompilyatsiya bosqichlari

```bash
gcc -E hello.c -o hello.i    # 1. preprotsessor
gcc -S hello.i -o hello.s    # 2. kompilyator (assembly)
gcc -c hello.s -o hello.o    # 3. assembler (obyekt fayl)
gcc hello.o -o hello         # 4. linker (bajariluvchi fayl)
./hello
```

## B qism: kompilyatsiya va ishga tushirish

```bash
gcc -Wall -Wextra masala1.c -o masala1
./masala1

gcc -Wall -Wextra masala2.c -o masala2
./masala2
```
