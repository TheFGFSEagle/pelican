# Pelican
Graphical video clip managing tool. Supports tagging, adding metadata, showing recording location on a map (if GPS info is included in the files), viewing frame by frame, grid preview of clip frames in user-specifiable intervals (to quickly search clip contents), etc.

## About the name
Pelican is a blend word from `pelicula` (spanish for movie) and `man` (abbreviation for manager).

## Installation
1. Clone this repo
2. `cd` into the cloned directory
3. Create a build folder
4. `cd` into build folder
5. Configure with CMake
6. Build with CMake
7. Install with CMake

 ```sh
 git clone https://github.com/TheFGFSEagle/pelican
 cd pelican
 mkdir build
 cd build
 cmake ..
 cmake --build .
 sudo cmake --install . --prefix /usr
 ```
 
## System dependencies
* [FreeImagePlus](https://github.com/imazen/freeimage)
* [Exiv2](https://github.com/Exiv2/exiv2)
* [{fmt}](https://github.com/fmtlib/fmt)
* [Pystring](https://github.com/imageworks/pystring)

Command for installing these dependencies on Ubuntu:
```sh
sudo apt install libpystring-dev libexiv2-dev libfreeimageplus-dev libfmt-dev
```

*Note*: at the time of writing, the version of Pystring in the Ubuntu package repositories seems to be out of date, causing a compile error.
This can be solved by copying the header file pystring.h from the repository to /usr/include/pystring/pystring.h, overwriting the system file.


