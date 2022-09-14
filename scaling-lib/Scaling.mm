/*
This is an Objective C file to detect the window's
resolution scale on Apple platforms.
It is not a C++ file and is not part of this course!
*/
#import "AppKit/NSWindow.h"
#include "Scaling.hpp"

namespace pacman {

double scaling_factor_for_window(sf::WindowHandle handle) {
    return [ reinterpret_cast<id>(handle) backingScaleFactor];
}

}