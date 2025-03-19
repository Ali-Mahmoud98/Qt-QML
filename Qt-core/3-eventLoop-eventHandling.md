# Qt Core - Event Loop & Event Handling in Qt

### **1. Event Loop**
The **event loop** is the core mechanism that keeps a Qt application running and responsive. It continuously checks for and dispatches events (e.g., user input, timers, network activity) to their respective handlers.

#### **Key Components:**
- **QApplication (GUI) or QCoreApplication (non-GUI):**  
  These classes manage the event loop. `QApplication` is used for GUI applications, while `QCoreApplication` is for console/backend apps.
- **`app.exec()`:**  
  Starts the event loop. The application remains in this loop until `quit()` is called or the main window is closed.

**Example Code:**
```cpp
int main(int argc, char* argv[]) {
    QApplication app(argc, argv); // Initializes GUI context
    // Create widgets or objects here
    return app.exec(); // Enters the event loop
}
```
- The loop processes events sequentially (e.g., mouse clicks, paint requests) and ensures the UI remains responsive.

---

### **2. Events vs. Signals**

#### **a. Events**
- **Low-level occurrences** (e.g., mouse press, keyboard input, window resize).
- Handled by overriding `event(QEvent*)` or specific handlers like `keyPressEvent()`.

**Example: Overriding `event()`**
```cpp
bool MyWidget::event(QEvent* e) {
    if (e->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(e);
        // Handle key press (e.g., log the key)
        return true; // Event handled
    }
    return QWidget::event(e); // Pass unhandled events to the parent
}
```

#### **b. Signals**
- **High-level notifications** triggered by events (e.g., `clicked()` for a button).
- Use the **signals and slots** mechanism for communication between objects.

**Example: Connecting a Signal to a Slot**
```cpp
QPushButton* button = new QPushButton("Click me");
connect(button, &QPushButton::clicked, []() {
    qDebug() << "Button clicked!";
});
```
- Signals decouple event handling logic: a button’s low-level mouse event triggers the high-level `clicked()` signal.

---

### **3. Custom Events**
Used for application-specific communication, especially across threads or to decouple components.

#### **Steps to Create Custom Events:**
1. **Subclass `QEvent`:**  
   Define a custom event type.
2. **Post/Send the Event:**  
   Use `QCoreApplication::postEvent()` (asynchronous) or `sendEvent()` (synchronous).

**Example: Custom Event Class**
```cpp
class CustomEvent : public QEvent {
public:
    static const QEvent::Type TYPE = static_cast<QEvent::Type>(1000);
    CustomEvent() : QEvent(TYPE) {}
};
```

**Posting the Event:**
```cpp
// Post to an object (e.g., a widget)
QCoreApplication::postEvent(receiver, new CustomEvent());
```

**Handling the Event:**
```cpp
bool ReceiverClass::event(QEvent* e) {
    if (e->type() == CustomEvent::TYPE) {
        // Handle custom event
        return true;
    }
    return QWidget::event(e);
}
```

---

### **Key Differences: Events vs. Signals**

| **Feature**         | **Events**                          | **Signals**                          |
|----------------------|-------------------------------------|---------------------------------------|
| **Level**            | Low-level (system or OS-generated)  | High-level (logical actions)          |
| **Handling**         | Override `event()` or handlers      | Connect to slots                      |
| **Use Case**         | Raw input, window system events     | UI interactions (e.g., button clicks) |
| **Thread Safety**    | Safe with `postEvent()`             | Auto-threaded via queued connections  |
| **Performance**      | Faster (direct handling)            | Slightly slower (meta-object system)  |

---

### **When to Use Each:**
- **Events:**  
  - Raw input handling (e.g., custom keyboard shortcuts).  
  - Intercepting low-level system events (e.g., window focus changes).  
  - Cross-thread communication with `postEvent()`.
- **Signals:**  
  - UI interactions (e.g., button clicks, slider moves).  
  - Decoupled communication between components.  
  - Simplifying code with the signals/slots syntax.

---

### **Best Practices:**
1. **Avoid Blocking the Event Loop:**  
   Long-running tasks freeze the UI. Use worker threads or `QTimer` for background work.
2. **Prefer Signals for UI Logic:**  
   They simplify code and reduce boilerplate compared to low-level event handling.
3. **Use Custom Events for Cross-Thread Communication:**  
   Safer than direct method calls between threads.

