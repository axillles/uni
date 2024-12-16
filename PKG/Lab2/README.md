# Image Info Extractor

This Python application allows users to extract metadata from image files, such as dimensions, DPI, color depth, and compression type. It features a graphical user interface (GUI) built with Tkinter for selecting individual image files or entire folders of images for analysis.

---

## Features
- **File and Folder Selection**:
  - Select individual image files for metadata extraction.
  - Analyze all supported image files within a chosen folder.
- **Metadata Extraction**:
  - File name
  - Dimensions (width x height)
  - DPI (dots per inch)
  - Color depth (image mode)
  - Compression type
- **Supported Image Formats**: JPEG, PNG, BMP, GIF, TIFF, PCX
- **Error Handling**: Gracefully handles unsupported or corrupted files.

---

## How to Run

### Prerequisites
- Python 3.8+
- Required Python libraries:
  - `tkinter` (comes pre-installed with Python on most systems)
  - `Pillow` (Python Imaging Library fork)

### Install Dependencies
```bash
pip install pillow
```

### Running the Application
1. Save the script to a file, e.g., `image_info_extractor.py`.
2. Run the script:
   ```bash
   python image_info_extractor.py
   ```
3. The application window will open, allowing you to select files or folders for analysis.

---

## User Interface
- **Buttons**:
  - **Open Images**: Opens a file dialog to select one or more image files.
  - **Open Folder**: Opens a folder dialog to select a directory containing image files.
- **Result Display**: A text area that lists extracted metadata for all processed images.

---

## Functions

### 1. `get_image_info(image_path)`
Extracts metadata from a given image file.
- **Input**: Path to the image file.
- **Output**: A dictionary containing the file’s metadata or an error message if processing fails.

### 2. `open_file_dialog()`
Opens a file selection dialog to choose individual image files for analysis.
- **Action**: Extracts metadata from selected files and displays the results in the GUI.

### 3. `open_folder_dialog()`
Opens a folder selection dialog to choose a directory containing image files.
- **Action**: Extracts metadata from all supported image files in the selected folder and displays the results in the GUI.

### 4. `display_image_data(image_data)`
Formats and displays extracted metadata in the text area of the GUI.
- **Input**: List of metadata dictionaries from processed images.

---

## Example Output
When analyzing an image, the following details might be displayed:

```
Filename: example.jpg
Size: 1920x1080
DPI: 72x72
Color Depth: RGB
Compression: JPEG

Filename: another_image.png
Size: 1024x768
DPI: N/A
Color Depth: RGBA
Compression: N/A

Error processing file: Unsupported format or corrupted image.
```

---

## Notes
- The application ignores non-image files and unsupported formats within selected folders.
- DPI and compression information may not be available for some image formats.

---

## License
This project is licensed under the MIT License.

