import os
import tkinter as tk
from tkinter import filedialog
from PIL import Image

def get_image_info(image_path):
    try:
        with Image.open(image_path) as img:
            info = {
                "filename": os.path.basename(image_path),
                "size": img.size,
                "dpi": img.info.get('dpi', (None, None)),
                "color_depth": img.mode,
                "compression": img.info.get('compression', 'N/A')
            }
            return info
    except Exception as e:
        return {"error": str(e)}

def open_file_dialog():
    file_paths = filedialog.askopenfilenames(
        title="Select Image Files",
        filetypes=[("Image Files", "*.jpg *.jpeg *.gif *.tif *.bmp *.png *.pcx")]
    )
    if file_paths:
        image_data = [get_image_info(path) for path in file_paths]
        display_image_data(image_data)

def open_folder_dialog():
    folder_path = filedialog.askdirectory(title="Select Folder")
    if folder_path:
        file_paths = [os.path.join(folder_path, f) for f in os.listdir(folder_path)
                      if f.lower().endswith(('.jpg', '.jpeg', '.gif', '.tif', '.bmp', '.png', '.pcx'))]
        image_data = [get_image_info(path) for path in file_paths]
        print(image_data)
        display_image_data(image_data)

def display_image_data(image_data):
    result_text.delete(1.0, tk.END)
    result_text.insert(tk.END, f"{'Filename':<30}\n{'Size':<15}\n{'DPI':<10}\n{'Color Depth':<15}\n{'Compression':<15}\n")
    result_text.insert(tk.END, "=" * 85 + "\n")

    for info in image_data:
        if 'error' in info:
            result_text.insert(tk.END, f"Error processing file: {info['error']}\n\n")
        else:
            dpi_values = f"{info['dpi'][0]}x{info['dpi'][1]}" if info['dpi'] and all(info['dpi']) else "N/A"
            result_text.insert(
                tk.END,
                f"{info['filename']:<30}\n{info['size'][0]}x{info['size'][1]:<15}\n{dpi_values:<10}\n{info['color_depth']:<15}\n{info['compression']:<15}\n\n"
            )

app = tk.Tk()
app.title("Image Info Extractor")

open_file_button = tk.Button(app, text="Open Images", command=open_file_dialog)
open_file_button.pack(pady=10)

open_folder_button = tk.Button(app, text="Open Folder", command=open_folder_dialog)
open_folder_button.pack(pady=10)

result_text = tk.Text(app, width=100, height=20)
result_text.pack(pady=10)

app.mainloop()
