import os
import shutil

images_directory = "C:/Users/tbran/Desktop/updated_set/images"
dst_labels_directory = "C:/Users/tbran/Desktop/updated_set/labels"
src_labels_directory = "C:/Users/tbran/Desktop/downloaded_set/valid/labels"

in_files = os.listdir(images_directory)
in_labels = os.listdir(src_labels_directory)

for file in in_files:
    file = file[:len(file)-4]
    for label in in_labels:
        label = label[:len(label) - 4]
        if label == file:
            original_path = os.path.join(src_labels_directory, label+".txt")
            duplicate_path = os.path.join(dst_labels_directory, label+".txt")
            shutil.copy2(original_path, duplicate_path)