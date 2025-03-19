# Qt Core - Performance & Best Practices

### 1. **Implicit Sharing (Copy-on-Write)**
**What it is:**  
Qt's smart memory management technique where multiple objects share the same data until one needs to modify it.

**How it works:**
```cpp
QString a = "Hello";  // Allocates memory
QString b = a;        // Shares the same data (no copy)
b[0] = 'J';           // Now makes a copy (copy-on-write)
// a remains "Hello", b becomes "Jello"
```

**Why it matters:**
- Reduces memory usage
- Avoids unnecessary deep copies
- Makes passing objects by value efficient

**Best Practices:**
- Don't worry about passing Qt types by value
- Use `const` references for read-only access:
  ```cpp
  void printData(const QString& str);  // Better than QString
  ```

---

### 2. **Avoid Blocking the Event Loop**
**The Problem:**  
Qt's main thread handles GUI updates and event processing. Blocking it makes your UI freeze.

**Bad Example:**
```cpp
void MainWindow::onClick()
{
    // This will freeze the UI for 5 seconds
    QThread::sleep(5);
}
```

**Solution:** Use worker threads  
**Qt6 Options:**
- `QThread` (traditional)
- `QtConcurrent::run()` (simplest)
- `QRunnable` (for thread pools)

**Good Example using QtConcurrent:**
```cpp
void MainWindow::onClick()
{
    QtConcurrent::run([=]() {
        // Heavy computation here (runs in separate thread)
        QThread::sleep(5);
        
        // Update UI safely
        QMetaObject::invokeMethod(this, [=]() {
            ui->resultLabel->setText("Done!");
        });
    });
}
```

**Key Rules:**
- Never modify GUI elements directly from worker threads
- Use signals/slots or `QMetaObject::invokeMethod` for UI updates
- Consider `QFutureWatcher` for monitoring async tasks

---

### 3. **Memory Management**
**Qt's Parent-Child System:**
```cpp
QObject* parent = new QObject;
QObject* child = new QObject(parent);  // Auto-deleted with parent

// Delete parent → automatically deletes all children
delete parent;
```

**Best Practices:**
- Set parents for QObject-derived classes
- Use smart pointers when parent-child isn't sufficient:
  ```cpp
  std::unique_ptr<QWidget> widget = std::make_unique<QWidget>();
  ```
- Watch for circular references (parent ↔ child)
- For non-QObject types, use standard C++ memory management

---

### 4. **Qt vs STL Containers**
**Why prefer Qt containers:**
- Implicit sharing (STL containers always copy)
- Better integration with Qt APIs
- Additional convenience methods

**Example of Conversion Cost:**
```cpp
// Conversion between containers creates copies
QVector<int> qtVec = ...;
std::vector<int> stlVec = qtVec.toStdVector();  // Deep copy
```

**When to mix them:**
- When using STL algorithms:
  ```cpp
  QList<QString> names = ...;
  std::sort(names.begin(), names.end());
  ```
- When interacting with non-Qt libraries

**Best Practices:**
- Stick to Qt containers (`QList`, `QVector`, `QMap`) for Qt-heavy code
- Use STL containers only for:
  - Performance-critical sections
  - Third-party library integration
  - Existing codebases using STL

---

### Performance Checklist
1. **For heavy operations:**  
   Always use worker threads (`QtConcurrent`/`QThread`)

2. **For data passing:**  
   Use `const &` for read-only access to Qt types

3. **For memory:**  
   Leverage parent-child relationships first

4. **For containers:**  
   Prefer Qt containers unless you need specific STL features

---

### Common Mistakes to Avoid
1. **UI thread blocking:**
   ```cpp
   // WRONG: Runs in main thread
   void processData() { /* heavy work */ }
   
   // RIGHT: Use QtConcurrent::run(processData)
   ```

2. **Unnecessary conversions:**
   ```cpp
   // BAD: Creates temporary copy
   std::string s = qString.toStdString();
   
   // BETTER: Work with QString directly
   ```

3. **Memory leaks:**
   ```cpp
   // BAD: No parent set, might leak
   auto* obj = new QObject;
   
   // GOOD: Auto-deletes with parent
   auto* obj = new QObject(parent);
   ```
