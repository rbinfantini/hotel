# KLPR Hotel — Reservation & Occupancy Manager

A console application written in C to manage reservations and occupancy for a 20-floor hotel with 14 apartments per floor (280 rooms). Made as a group project for the Introduction to Computing Lab course (Computer Science, PUC-SP, 2025).

> The program interface (menus and messages) is in Brazilian Portuguese.

## Features

- Check-in, with or without a prior reservation
- Check-out
- Make and cancel reservations
- Guest registration (CPF, name, address, phone, e-mail)
- Apartment lookup (status and guest data)
- ASCII occupancy map of the whole hotel
- Occupancy and reservation rates

Guests are verified by CPF (Brazilian taxpayer ID) on check-in of a reserved room, check-out and cancellation.

Each apartment is shown on the map as:

| Symbol | Meaning  |
|:------:|----------|
| `.`    | Free     |
| `R`    | Reserved |
| `O`    | Occupied |

The project deliberately ignores dates: it only tracks the hotel's current state.

## How to run

**Dev-C++:** open `Hotel.cpp`, compile and run (F11). Use a maximized console window so the map fits.

**Command line:**

```bash
gcc -x c -std=gnu99 Hotel.cpp -o hotel
./hotel
```

The code is plain C (it only uses `stdio.h` and `string.h`), so compile it as C. Recent versions of `g++` may build it but the program can crash.

## Known limitations

- Uses `gets()`, which is unsafe and removed from newer C standards
- No input validation (typing letters at a numeric prompt makes the menu loop forever)
- Data is kept in memory only and is lost when the program exits
- The occupancy-rate `printf` format is malformed and may print stray characters on some platforms

## Authors

- Kauã Bezerra Brito
- Livia de Aguiar Almeida Figueiredo
- Pedro Chagas Neves de Farias Nascimento
- Rafael Barros Infantini
