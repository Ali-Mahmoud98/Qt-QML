# Qt Core - Containers & Smart Pointers

[EXAMPLE 2](./example2/)

#### **1. Qt Containers**
Qt provides its own set of containers optimized for performance, memory usage, and integration with Qt's ecosystem. While STL containers are generic, Qt containers are tailored for Qt types and use cases.

---

##### **Key Qt Containers**
- **`QList` / `QVector`** (historically distinct, unified in Qt 6):
  - **`QList`** (pre-Qt 6): Uses a hybrid array-of-pointers for large/non-movable types, optimizing insertions and removals. Best for polymorphic types or frequent mid-list modifications.
  - **`QVector`** (pre-Qt 6): Contiguous memory layout like `std::vector`, ideal for indexed access and iteration.
  - **Qt 6+**: `QList` replaces `QVector` with contiguous storage, optimized for small types (e.g., `int`, `QString`).

- **`QMap`**:
  - A sorted associative container (red-black tree) with **O(log n)** lookups. Similar to `std::map`.
  - Use for ordered key-value pairs where keys are sortable (e.g., integers, strings).

- **`QHash`**:
  - Hash-table-based unordered container with **average O(1)** lookups. Analogous to `std::unordered_map`.
  - Faster than `QMap` for large datasets but lacks ordering.

- **`QSet`**:
  - Unordered collection of unique values, implemented as a hash table. Similar to `std::unordered_set`.

---

##### **Why Qt Containers Over STL?**
- **Implicit Sharing (Copy-on-Write)**:
  - Memory-efficient when passing containers by value. Copies share data until modified.
- **Optimized for Qt Types**:
  - Better performance with `QString`, `QVariant`, or other Qt classes.
- **Qt API Integration**:
  - Many Qt functions return or expect Qt containers (e.g., `QWidget::children()` returns `QObjectList`).
- **Portability**:
  - Consistent behavior across platforms/compilers, avoiding STL implementation quirks.

---

##### **`QString` vs. `std::string`**
- **`QString`**:
  - Stores Unicode text (UTF-16), supporting internationalization.
  - Rich API for text manipulation (e.g., `split()`, `trimmed()`, `arg()` for formatting).
  - Seamless integration with Qt APIs (e.g., GUI labels, file I/O).
- **`std::string`**:
  - Byte string without guaranteed encoding. Use only for ASCII or binary data.

---

#### **2. Qt Smart Pointers**
Qt provides smart pointers tailored for its object model, particularly for `QObject` hierarchies.

---

##### **Key Qt Smart Pointers**
- **`QSharedPointer`**:
  - Reference-counted shared ownership (like `std::shared_ptr`).
  - Custom deleters supported (e.g., `QSharedPointer<QFile>::create("file.txt")`).
  - Use for shared ownership of heap-allocated objects.

- **`QWeakPointer`**:
  - Non-owning pointer to break reference cycles (like `std::weak_ptr`).
  - Safely check validity via `toStrongRef()` or `lock()`.

- **`QScopedPointer`**:
  - Sole ownership with scope-bound lifetime (like `std::unique_ptr`).
  - Non-copyable; deletes object when it goes out of scope.

---

##### **Why Qt Smart Pointers Over STL for Qt Objects?**
- **Parent-Child Hierarchy Compatibility**:
  - Qt objects (`QObject` subclasses) often use parent-child relationships. Mixing `std::shared_ptr` with manual parent-child ownership can cause double deletions.
  - Example: A `QWidget` parent automatically deletes its children. Using `QSharedPointer` for a child widget without a parent is safe, but combining it with a parent could lead to conflicts.
- **Qt-Specific Features**:
  - `QSharedPointer` works with `QObject`-derived types, respecting Qt’s memory model.
  - Better integration with Qt’s signal/slot system (e.g., queued signals with smart pointers).
- **DLL Boundary Safety**:
  - Ensures consistent allocator/deallocator use across Qt libraries.

---

##### **Guidelines**
1. **For non-QObject types**: Use STL smart pointers if not using Qt features.
2. **For `QObject` hierarchies**:
   - Prefer `QSharedPointer` for shared ownership (no parent).
   - Use raw pointers with parent-child relationships for automatic management.
   - Avoid mixing parent-child and smart pointers for the same object.
3. **Short-lived, scoped objects**: Use `QScopedPointer` for clear ownership.

---

#### **Example: Qt vs. STL**
```cpp
// Qt Containers
QList<QString> names = {"Alice", "Bob"};
QHash<QString, int> phonebook = {{"Alice", 123}, {"Bob", 456}};

// STL Containers
std::vector<std::string> stdNames = {"Charlie"};
std::unordered_map<std::string, int> stdPhonebook = {{"Charlie", 789}};

// Qt Smart Pointer (QObject-derived)
QSharedPointer<QWidget> widget = QSharedPointer<QWidget>::create();
widget->setWindowTitle("Hello Qt");

// STL Smart Pointer (non-Qt type)
auto file = std::make_shared<std::ofstream>("data.txt");
```

---

#### **Summary**
- **Qt Containers**: Optimized for Qt types, implicit sharing, and Qt APIs.
- **`QString`**: Essential for Unicode and Qt integration.
- **Qt Smart Pointers**: Safer for `QObject` hierarchies, avoiding conflicts with parent-child ownership.
