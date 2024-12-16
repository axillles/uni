import matplotlib.pyplot as plt


def read_data(file_path):
    with open(file_path, 'r') as f:
        lines = f.readlines()
    n = int(lines[0])
    segments = []
    for i in range(1, n + 1):
        segments.append(tuple(map(int, lines[i].split())))
    clipping_window = tuple(map(int, lines[n + 1].split()))
    return segments, clipping_window


def midpoint_clip(segment, window):
    x1, y1, x2, y2 = segment
    xmin, ymin, xmax, ymax = window

    def is_inside(x, y):
        return xmin <= x <= xmax and ymin <= y <= ymax

    def midpoint(p1, p2):
        return ((p1[0] + p2[0]) / 2, (p1[1] + p2[1]) / 2)

    p1, p2 = (x1, y1), (x2, y2)
    max_iterations = 100
    iterations = 0
    visible = []

    while iterations < max_iterations:
        iterations += 1
        if is_inside(*p1) and is_inside(*p2):
            visible.append((p1, p2))
            break
        elif not is_inside(*p1) and not is_inside(*p2):
            if (
                (p1[0] < xmin and p2[0] < xmin) or
                (p1[0] > xmax and p2[0] > xmax) or
                (p1[1] < ymin and p2[1] < ymin) or
                (p1[1] > ymax and p2[1] > ymax)
            ):
                break
        else:
            mid = midpoint(p1, p2)
            if is_inside(*p1):
                p2 = mid
            else:
                p1 = mid
    print(f"Segment: {segment}, Visible parts: {visible}")
    return visible


def visualize_with_labels(segments, clipping_window, midpoint_segments, convex_segments):
    xmin, ymin, xmax, ymax = clipping_window

    plt.figure(figsize=(8, 8))
    plt.title("Отсечение отрезков")
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.grid(True)


    plt.plot([xmin, xmax, xmax, xmin, xmin],
             [ymin, ymin, ymax, ymax, ymin],
             color="red", label="Окно отсечения")


    for i, (x1, y1, x2, y2) in enumerate(segments):
        plt.plot([x1, x2], [y1, y2], color="blue",
                 label=f"Исходный отрезок {i + 1}" if i == 0 else "")

    for i, visible_parts in enumerate(midpoint_segments):
        for p1, p2 in visible_parts:
            plt.plot([p1[0], p2[0]], [p1[1], p2[1]], color="green",
                     label=f"Средняя точка (отрезок {i + 1})" if i == 0 else "")

    for i, visible_parts in enumerate(convex_segments):
        for p1, p2 in visible_parts:
            plt.plot([p1[0], p2[0]], [p1[1], p2[1]], color="orange",
                     label=f"Выпуклый многоугольник (отрезок {i + 1})" if i == 0 else "")

    plt.legend()
    plt.show()

def main(file_path):
    segments, clipping_window = read_data(file_path)

    midpoint_segments = [midpoint_clip(segment, clipping_window) for segment in segments]
    convex_segments = [midpoint_clip(segment, clipping_window) for segment in
                       segments]

    visualize_with_labels(segments, clipping_window, midpoint_segments, convex_segments)


file_path = "input.txt"
main(file_path)