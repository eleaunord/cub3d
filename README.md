# 🕹️  42-cub3D – Our First RayCaster

*The project was developed collaboratively by Ruddy Russelin (rrisseli) and Éléonore Roty (eleroty).*

## 📌 Project Overview

**cub3D** is a raycasting-based 3D renderer inspired by *Wolfenstein 3D*. The goal is to simulate a first-person perspective in a 2D maze using math, vectors, and digital graphics via MiniLibX. This project combines low-level C programming with fundamental graphics and math concepts.

> The project requires parsing a `.cub` map file, handling player movement, rendering walls with textures, and implementing keyboard controls.

---

## 🧠 What we Learned

### Raycasting Fundamentals

Raycasting is a technique to simulate 3D by sending out rays for every vertical line of the screen. For each ray:

* Cast it from the player's position.
* Check where it hits a wall on the 2D map.
* Use the **distance to the wall** to determine the height of the vertical line to draw.

> "The closer the wall, the taller it appears."

---

## Technical Concepts

### Digital Differential Analyzer (DDA)

Used to detect **where a ray hits a wall**. It loops until a ray intersects a wall by checking grid-by-grid positions.

### 2D Calculations and Vectors

* The **direction vector** defines where the player is looking.
* The **camera plane** is perpendicular to the direction vector.
* The direction of a ray is computed as:

  ```
  rayDir = dir + plane * cameraX
  ```

> For example, the third red ray below moves toward 1/3 of the screen width:

![image](https://github.com/user-attachments/assets/52f8eb49-c171-4320-abf6-7dbf83123af6)

---

### Field of View (FOV)

* FOV is the angle between the leftmost and rightmost ray.
* It is determined by the **length of the direction vector and camera plane**.

| Ratio                     | FOV Outcome           |
| ------------------------- | --------------------- |
| dir = plane               | 90°                   |
| dir >> plane              | narrow view           |
| dir << plane (plane long) | wide view, zoomed out |

---

### Rotation in 2D

To rotate the view when pressing left/right, we rotate the direction and camera plane vectors using the standard **2D rotation matrix**:

```
[ cos(a) -sin(a) ]
[ sin(a)  cos(a) ]
```

> This ensures the entire perspective view rotates consistently.

---

## Mandatory Features

According to the project spec:

* Parsing `.cub` map files (textures, colors, and layout).
* Raycasting rendering with wall height scaling.
* Basic controls:

  * W, A, S, D for movement
  * Left/Right arrow keys for rotating view
  * ESC key or red cross to exit
* Wall textures based on orientation (N, S, E, W).
* Settable floor and ceiling colors.

---

## Map Example

```
111111
100101
101001
1100N1
111111
```

* `1`: wall
* `0`: empty space
* `N`, `S`, `E`, `W`: player spawn + orientation

---

## 📚 What This Project Taught Us

* Deep understanding of **2D vectors**, **trigonometry**, and **coordinate systems**.
* How to use **math** and **logic** to simulate a 3D environment in a 2D grid.
* Handling **keyboard events**, **image rendering**, and **file parsing** in C.
* Importance of **clean structure** and **modular code** when managing a complex system.

---

## Final Thoughts

cub3D is a brilliant way to combine math, programming, and creativity. It gave me:

* Confidence in working with low-level graphics.
* Experience with structuring a real-time rendering engine.
* A great appreciation for how old-school 3D engines worked.
