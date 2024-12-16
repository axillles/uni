import cv2
import numpy as np
from tkinter import Tk, filedialog, Button, Label
from PIL import Image, ImageTk

def linear_contrast(image, alpha, beta):
    return cv2.convertScaleAbs(image, alpha=alpha, beta=beta)

def apply_processing(image_path):
    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)

    # добавление шума
    noise = np.random.normal(0, 25, image.shape).astype(np.uint8)
    noisy_image = cv2.add(image, noise)

    # размытие изображения
    blurred_image = cv2.GaussianBlur(image, (5, 5), 0)

    # малоконтрастное изображение
    low_contrast_image = linear_contrast(image, 0.5, 0)

    # глобальная пороговая обработка отсу
    _, global_thresh_otsu = cv2.threshold(image, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

    # глобальная пороговая обработка
    _, global_thresh_triangle = cv2.threshold(image, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_TRIANGLE)

    # адаптивная пороговая обработка
    adaptive_thresh_mean = cv2.adaptiveThreshold(image, 255, cv2.ADAPTIVE_THRESH_MEAN_C,
                                                 cv2.THRESH_BINARY, 11, 2)
    adaptive_thresh_gaussian = cv2.adaptiveThreshold(image, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C,
                                                     cv2.THRESH_BINARY, 11, 2)

    #поэлементные операции инверсия
    inverted_image = cv2.bitwise_not(image)

    #линейное контрастирование
    high_contrast_image = linear_contrast(image, 1.5, 0)

    cv2.imshow('Original', image)
    cv2.moveWindow('Original', 0, 0)
    cv2.imshow('Noisy', noisy_image)
    cv2.moveWindow('Noisy', 300, 0)
    cv2.imshow('Blurred', blurred_image)
    cv2.moveWindow('Blurred', 600, 0)
    cv2.imshow('Low Contrast', low_contrast_image)
    cv2.moveWindow('Low Contrast', 900, 0)

    cv2.imshow('Global Thresh Otsu', global_thresh_otsu)
    cv2.moveWindow('Global Thresh Otsu', 0, 300)
    cv2.imshow('Adaptive Thresh Mean', adaptive_thresh_mean)
    cv2.moveWindow('Adaptive Thresh Mean', 300, 300)
    cv2.imshow('Inverted', inverted_image)
    cv2.moveWindow('Inverted', 600, 300)
    cv2.imshow('High Contrast', high_contrast_image)
    cv2.moveWindow('High Contrast', 900, 300)


def open_file():
    file_path = filedialog.askopenfilename(filetypes=[("Image files", "*.jpg *.jpeg *.png")])
    if file_path:
        apply_processing(file_path)

def close_windows():
    cv2.destroyAllWindows()

# Создание графического интерфейса
root = Tk()
root.title("Image Processing App")

open_button = Button(root, text="Выбрать изображение", command=open_file)
open_button.pack(pady=10)

stop_button = Button(root, text="Стоп", command=close_windows)
stop_button.pack(pady=10)

root.mainloop()
