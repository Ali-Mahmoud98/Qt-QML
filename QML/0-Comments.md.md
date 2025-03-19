# QML Comments
### QML Comments Basics
Comments are notes for developers that the QML engine ignores. They help explain your code.

**Two types:**
1. **Single-line comments**  
   Start with `//`  
   ```qml
   // This text is ignored by QML
   Rectangle {
       width: 100  // This comment is after code
   }
   ```

2. **Multi-line comments**  
   Wrap with `/* */`  
   ```qml
   /* This is a
      longer comment */
   Text {
       /* You can comment out
          multiple properties */
       // text: "Temporary disabled"
   }
   ```

---

### Where to Use Comments
1. **Explain complex code**  
   ```qml
   // Rotate image every 2 seconds
   RotationAnimation {
       duration: 2000
       loops: Animation.Infinite
   }
   ```

2. **Temporarily disable code**  
   ```qml
   Button {
       // onClicked: doSomething() // Disabled for testing
   }
   ```

3. **Document component purpose**  
   ```qml
   /* Custom slider control
      - Handles touch input
      - Works with values 0-100 */
   Slider { ... }
   ```

---

### Key Rules
1. Works anywhere in QML files
2. **Cannot nest multi-line comments**  
   `/* /* inner */ outer */` → Error
3. Use freely in both QML and JavaScript sections

---

### Example in Context
```qml
// Main application window
Window {
    /* Window size configuration
       Default: 800x600 */
    width: 800
    height: 600  // Can adjust these later

    /*
    Title customization:
    - qsTr() enables translations
    - Visible in window title bar
    */
    title: qsTr("My Awesome App")
}
```

Comments make your QML code easier to understand and maintain! 😊