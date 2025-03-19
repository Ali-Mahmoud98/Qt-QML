# QML Basic Types
### 1. **`Item`**  
**Base Type**: All visual QML components inherit from `Item`  
**Purpose**: Non-visual container for grouping/organizing elements and handling basic properties  

#### Key Properties:
- **Geometry**:  
  ```qml
  width, height, x, y, z (stacking order)
  ```
- **Layout Control**:  
  ```qml
  anchors { ... }, transform: [Scale, Rotation, Translate]
  ```
- **Visibility**:  
  ```qml
  visible (true/false), opacity (0.0-1.0)
  ```

#### Common Use Cases:
- Grouping related components
- Creating custom components
- Layout organization (using anchors)
- Base for visual elements

#### Example:
```qml
Item {
    width: 300
    height: 200
    anchors.centerIn: parent
}
```

---

### 2. **`Rectangle`**  
**Inherits**: `Item`  
**Purpose**: Basic colored rectangle with optional borders/rounded corners  

#### Key Properties:
- **Visual**:  
  ```qml
  color: "red" | "#RRGGBB" | Qt.rgba()
  border { width: 2; color: "black" }
  radius: 10 // Rounded corners
  ```
- **Gradient**:  
  ```qml
  gradient: Gradient {
      GradientStop { position: 0.0; color: "white" }
      GradientStop { position: 1.0; color: "gray" }
  }
  ```

#### Common Use Cases:
- Buttons/backgrounds
- Visual separators
- Card-like UI elements

#### Example:
```qml
Rectangle {
    width: 100
    height: 50
    color: "blue"
    radius: 5
    border { width: 2; color: "navy" }
}
```

---

### 3. **`Image`**  
**Inherits**: `Item`  
**Purpose**: Display raster images (PNG, JPG, etc.)  

#### Key Properties:
- **Source**:  
  ```qml
  source: "image.png" // Local file
  source: "https://example.com/image.jpg" // Web URL
  ```
- **Scaling**:  
  ```qml
  fillMode: Image.PreserveAspectFit // Common modes:
  // Stretch (default), PreserveAspectCrop, Tile
  ```
- **Performance**:  
  ```qml
  asynchronous: true // For web images
  cache: false // Disable caching
  ```

#### Common Use Cases:
- Icons/avatars
- Background images
- Dynamic image loading

#### Example:
```qml
Image {
    source: "assets/logo.png"
    width: 200
    height: 200
    fillMode: Image.PreserveAspectFit
}
```

---

### 4. **`Text`**  
**Inherits**: `Item`  
**Purpose**: Display styled text content  

#### Key Properties:
- **Content**:  
  ```qml
  text: "Hello World"
  textFormat: Text.AutoText | Text.RichText | Text.StyledText
  ```
- **Styling**:  
  ```qml
  color: "green"
  font { 
      family: "Arial"
      pixelSize: 24
      bold: true
      italic: true 
  }
  ```
- **Layout**:  
  ```qml
  horizontalAlignment: Text.AlignHCenter
  verticalAlignment: Text.AlignVCenter
  elide: Text.ElideRight // For overflow text
  wrapMode: Text.WordWrap
  ```

#### Common Use Cases:
- Labels/headings
- Dynamic text displays
- Formatted text (using HTML tags)

#### Example:
```qml
Text {
    text: "<b>Important</b> Message"
    color: "#333"
    font.pixelSize: 16
    width: 200
    wrapMode: Text.Wrap
}
```

---

### 5. **`MouseArea`**  
**Inherits**: `Item`  
**Purpose**: Handle mouse/touch input  

#### Key Properties:
- **Interaction**:  
  ```qml
  enabled: true // Enable/disable interaction
  hoverEnabled: true // Track mouse hover
  acceptedButtons: Qt.LeftButton | Qt.RightButton
  ```
- **Signals**:  
  ```qml
  onClicked: { ... }
  onPressed: { ... }
  onReleased: { ... }
  onDoubleClicked: { ... }
  ```
- **Position**:  
  ```qml
  mouseX, mouseY // Current cursor position
  ```

#### Common Use Cases:
- Clickable buttons
- Drag-and-drop interactions
- Hover effects

#### Example:
```qml
Rectangle {
    width: 100
    height: 50
    color: mouseArea.containsMouse ? "darkred" : "red"
    
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: console.log("Clicked!")
    }
}
```

---

### Comparison Table
| Type        | Primary Purpose          | Key Features                          |
|-------------|--------------------------|---------------------------------------|
| `Item`      | Structural container     | Anchors, transformations, grouping   |
| `Rectangle` | Colored shapes           | Borders, gradients, rounded corners  |
| `Image`     | Visual content display   | Aspect control, web loading          |
| `Text`      | Typography               | Font styling, text wrapping          |
| `MouseArea` | User interaction         | Click/hover detection, position data |

---

### Combined Example (Real-World Usage):
```qml
Rectangle {
    width: 200
    height: 80
    color: "lightgray"
    radius: 8

    Text {
        text: "Click Me!"
        anchors.centerIn: parent
        font.pixelSize: 18
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("Button pressed")
            parent.color = "gray"
        }
    }
}
```

This creates a clickable button with hover feedback and visual styling. Each QML type plays a specific role in building interactive UI components.