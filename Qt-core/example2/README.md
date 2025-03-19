# `explicit` Keyword

The keyword **explicit** in the constructor declaration:

```cpp
explicit MyContainer(QObject *parent = nullptr);
```

ensures that this constructor cannot be used for implicit type conversions. This means that objects of the `MyContainer` class can only be created when you explicitly call the constructor, preventing accidental or unintended conversions from a `QObject*` (or any other convertible type) into a `MyContainer` object. This design choice is particularly useful for avoiding subtle bugs where the compiler might otherwise convert types implicitly, leading to ambiguous or unintended behavior in your code.

For more details on the explicit keyword and its usage in C++, you can refer to the [cppreference documentation on explicit](https://en.cppreference.com/w/cpp/language/explicit) and a detailed discussion on [StackOverflow about explicit constructors](https://stackoverflow.com/questions/1888047/when-to-use-explicit-in-c).

## EXAMPLES:

The **explicit** keyword in C++ is used to mark constructors (or conversion operators) to prevent the compiler from using them for implicit conversions. This means that if you have a constructor that can be called with a single argument, marking it as explicit ensures that the compiler won't automatically convert that argument into an object of your class, avoiding potential ambiguity or unexpected behavior.

### **Example Without `explicit`**

Consider the following class without the `explicit` keyword:

```cpp
#include <iostream>

class MyNumber {
public:
    // Constructor without explicit
    MyNumber(int value) : m_value(value) {}

    int value() const { return m_value; }
private:
    int m_value;
};

void printNumber(MyNumber num) {
    std::cout << "Number: " << num.value() << std::endl;
}

int main() {
    MyNumber a(42);       // Direct initialization is fine.
    MyNumber b = 42;      // Implicit conversion from int to MyNumber allowed.
    
    printNumber(10);      // Implicit conversion: 10 is automatically converted to MyNumber.
    
    return 0;
}
```

In this case, the integer `42` is automatically converted into a `MyNumber` object when used in an assignment or as a function argument. While convenient, this implicit conversion can lead to bugs if the conversion is not intended.

### **Example With `explicit`**

Now, let’s modify the class by adding the `explicit` keyword to the constructor:

```cpp
#include <iostream>

class MyNumber {
public:
    // Explicit constructor prevents implicit conversion.
    explicit MyNumber(int value) : m_value(value) {}

    int value() const { return m_value; }
private:
    int m_value;
};

void printNumber(MyNumber num) {
    std::cout << "Number: " << num.value() << std::endl;
}

int main() {
    MyNumber a(42);       // Direct initialization is still allowed.
    // MyNumber b = 42;   // Error: implicit conversion from int to MyNumber is not allowed.

    // printNumber(10);   // Error: implicit conversion from int to MyNumber is not allowed.
    printNumber(MyNumber(10)); // Correct: explicit conversion.

    return 0;
}
```

In this version, the constructor is marked as **explicit**, so the following implicit conversions are now disallowed:
- `MyNumber b = 42;` causes a compilation error.
- `printNumber(10);` causes a compilation error.

You must explicitly convert an `int` to a `MyNumber` object, as shown in the call `printNumber(MyNumber(10));`. This requirement helps ensure that conversions are intentional and clear in your code.

For a more in-depth discussion and additional examples on the usage of the `explicit` keyword, you can refer to the [cppreference documentation on explicit](https://en.cppreference.com/w/cpp/language/explicit) and check out this detailed explanation on [StackOverflow](https://stackoverflow.com/questions/1888047/when-to-use-explicit-in-c).
