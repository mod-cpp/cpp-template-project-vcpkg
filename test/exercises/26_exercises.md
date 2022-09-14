[< Back](README.md)

# 26. Tools

* [Exercise 260](#exercise-260)
* [Exercise 261](#exercise-261)
* [Exercise 262](#exercise-262)

## Exercise 260

### UndefinedBehaviorSanitizer (UBSan)

Experiment on [Compiler Explorer][2].

```cpp
int div(int a, int b) {
    return a / b;
}

int main () {
    int a = 42;
    int b = 0;
    return div(a, b);
}
```

## Exercise 261

### AddressSanitizer (ASan)

Experiment on [Compiler Explorer][3].

```cpp
#include <array>

int main() {
    std::array v{1, 2, 3};
    return v[4];
}
```

## Exercise 262

### MemorySanitizer (MSan)

Experiment on [Compiler Explorer][4].

```cpp
int main() {
   int a;
   return a;
}
```

[1]: 26_exercises.cpp
[2]: https://godbolt.org/z/nT54sj4hj
[3]: https://godbolt.org/z/84Kr7Gcbz
[4]: https://godbolt.org/z/n5zWWM3aa
