# Midpoint Clipping Visualization

This project implements a midpoint clipping algorithm for line segments within a defined clipping window and visualizes the results using Matplotlib.

## Features
- **Midpoint Clipping Algorithm**: Iteratively clips line segments to fit within a given rectangular window.
- **Visualization**: Uses Matplotlib to display original and clipped line segments, along with the clipping window.
- **Input File Support**: Reads line segments and clipping window data from a text file.

---

## File Structure
- `main.py`: Contains the implementation of the midpoint clipping algorithm and visualization.
- `input.txt`: Sample input file containing line segments and clipping window data.

---

## Input File Format
The input file should follow the format below:

```
N  # Number of line segments
x1 y1 x2 y2  # Coordinates of the first segment
x3 y3 x4 y4  # Coordinates of the second segment
...
xmin ymin xmax ymax  # Clipping window boundaries
```

### Example
```
3
0 0 10 10
-5 5 15 5
5 -5 5 15
0 0 10 10
```
This specifies:
- 3 line segments:
  - (0, 0) to (10, 10)
  - (-5, 5) to (15, 5)
  - (5, -5) to (5, 15)
- Clipping window: (0, 0) to (10, 10)

---

## How to Run

1. **Prepare the Input File**
   - Create an input file (e.g., `input.txt`) with the format described above.

2. **Run the Script**
   ```bash
   python main.py
   ```

3. **View Results**
   - The visualization will display the following:
     - Original line segments (blue)
     - Clipped line segments using the midpoint clipping algorithm (green and orange)
     - The clipping window (red)

---

## Functions

### 1. `read_data(file_path)`
Reads line segment and clipping window data from a file.

- **Input**: File path
- **Output**: List of line segments and the clipping window

### 2. `midpoint_clip(segment, window)`
Clips a line segment to fit within the specified clipping window using the midpoint algorithm.

- **Input**: Line segment and clipping window
- **Output**: Visible parts of the clipped segment

### 3. `visualize_with_labels(segments, clipping_window, midpoint_segments, convex_segments)`
Visualizes the original and clipped line segments with the clipping window.

- **Input**: Original segments, clipping window, and clipped segments

### 4. `main(file_path)`
Orchestrates the reading, clipping, and visualization of the data.

- **Input**: Path to the input file

---

## Requirements
- Python 3.8+
- Matplotlib

### Install Dependencies
```bash
pip install matplotlib
```

---

## Notes
- The algorithm limits iterations to 100 to prevent infinite loops.
- Both midpoint and convex clipping results are visualized for comparison.

---

## License
This project is licensed under the MIT License.

