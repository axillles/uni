# Midpoint Clipping and Rasterization Algorithms Visualization

This project implements a midpoint clipping algorithm for line segments within a defined clipping window and visualizes the results using Matplotlib. Additionally, it demonstrates rasterization algorithms using Pygame for lines and circles, including DDA, Bresenham, and incremental algorithms.

## Features
- **Midpoint Clipping Algorithm**: Iteratively clips line segments to fit within a given rectangular window.
- **Rasterization Algorithms**:
  - **DDA (Digital Differential Analyzer)**: Renders lines using incremental steps.
  - **Bresenham Line Algorithm**: Efficiently rasterizes lines using integer arithmetic.
  - **Bresenham Circle Algorithm**: Rasterizes circles using symmetry.
  - **Incremental Algorithm**: Renders lines using slope-based calculations.
- **Visualization**:
  - Matplotlib for clipping window and segments.
  - Pygame for rasterization visualization of lines and circles.
- **Input File Support**: Reads line segments and clipping window data from a text file.

---

## File Structure
- `main.py`: Contains the implementation of the midpoint clipping algorithm and visualization.
- `rasterization.py`: Demonstrates the rasterization algorithms using Pygame.
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

### Midpoint Clipping Visualization
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

### Rasterization Visualization
1. **Run the Script**
   ```bash
   python rasterization.py
   ```

2. **View Results**
   - The Pygame window will display:
     - Axes for reference.
     - Lines and circles drawn using different rasterization algorithms.
     - Execution times for each algorithm displayed on the screen.

---

## Functions

### Midpoint Clipping (Matplotlib)

#### 1. `read_data(file_path)`
Reads line segment and clipping window data from a file.

- **Input**: File path
- **Output**: List of line segments and the clipping window

#### 2. `midpoint_clip(segment, window)`
Clips a line segment to fit within the specified clipping window using the midpoint algorithm.

- **Input**: Line segment and clipping window
- **Output**: Visible parts of the clipped segment

#### 3. `visualize_with_labels(segments, clipping_window, midpoint_segments, convex_segments)`
Visualizes the original and clipped line segments with the clipping window.

- **Input**: Original segments, clipping window, and clipped segments

#### 4. `main(file_path)`
Orchestrates the reading, clipping, and visualization of the data.

- **Input**: Path to the input file

### Rasterization (Pygame)

#### 1. `draw_axes()`
Draws coordinate axes with labeled grid lines.

#### 2. `dda_algorithm(x0, y0, x1, y1, color)`
Renders a line using the DDA algorithm.

#### 3. `bresenham_line(x0, y0, x1, y1, color)`
Renders a line using the Bresenham line algorithm.

#### 4. `bresenham_circle(x0, y0, radius, color)`
Renders a circle using the Bresenham circle algorithm.

#### 5. `incremental_algorithm(x0, y0, x1, y1, color)`
Renders a line using the incremental slope-based algorithm.

---

## Requirements
- Python 3.8+
- Matplotlib
- Pygame

### Install Dependencies
```bash
pip install matplotlib pygame
```

---

## Notes
- The midpoint clipping algorithm limits iterations to 100 to prevent infinite loops.
- Rasterization execution times are displayed directly in the Pygame window for performance comparison.

---

## License
This project is licensed under the MIT License.

