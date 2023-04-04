# C++ Tic-Tac-Toe

[![CI](https://github.com/Toxe/tic-tac-toe/workflows/CI/badge.svg)](https://github.com/Toxe/tic-tac-toe/actions)

Tic-Tac-Toe in C++ using Minimax with alpha-beta pruning.

## Dependencies

- CMake
- Vcpkg

## Build

Example build instructions for CMake and Vcpkg. These examples assume that Vcpkg is installed in your home directory.
Adjust the paths if necessary.

This will build three binaries: The main binary and tests.

#### Vcpkg toolchain

Pass the Vcpkg toolchain file via `CMAKE_TOOLCHAIN_FILE`.

- Windows: `-DCMAKE_TOOLCHAIN_FILE=%HOMEPATH%\vcpkg\scripts\buildsystems\vcpkg.cmake`
- Unix systems: `-DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake`

### Linux & Mac

```
$ mkdir build
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake -B build
$ cmake --build build
```

### Windows

```
PS> mkdir build
PS> cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="$HOME\vcpkg\scripts\buildsystems\vcpkg.cmake" -B build
PS> cmake --build build --config Release
```

## Human vs. AI

```
+---+---+---+
|   |   |   | 1
+---+---+---+
|   |   |   | 2
+---+---+---+
|   |   |   | 3
+---+---+---+
  A   B   C

Player X, your move? (type "?" for help)
? help

Enter moves like "c2" or "2c".

(?), (h), (help): show help
(q), (quit), (exit): quit program
(u), (undo): undo last command
(r), (redo): redo last undo

+---+---+---+
|   |   |   | 1
+---+---+---+
|   |   |   | 2
+---+---+---+
|   |   |   | 3
+---+---+---+
  A   B   C

Player X, your move? (type "?" for help)
? a1
> player X move: A1

+---+---+---+
| X |   |   | 1
+---+---+---+
|   |   |   | 2
+---+---+---+
|   |   |   | 3
+---+---+---+
  A   B   C

> calculated 2788 moves in 0.351 ms (depth: 8)
> player O move: B2

+---+---+---+
| X |   |   | 1
+---+---+---+
|   | O |   | 2
+---+---+---+
|   |   |   | 3
+---+---+---+
  A   B   C

Player X, your move? (type "?" for help)
? c1
> player X move: C1

+---+---+---+
| X |   | X | 1
+---+---+---+
|   | O |   | 2
+---+---+---+
|   |   |   | 3
+---+---+---+
  A   B   C

> calculated 121 moves in 0.019 ms (depth: 6)
> player O move: B1

+---+---+---+
| X | O | X | 1
+---+---+---+
|   | O |   | 2
+---+---+---+
|   |   |   | 3
+---+---+---+
  A   B   C

Player X, your move? (type "?" for help)
? b3
> player X move: B3

+---+---+---+
| X | O | X | 1
+---+---+---+
|   | O |   | 2
+---+---+---+
|   | X |   | 3
+---+---+---+
  A   B   C

> calculated 29 moves in 7.300 us (depth: 4)
> player O move: A2

+---+---+---+
| X | O | X | 1
+---+---+---+
| O | O |   | 2
+---+---+---+
|   | X |   | 3
+---+---+---+
  A   B   C

Player X, your move? (type "?" for help)
? c2
> player X move: C2

+---+---+---+
| X | O | X | 1
+---+---+---+
| O | O | X | 2
+---+---+---+
|   | X |   | 3
+---+---+---+
  A   B   C

> calculated 5 moves in 3.300 us (depth: 2)
> player O move: C3

+---+---+---+
| X | O | X | 1
+---+---+---+
| O | O | X | 2
+---+---+---+
|   | X | O | 3
+---+---+---+
  A   B   C

Player X, your move? (type "?" for help)
? a3
> player X move: A3

+---+---+---+
| X | O | X | 1
+---+---+---+
| O | O | X | 2
+---+---+---+
| X | X | O | 3
+---+---+---+
  A   B   C

Draw!
```

## AI vs. AI

```
+---+---+---+
|   |   |   | 1
+---+---+---+
|   |   |   | 2
+---+---+---+
|   |   |   | 3
+---+---+---+
  A   B   C

> calculated 20866 moves in 2.309 ms (depth: 9)
> player X move: A1

+---+---+---+
| X |   |   | 1
+---+---+---+
|   |   |   | 2
+---+---+---+
|   |   |   | 3
+---+---+---+
  A   B   C

> calculated 2788 moves in 0.320 ms (depth: 8)
> player O move: B2

+---+---+---+
| X |   |   | 1
+---+---+---+
|   | O |   | 2
+---+---+---+
|   |   |   | 3
+---+---+---+
  A   B   C

> calculated 871 moves in 0.099 ms (depth: 7)
> player X move: B1

+---+---+---+
| X | X |   | 1
+---+---+---+
|   | O |   | 2
+---+---+---+
|   |   |   | 3
+---+---+---+
  A   B   C

> calculated 75 moves in 9.200 us (depth: 6)
> player O move: C1

+---+---+---+
| X | X | O | 1
+---+---+---+
|   | O |   | 2
+---+---+---+
|   |   |   | 3
+---+---+---+
  A   B   C

> calculated 64 moves in 0.010 ms (depth: 5)
> player X move: A3

+---+---+---+
| X | X | O | 1
+---+---+---+
|   | O |   | 2
+---+---+---+
| X |   |   | 3
+---+---+---+
  A   B   C

> calculated 17 moves in 3.200 us (depth: 4)
> player O move: A2

+---+---+---+
| X | X | O | 1
+---+---+---+
| O | O |   | 2
+---+---+---+
| X |   |   | 3
+---+---+---+
  A   B   C

> calculated 10 moves in 2.200 us (depth: 3)
> player X move: C2

+---+---+---+
| X | X | O | 1
+---+---+---+
| O | O | X | 2
+---+---+---+
| X |   |   | 3
+---+---+---+
  A   B   C

> calculated 5 moves in 1.600 us (depth: 2)
> player O move: B3

+---+---+---+
| X | X | O | 1
+---+---+---+
| O | O | X | 2
+---+---+---+
| X | O |   | 3
+---+---+---+
  A   B   C

> calculated 2 moves in 0.900 us (depth: 1)
> player X move: C3

+---+---+---+
| X | X | O | 1
+---+---+---+
| O | O | X | 2
+---+---+---+
| X | O | X | 3
+---+---+---+
  A   B   C

Draw!
```
