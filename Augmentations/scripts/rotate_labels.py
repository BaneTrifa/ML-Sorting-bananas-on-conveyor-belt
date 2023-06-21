import os

def rotate_bbox(bbox, image_width, image_height):
    # Calculate center coordinates and dimensions
    x, y, w, h = bbox

    # Calculate rotation center (image center)
    center_x = image_width / 2
    center_y = image_height / 2

    # Convert to absolute coordinates
    abs_x = x * image_width
    abs_y = y * image_height
    abs_w = w * image_width
    abs_h = h * image_height

    # Rotate center coordinates
    new_cx = center_x + (abs_y - center_y)
    new_cy = center_y - (abs_x - center_x)

    # Calculate new dimensions
    new_w = abs_h
    new_h = abs_w

    # Convert back to normalized coordinates
    new_x = new_cx / image_width
    new_y = new_cy / image_height
    new_w /= image_width
    new_h /= image_height

    return new_x, new_y, new_w, new_h


if __name__ == "__main__":
    in_dir_path = '/home/branko/Documents/ADOS/ADOS_PZ1_Labeling_and_Augmentation/ADOS_PZ1_Labeling_and_Augmentation/datasets/train/labels'
    out_dir_path = '/home/branko/Desktop/ADOS_PZ1/ADOS_PZ1_Labeling_and_Augmentation/ADOS_PZ1_Labeling_and_Augmentation/datasets/train/labels'
    entries = os.listdir(in_dir_path)
    image_width = 640  # Example image width
    image_height = 640  # Example image height

    for in_labels in entries:
        label_file = open(f'{in_dir_path}/' + in_labels, 'r')
        labels = label_file.readlines()
        label_file.close()

        rotate_labels = []
        for label in labels:
            label = label.strip().split()
            x_center, y_center, box_w, box_h = map(float, label[1:])
            bbox = (x_center, y_center, box_w, box_h)

            yolo_x, yolo_y, yolo_w, yolo_h = rotate_bbox(bbox, image_width, image_height)

            new_label = f"{label[0]} {yolo_x} {yolo_y} {yolo_w} {yolo_h}\n"
            rotate_labels.append(new_label)

        label_file = open(f'{out_dir_path}/a2_' + in_labels, 'w')
        label_file.writelines(rotate_labels)
        label_file.close()

