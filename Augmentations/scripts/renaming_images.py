import os

# set directory path
directory_path = "C:\\Users\\tbran\\Desktop\\BRANKO\\E2\\1_FTN_E2\\DRUGI_SEMESTAR\\ADOS\\Project\\Banana data set"

# get all filenames in directory
files = os.listdir(directory_path)

# set starting index for filenames
index = 0

# loop through all files in directory
for file in files:
    # get file extension
    extension = os.path.splitext(file)[1]

    # create new filename with 3-digit index and original extension
    new_filename = "IMG" + str(index).zfill(3) + extension

    # construct full path for current and new filenames
    current_path = os.path.join(directory_path, file)
    new_path = os.path.join(directory_path, new_filename)

    # rename file
    os.rename(current_path, new_path)

    # increment index for next filename
    index += 1
