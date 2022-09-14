[< Back](README.md)

# 11. Introduction

* [Exercise 110: Set up development environment](#exercise-110)
* [Exercise 111: Enable a test and make it green](#exercise-111)
* [Exercise 112: Make both asserts run](#exercise-112)

## Exercise 110

### Set up development environment

* [Quick install](#quick-install)
* [Manual install](#manual-install)
* [Build](#build)
* [Troubleshoot](#troubleshoot)

#### Quick install

<details>
   <summary>Windows: <b>Chocolatey</b></summary>

PowerShell run as Admin

```bash
iex ((New-Object System.Net.WebClient).DownloadString('https://raw.githubusercontent.com/mod-cpp/pacman/main/dev/windows.ps1'))
```

</details>
<details>
   <summary>Windows: <b>WinGet</b></summary>

PowerShell run as Admin

```bash
iex ((New-Object System.Net.WebClient).DownloadString('https://raw.githubusercontent.com/mod-cpp/pacman/main/dev/windows_winget.ps1'))
```

</details>
<details>
   <summary>Ubuntu: <b>apt</b></summary>

```bash
bash <(curl -s https://raw.githubusercontent.com/mod-cpp/pacman/main/dev/ubuntu.sh)
```

</details>

#### Manual install

<details>
   <summary>Windows</summary>

* Follow the instructions to install cmake (3.22) from https://cmake.org/download/
* Install Visual Studio 2022 https://visualstudio.microsoft.com/
* Click "Modify" in the Visual Studio Installer and select "Desktop development with
  C++"
* Reboot your computer once that's done.
* [Install VS Code][5]

</details>

<details>
   <summary>MacOS</summary>

* Install clang by typing `xcode-select --install` in a terminal and following the
  instructions
* Install brew if you haven't already

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

* Install the build tools

```bash
brew install cmake ninja
```

* [Install VS Code][5]
* Follow the instructions for [Launching VSCode from the command line][4]

</details>

<details>
   <summary>Ubuntu 20.04 or newer</summary>

```bash
sudo apt install build-essential clang-12 cmake curl g++-10 git libgl1-mesa-dev libudev-dev libx11-dev libxi-dev libxrandr-dev ninja-build pkg-config tar unzip zip
```

#### Install Visual Studio Code

You can either download the package for VS Code from the [official website][5] or
by [adding the vscode repository][6] to your distribution's package manager.


</details>

<details>
   <summary>Fedora 33 or newer</summary>

```bash
sudo dnf install ninja-build SFML-devel libXi-devel libX11-devel libXrandr-devel mesa-libGL-devel systemd-devel
```

#### Install Visual Studio Code

You can either download the package for VS Code from the [official website][5] or
by [adding the vscode repository][7] to your distribution's package manager.

</details>

<details>
   <summary>FreeBSD 12 or newer</summary>

```bash
sudo pkg install catch cmake libfmt ninja sfml
```

Install VS Code

```bash
sudo pkg install vscode
```

</details>

#### Build

<details>
   <summary>VS Code</summary>

```bash
git clone https://github.com/mod-cpp/pacman.git
cd pacman
code .
```

* A dialog will appear saying "Do you trust the authors of the files in this folder?",
  select "Yes, I trust the authors".
* You will get a popup in the lower right hand corner asking "Do you want to install
  the recommended extensions for C++?" - click Install.
* Click on "No Configure Preset Selected" on the bottom status bar
* In the dropdown that appears select
   * either `x64-windows` (64 bit) or `x86-windows` (32
  bit).
  * `linux-gcc` on Linux
  * `macos` on MacOS
* Build by clicking on "Build" button on the bottom status bar.
* Wait until build is finished, it might take a while the first time because it is
  downloading and building the dependencies as well.
* Click on flask icon on the left vertical bar to open the test panel
* Run the tests by clicking on the run button on top of the test panel
* Run the game by clicking on the play button on the bottom status bar
* Select `pacman` in the dropdown
* To debug, click on the play button with a bug on it on the left vertical bar to open
  the debug panel
* Then click the play button on the top of the panel to run in the debugger.

</details>

<details>
   <summary>Commandline</summary>

Example for Ubuntu using the preset `linux-gcc`, for other platforms use the
appropriate preset, see [CMakePresets.json](../../CMakePresets.json).

```bash
git clone https://github.com/mod-cpp/pacman.git
cd pacman
cmake --preset linux-gcc -DCMAKE_BUILD_TYPE=Debug # configure
cmake --build --preset linux-gcc-build --config Debug # build
ctest --preset linux-gcc-test -C Debug # run tests
```

</details>

<details>
   <summary>CLion</summary>

* Clone project through "Get from VCS": https://github.com/mod-cpp/pacman.git
* In the "Open Project Wizard" unselect "Enable profile" for the "Debug" profile
* Select the profile(s) appropriate for your platform, example x64-windows-build for Windows 64 bit
* Enable the profile by checking the checkbox "Enable profile"
* Check the checkbox at the top of the dialog "Reload CMake project on editing CMakeLists.txt or other CMake configuration files"
* Click "OK"
* (If CLion created a `cmake-build-debug` folder you can safely delete it, we will be
  using the `build` directory)
* If you need to get back to this dialog, open Settings and go to: Build, Execution, Deployment > CMake 
* On the bottom of the CLion window you will see a tab called CMake
* To reload CMake fully, click on it and click on the cog wheel and select "Reset Cache and Reload Project"
* To run pacman press the green play button at the top right of the window
* To run in debug press the bug button to its right
* To run the tests click on the dropdown to its left and select "All CTest" and then either the run or the debug button.

</details>

#### Troubleshoot

<details>
   <summary>All</summary>

After installing the build tools, you may have to reboot your IDE and/or your Linux
session if you encounter any errors such as Ninja not being found by VSCode.

</details>

<details>
   <summary>Arch Linux</summary>

If there are opengl driver errors, try running in software mode

</details>

<details>
   <summary>Windows</summary>

* If you have issues with using VSCode, start it from the "Developer Command Prompt
  for VS 2022"
* (Windows Defender dialog for VSCode: "Allow access")

</details>

## [Exercise 111][1]

### Enable a test and make it green

Make sure you can run tests, so enable the test in the [cpp file][1], and make sure it
fails before you make it pass. Hint is in the comment over the test.

* Catch2 : [Special Tags][3]

```cpp
// HINT: To enable a test remove [.] from the tags on the test
TEST_CASE("Exercise 111 : Enable the test and make it green", "[.][11]") {
REQUIRE(true == false);
}
```

<details>
   <summary>Solution</summary>

```cpp
TEST_CASE("Exercise 111 : Enable a test and make it green", "[11]") {
  REQUIRE(true == true);
}
```

</details>

## [Exercise 112][1]

### Make both asserts run (distinguish between REQUIRE and CHECK in Catch2)

Enable the test and see you will only get one error. Look up REQUIRE and CHECK in
Catch2 and change the code in [the test][1], so you get an error on both lines.

Then fix both errors by making both sides of the == the same.

* Catch2 : [Assertion Macros][2]

```cpp
// HINT: https://github.com/catchorg/Catch2/blob/v2.x/docs/assertions.md
TEST_CASE("Exercise 112 : Make both asserts run (distinguish between REQUIRE and CHECK in Catch2)", "[.][11]") {
  REQUIRE(true == false);
  CHECK(false == true);
}
```

<details>
   <summary>Solution</summary>

```cpp
TEST_CASE("Exercise 112 : Make both asserts run (distinguish between REQUIRE and CHECK in Catch2)", "[11]") {
  CHECK(true == true);
  CHECK(true == true);
}
```

</details>

[1]: 11_exercises.cpp
[2]: https://github.com/catchorg/Catch2/blob/v2.x/docs/assertions.md
[3]: https://github.com/catchorg/Catch2/blob/v2.x/docs/test-cases-and-sections.md#special-tags
[4]: https://code.visualstudio.com/docs/setup/mac#_launching-from-the-command-line
[5]: https://code.visualstudio.com/download
[6]: https://code.visualstudio.com/docs/setup/linux#_debian-and-ubuntu-based-distributions
[7]: https://code.visualstudio.com/docs/setup/linux#_rhel-fedora-and-centos-based-distributions
