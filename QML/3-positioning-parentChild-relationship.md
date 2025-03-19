# **x, y, z**, and **parent-child relationships** in QML (Qt Quick)

---

### 1. **Parent-Child Relationship**
#### What It Means:
- QML items are organized in a **hierarchy** where a parent "owns" its children.
- **Key Implications**:
  - **Positioning**: Child coordinates (`x`, `y`) are relative to the parent’s top-left corner.
  - **Memory**: Destroying a parent automatically deletes its children.
  - **Transformations**: Parent’s rotations/scales affect children.

#### Example:
```qml
Item { // Parent
    x: 50
    y: 50

    Rectangle { // Child
        x: 20 // Positioned 20px right of parent's left edge
        y: 30 // Positioned 30px below parent's top edge
        width: 100; height: 100; color: "red"
    }
}
```
The red rectangle’s **global position** is `(50+20, 50+30) = (70, 80)`.

---

### 2. **`x` and `y` Properties**
#### Purpose:
- Position an item **relative to its parent**.
- `x`: Horizontal offset from parent’s left edge.
- `y`: Vertical offset from parent’s top edge.

#### Example:
```qml
Rectangle { // Parent (blue)
    width: 200; height: 200; color: "blue"

    Rectangle { // Child (red)
        x: 50; y: 50
        width: 100; height: 100; color: "red"
    }
}
```
The red rectangle appears **inside the blue parent**, offset by `(50, 50)`.

---

### 3. **`z` Property**
#### Purpose:
- Controls **stacking order** of sibling items (items with the same parent).
- Higher `z` values appear **on top**.
- Default `z = 0`.

#### Example:
```qml
Rectangle { // Parent
    Rectangle { // Child 1 (red, z=1)
        width: 100; height: 100; color: "red"
        z: 1
    }

    Rectangle { // Child 2 (green, z=0)
        x: 50; y: 50
        width: 100; height: 100; color: "green"
    }
}
```
The red rectangle overlaps the green one because `z: 1 > z: 0`.

---

### 4. **Key Rules**
| Concept               | Behavior                                                                 |
|-----------------------|--------------------------------------------------------------------------|
| **Parent Coordinates** | Children inherit the parent’s coordinate system.                        |
| **Global Position**    | `mapToItem(null, x, y)` converts to global screen coordinates.          |
| **z-Order**            | Only affects siblings; parents’ `z` values don’t override children’s.   |
| **Visibility**         | If a parent is hidden (`visible: false`), all children are hidden too.  |

---

### 5. **Common Scenarios**
#### Scenario 1: Overlapping Items
```qml
Rectangle { color: "red"; width: 100; height: 100 }
Rectangle { color: "green"; x: 50; y: 50; width: 100; height: 100 }
```
Without `z`, the **last item** defined is drawn on top. Use `z` to override.

#### Scenario 2: Nested Parents
```qml
Item { // Root parent
    Item { // Parent A
        x: 50
        Rectangle { // Child of A
            x: 20 // Global x = 50 (A) + 20 = 70
        }
    }

    Item { // Parent B
        x: 100
        Rectangle { // Child of B
            x: 30 // Global x = 100 (B) + 30 = 130
        }
    }
}
```

---

### 6. **When to Use `z`**
- Bring an item to the front on click:
  ```qml
  Rectangle {
      TapHandler {
          onTapped: parent.z += 1 // Increase z to bring forward
      }
  }
  ```
- Layer UI elements (e.g., popups over content).

---

### 7. **Memory Management**
- Deleting a parent automatically deletes its children:
  ```qml
  Item {
      id: parentItem
      // ...
  }

  // Later:
  parentItem.destroy() // Children are deleted too
  ```

---

### Summary Table
| Property/Concept | Behavior                                                                 |
|------------------|--------------------------------------------------------------------------|
| **Parent**       | Defines coordinate system and ownership for children.                   |
| **`x`/`y`**      | Position relative to parent’s top-left corner.                          |
| **`z`**          | Controls stacking order of siblings (higher = front).                   |
| **Visibility**   | Children inherit parent’s visibility.                                   |
