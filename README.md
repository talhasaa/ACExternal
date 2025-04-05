# ACExternal
An external cheat for Assault Cube with ImGui overlay.

# Features

- Value Editing (Health, Armor and ammo values)
- Customizable ESP
- Customizable AimBot

The AimBot is activated by holding down either Left Click or Left Ctrl.

# Showcase

[![Showcase](https://img.youtube.com/vi/o_ry8-986T0/maxresdefault.jpg)](https://www.youtube.com/watch?v=o_ry8-986T0)

# How to build

You can use `git clone` to clone the repository.
You need to have [CMake](https://cmake.org/getting-started/), [vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/overview), [MinGW compiler](https://code.visualstudio.com/docs/cpp/config-mingw) and [Ninja](https://ninja-build.org) installed.

**Make sure to edit the `CMakePresets.json` file before compiling.**

To build for release:

- Run `cmake --preset=release` first,
- Then run `cmake --build --preset release` to build

# Contact

Feel free to contact me if you have any questions or issues.

Discord: @talhasa
