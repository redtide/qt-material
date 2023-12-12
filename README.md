# Material Widgets for Qt

[![Language]]()
[![CI]](https://github.com/redtide/qt-material-widgets/actions/workflows/build.yml)

*** Work in progress ***

This project' development is not yet complete and API needs to be defined, but quite usable.
Contributions are welcome.

## Overview

Material Widgets for Qt is a C++ widgets library that can be used on any supported operating system,
including Android, where usually only QML gives a native appearance.

## Changes

There are several changes compared to the [original repository]:

- API changes, with some removals (see below).
- Changed the directory structure, headers are separated from implementation files.
- Material 3.
- Removed all color getters/setters; this version is meant to work via QStyle and palettes,
  not using stylesheets nor setting colors directly per widget.
  Custom colors should be prepared in a custom palette instead.
  The style is not ready, so the palette is fixed to light / dark defaults.
- Code style.

## Features

- Qt5/6 support
- Qt Designer plugin
- Light/Dark color scheme

## Dependencies

### Runtime

- Qt5/6 base

### Qt6 only

- qt6-scxml (QStateMachine)

### Build

- CMake
- Qt Linguist Tools
- Git (optional, to pull latest VCS checkouts)

## Build

`CMAKE_BUILD_TYPE` is usually set to `Release`, though `None` might be a valid [alternative].<br>
`CMAKE_INSTALL_PREFIX` has to be set to `/usr` on most operating systems.<br>
Using `sudo make install` is discouraged, instead use the system package manager where possible.

```bash
cmake -B build -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr -W no-dev
cmake --build build --verbose
DESTDIR="$(pwd)/package" cmake --install build
```

## License

Licensed under the [BSD-3-Clause] license.

[alternative]:         https://wiki.archlinux.org/title/CMake_package_guidelines#Fixing_the_automatic_optimization_flag_override
[BSD-3-Clause]:        COPYING
[CI]:                  https://github.com/redtide/sddm-conf/actions/workflows/build.yml/badge.svg
[Language]:            https://img.shields.io/badge/language-c++-brightgreen.svg
[original repository]: https://github.com/laserpants/qt-material-widgets/
