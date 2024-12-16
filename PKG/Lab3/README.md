# Image Processing App

This Python application provides a graphical interface for performing various image processing operations using OpenCV. Users can apply different transformations and visualizations to grayscale images, such as noise addition, blurring, contrast adjustment, thresholding, and more.

---

## Features

- **Graphical User Interface (GUI)**:
  - Easily select an image file for processing.
  - View multiple processed versions of the image in separate OpenCV windows.

- **Image Processing Operations**:
  - Add noise to the image.
  - Apply Gaussian blur for smoothing.
  - Generate low-contrast and high-contrast versions of the image.
  - Perform global thresholding using Otsu's and Triangle methods.
  - Apply adaptive mean and Gaussian thresholding.
  - Invert the image colors.

---

## How to Run

### Prerequisites
- Python 3.8+
- Required Python libraries:
  - `opencv-python`
  - `numpy`
  - `Pillow`

### Install Dependencies
```bash
pip install opencv-python numpy pillow
```

### Running the Application
1. Save the script to a file, e.g., `image_processing_app.py`.
2. Run the script:
   ```bash
   python image_processing_app.py
   ```
3. The application window will open, allowing you to select an image for processing.

---

## User Interface

- **Buttons**:
  - **Select Image**: Opens a file dialog to select an image file.
  - **Stop**: Closes all OpenCV windows displaying processed images.

- **Display Windows**:
  - Each processing operation generates a separate window with the result.

---

## Functions

### 1. `linear_contrast(image, alpha, beta)`
Adjusts the contrast of the image.
- **Input**: Image, scaling factor `alpha`, and brightness offset `beta`.
- **Output**: Image with adjusted contrast.

### 2. `apply_processing(image_path)`
Applies all processing operations to the selected image and displays the results.
- **Input**: Path to the image file.
- **Output**: Displays processed images in separate windows.

#### Processing Steps:
- Adds random noise to the image.
- Applies Gaussian blur.
- Generates low-contrast and high-contrast images.
- Performs global thresholding using Otsu's and Triangle methods.
- Applies adaptive mean and Gaussian thresholding.
- Inverts the image colors.

### 3. `open_file()`
Opens a file selection dialog to choose an image file for processing.

### 4. `close_windows()`
Closes all OpenCV windows.

---

## Example
When selecting an image, the following windows might appear:

- **Original**: Displays the original grayscale image.
- **Noisy**: Displays the image with added random noise.
- **Blurred**: Displays the image after Gaussian blurring.
- **Low Contrast**: Displays the image with reduced contrast.
- **High Contrast**: Displays the image with enhanced contrast.
- **Global Thresh Otsu**: Shows the binary image after Otsu's global thresholding.
- **Adaptive Thresh Mean**: Shows the binary image after adaptive mean thresholding.
- **Inverted**: Displays the color-inverted image.

---

## Notes
- Ensure the selected image is in grayscale for accurate processing.
- Supported image formats: JPEG, PNG.
- The application ignores unsupported or invalid image files.

---

## License
This project is licensed under the MIT License.

