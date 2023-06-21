import os
import shutil

# set directory path
directory_path = "/home/branko/Desktop/ADOS_PZ1/ADOS_PZ1_Labeling_and_Augmentation/ADOS_PZ1_Labeling_and_Augmentation/datasets/valid/labels"

# get all filenames in directory
files = os.listdir(directory_path)

# loop through all files in directory
for file in files:

    new_filename0 = "a0_" + file
    new_filename1 = "a1_" + file
    new_filename2 = "a3_" + file

    # construct full path for current and new filenames
    original_path = os.path.join(directory_path, file)
    duplicate_path0 = os.path.join(directory_path, new_filename0)
    duplicate_path1 = os.path.join(directory_path, new_filename1)
    duplicate_path2 = os.path.join(directory_path, new_filename2)

    shutil.copy2(original_path, duplicate_path0)
    shutil.copy2(original_path, duplicate_path1)
    shutil.copy2(original_path, duplicate_path2)