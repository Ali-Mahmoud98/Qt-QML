# Root Object and IDs
---
### 1. **Root Object**
#### What is it?
- Every QML file has **exactly one root object**.
- It’s the "parent" of all other elements in the file.
- Defined by the **first/top-level component** in the file.

#### Key Rules:
- Only **one root object** per QML file.
- Acts as the entry point for the QML engine.
- Typically a container like `Window`, `Item`, or `Rectangle`.

#### Example:
```qml
// Root object: Window
Window {
    // Child objects
    Text { text: "Hello" }
    Button { /* ... */ }
}
```

---

### 2. **ID**
#### What is it?
- A **unique identifier** for a QML object.
- Lets you reference objects from other parts of the code.

#### Key Rules:
- Must be **unique** within the same QML file.
- Declared with `id: your_id_name`.
- IDs are **case-sensitive** (`myId` ≠ `myID`).

#### Example:
```qml
Window {
    id: rootWindow // ID for the root object

    Text {
        id: titleText // ID for this Text element
        text: "Hello World"
    }

    Button {
        onClicked: {
            titleText.text = "Clicked!" // Access via ID
        }
    }
}
```

---

### Key Differences
| **Root Object**                | **ID**                          |
|---------------------------------|---------------------------------|
| Always exists (one per file)    | Optional identifier             |
| Defines the file structure      | Used to reference objects       |
| No need to declare an `id`      | Must explicitly declare `id:`   |

---

### Common Use Cases
#### Root Object:
- Set up the main component (e.g., `Window`, `Item`).
- Define default properties like size/position.

#### ID:
- Modify properties of another object:
  ```qml
  Button {
      onClicked: someOtherObject.color = "red"
  }
  ```
- Call functions between components:
  ```qml
  Button {
      onClicked: myAnimation.start()
  }
  ```

---

### Important Notes
- **Root object can have an ID**, but it’s optional.
- If you don’t give the root an ID, you can still reference it using the QML file’s name (without `.qml`):
  ```qml
  // File: MyComponent.qml
  Item { /* ... */ }

  // In another file:
  MyComponent { // Refers to the root object
      // ...
  }
  ```

---

### Example: Full Usage
```qml
// Root object (Window)
Window {
    id: mainWindow
    width: 400

    // Child Rectangle with ID
    Rectangle {
        id: coloredBox
        color: "blue"
    }

    // Button to modify the Rectangle
    Button {
        text: "Change Color"
        onClicked: coloredBox.color = "green" // Use ID
    }
}
```
