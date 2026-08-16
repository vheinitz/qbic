# qbic — a programming environment for children 🧩

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-blue.svg)](#)

A **programming environment for children**, part of the author's KiKu
educational series. Children compose programs from visual **pieces**
(`pieceslist`, `prog`) and watch them run in a **runtime simulator**
(`runtime_sim`) with a waste box for incorrect pieces — a playful introduction
to sequencing and logic.

## What it offers

- **Pieces list** — a palette of command blocks (`pieceslist`, `prog`).
- **Program composition** — arrange/order pieces to build a program.
- **Runtime simulation** — step through and watch the program execute
  (`runtime_sim`).
- **Waste box** — a friendly place for pieces that don't belong (`wastebox`),
  making trial-and-error safe.

## Requirements

- Qt (Widgets), C++ compiler

## Build

```bash
cd src
qmake && make
```

## License

[MIT](LICENSE) © Valentin Heinitz

Part of the broader [KiKu educational work](../kiku_robotics).
