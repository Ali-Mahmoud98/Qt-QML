# Qt - Core Modules & Key Concepts

These are foundational to understanding how Qt works under the hood and how to build efficient, cross-platform applications.

### Contents
#### [1. Qt Object Model](#1-qt-object-model)
#### [2. Containers & Smart Pointers](2-containers-smart-pointers)
#### [3. Event Loop & Event Handling](3-event-loop-event-handling)
#### [4. File I/O & Data Streams](4-file-io-data-streams)
#### [5. QtConcurrent](5-qtconcurrent)
#### [6. Thread Safety](6-thread-safety)

---

### **1. Qt Object Model**
The Qt Object Model extends standard C++ with features like **signals/slots**, **object ownership**, and **introspection** (runtime reflection). At its core is the `QObject` class.

#### **Key Components**:
1. **QObject**:
   - **Parent-Child Relationship**: 
     - When a `QObject` has a parent, its memory is automatically managed. Deleting the parent deletes all children recursively.
     ```cpp
     QObject* parent = new QObject();
     QObject* child = new QObject(parent); // Child is owned by parent
     delete parent; // Child is automatically deleted
     ```
   - **Signals & Slots**:
     - Mechanism for communication between objects (event-driven programming).
     - Declare signals in the `signals:` section and slots in `public slots:`.
     ```cpp
     class Sensor : public QObject {
         Q_OBJECT
     signals:
         void temperatureChanged(double newTemp);
     public slots:
         void logTemperature(double temp) { qDebug() << "Temp:" << temp; }
     };
     ```
     - Connect signals to slots using `QObject::connect`:
     ```cpp
     Sensor sensor;
     QObject::connect(&sensor, &Sensor::temperatureChanged, 
                      &logger, &Logger::logTemperature);
     ```

2. **Meta-Object System**:
   - **Enabled by the `Q_OBJECT` macro** and the **Meta-Object Compiler (moc)**.
   - Provides runtime type information (`RTTI`) and dynamic properties.
   - Example: Access class name dynamically:
     ```cpp
     QObject* obj = new Sensor();
     qDebug() << obj->metaObject()->className(); // Output: "Sensor"
     ```
    - Detailed explaination: https://doc.qt.io/qt-6/moc.html
    - You can read also: [moc-qobject.md](./moc-qobject.md)

---

### **2. Containers & Smart Pointers**
Qt provides its own optimized containers and memory management tools.

#### **a. Containers**:
- **Qt vs STL**: 
  - Qt containers (e.g., `QList`, `QMap`) are implicitly shared (copy-on-write) and integrate better with Qt APIs.
  - Example of `QList`:
    ```cpp
    QList<int> numbers = {1, 2, 3};
    numbers.append(4); // Efficient for Qt types
    ```
- **Key Containers**:
  - `QVector` (similar to `std::vector`).
  - `QMap` (ordered key-value pairs).
  - `QHash` (faster unordered key-value pairs).
  - `QString` (Unicode string handling).

#### **b. Smart Pointers**:
- **QSharedPointer**: Reference-counted shared ownership.
  ```cpp
  QSharedPointer<QObject> obj = QSharedPointer<QObject>(new QObject());
  ```
- **QScopedPointer**: RAII-style ownership (deleted when out of scope).
  ```cpp
  QScopedPointer<QFile> file(new QFile("data.txt"));
  ```
- **QObject Ownership**: Prefer `QObject` parent-child relationships over smart pointers for Qt objects.

---

### **3. Event Loop & Event Handling**
Qt applications are event-driven. The event loop processes events like user input, timers, or network activity.

#### **a. Event Loop**:
- Managed by `QCoreApplication` (non-GUI) or `QApplication` (GUI).
  ```cpp
  int main(int argc, char* argv[]) {
      QApplication app(argc, argv); // Starts the event loop
      // ... create widgets or objects ...
      return app.exec(); // Enters the event loop
  }
  ```

#### **b. Events vs Signals**:
- **Events**: Low-level (e.g., mouse press, key event). Handle by overriding `event(QEvent*)`:
  ```cpp
  bool MyWidget::event(QEvent* e) {
      if (e->type() == QEvent::KeyPress) {
          // Handle key press
          return true;
      }
      return QWidget::event(e);
  }
  ```
- **Signals**: High-level notifications (e.g., `clicked()` signal from a button).

#### **c. Custom Events**:
- Subclass `QEvent` and use `QCoreApplication::postEvent()`:
  ```cpp
  class CustomEvent : public QEvent {
  public:
      static const QEvent::Type TYPE = static_cast<QEvent::Type>(1000);
      CustomEvent() : QEvent(TYPE) {}
  };
  // Post the event to an object
  QCoreApplication::postEvent(receiver, new CustomEvent());
  ```

---

### **4. File I/O & Data Streams**
Qt provides platform-independent file handling and serialization.

#### **a. Reading/Writing Files**:
- **QFile**: Platform-agnostic file operations.
  ```cpp
  QFile file("data.txt");
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      QTextStream in(&file);
      QString line = in.readLine();
  }
  ```

#### **b. Data Serialization**:
- **QDataStream**: Serialize binary data (e.g., for network or files).
  ```cpp
  QFile file("data.bin");
  file.open(QIODevice::WriteOnly);
  QDataStream out(&file);
  out << 42 << "Hello Qt"; // Write integers and strings
  ```

---

### **5. Threading & Concurrency**
Qt simplifies multithreading while ensuring thread safety.

#### **a. QThread**:
- Subclass `QThread` and override `run()`:
  ```cpp
  class WorkerThread : public QThread {
      void run() override {
          // Long-running task here
      }
  };
  WorkerThread thread;
  thread.start(); // Starts a new thread
  ```

#### **b. QtConcurrent**:
- High-level API for parallel execution:
  ```cpp
  QFuture<void> future = QtConcurrent::run([](){
      // Code to run in a thread
  });
  ```

#### **c. Thread Safety**:
- Use `QMutex` or `QReadWriteLock` to protect shared data.
- Signals/slots across threads require `Qt::QueuedConnection`:
  ```cpp
  connect(worker, &Worker::resultReady, 
          guiThread, &GUI::updateUI, Qt::QueuedConnection);
  ```

---

### **Key Best Practices**:
1. **Parent-Child Hierarchy**: Use it to automate memory management.
2. **Avoid Blocking the Event Loop**: Offload heavy tasks to threads.
3. **Implicit Sharing**: Use Qt containers (e.g., `QImage`, `QString`) to minimize copying.
4. **Signals/Slots**: Prefer them over callbacks for decoupled communication.

---

### **Common Pitfalls**:
- Forgetting `Q_OBJECT` in classes using signals/slots.
- Accessing GUI elements from non-main threads.
- Using `new` without assigning a parent (risk of memory leaks).

---

### **Example: Signals/Slots Across Threads**
```cpp
// Worker in a thread
class Worker : public QObject {
    Q_OBJECT
public slots:
    void doWork() { 
        // Long task...
        emit resultReady(); 
    }
signals:
    void resultReady();
};

// Main thread setup
QThread workerThread;
Worker worker;
worker.moveToThread(&workerThread);
connect(&workerThread, &QThread::started, &worker, &Worker::doWork);
connect(&worker, &Worker::resultReady, [](){ qDebug() << "Done!"; });
workerThread.start();
```
