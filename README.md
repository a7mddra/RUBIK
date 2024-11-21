## Project Overview
This project is a Rubik's Cube solver that:
1. **Detects cube colors using OpenCV** through a live camera feed.
2. **Displays a 2D representation** of the cube after color detection.
3. **Solves the cube** using the Kociemba algorithm, showing step-by-step instructions for solving.
4. **Handles hardware movements** using C for efficient execution of the cube's rotations.

---

## How to Run
1. **Ensure dependencies are installed**:
   - Python libraries: OpenCV, Numpy, and Kociemba.
   - Camera setup: For `DroidCam` users, ensure it's configured and accessible.

2. **Run the main script**:
   ```bash
   python main.py
   ```

3. **Camera feed operations**:
   - Use the live feed to capture the cube faces in the specified order:
     1. **Front**
     2. **Right**
     3. **Back**
     4. **Left**
     5. **Up**
     6. **Down**
   - Capture faces by pressing:
     - `r` to save the current face.
     - `g` to step back and recapture the previous face.

4. **Handle color misdetections**:
   - If the detected colors seem incorrect, adjust the RGB ranges in `color_picker.py`.

5. **View the 2D representation**:
   - After all faces are captured, a 2D representation of the cube will be displayed.

6. **Solve the cube**:
   - Press `r` to view the next move based on the Kociemba algorithm's solution.
   - The solution follows standard cube notation (e.g., `F`, `F'`, `F2`, etc.).

---

## Cube Face Capture Order
Follow this order when capturing the cube's faces on the camera:

```plaintext
            37 38 39
            40 41 42
            43 44 45
 28 29 30   1  2  3  10 11 12  19 20 21
 31 32 33   4  5  6  13 14 15  22 23 24
 34 35 36   7  8  9  16 17 18  25 26 27
            46 47 48
            49 50 51
            52 53 54
```

Face representation:
```plaintext
   U
L  F  R  B
   D
```

---

## Notes
1. **Color detection calibration**:
   - Use `color_picker.py` to fine-tune RGB ranges for accurate detection.

2. **Solution notation**:
   - The solution steps are based on the **Kociemba algorithm**. Example moves:
     - `F`  : Rotate the front face clockwise.
     - `F'` : Rotate the front face counterclockwise.
     - `F2` : Rotate the front face twice.
     - Similar for `L`, `R`, `U`, `D`, and `B`.

---

## Contribution
Feel free to contribute by:
- Improving color detection algorithms.
- Optimizing cube movement handling in the C module.
- Enhancing the UI/UX for the 2D representation and camera feed. 
