import os

path_in = "datasets/train/images/"
path_out = "datasets/train/images/"

absolute_path = os.path.dirname(__file__)
full_path = os.path.join(absolute_path, path_in)

entries = os.listdir(path_in)

for in_img_name in entries:
    hue_increase = 10
    h_blocks = 5
    w_blocks = 5
    percentage = 50
    angle = 90
    N = 64
    B = 64
    lambda_coeff = -0.5

    os.system('./ImageDSP/build/linux/build-ImageDSP-Desktop-Debug/ImageDSP --prog-name "Hue Change" --in-img "datasets/train/images/' + in_img_name + '" --out-img "datasets/train/images/a0_' + in_img_name + '" --params "' + str(hue_increase) + '"')

    os.system('./ImageDSP/build/linux/build-ImageDSP-Desktop-Debug/ImageDSP --prog-name "Hide n Seek" --in-img "datasets/train/images/' + in_img_name + '" --out-img "datasets/train/images/a1_' + in_img_name + '" --params "' + str(w_blocks) + ';' + str(h_blocks) + ';' + str(percentage) + '"')

    os.system('./ImageDSP/build/linux/build-ImageDSP-Desktop-Debug/ImageDSP --prog-name "Rotate" --in-img "datasets/train/images/' + in_img_name + '" --out-img "datasets/train/images/a2_' + in_img_name + '" --params "' + str(angle) + '"')

    os.system('./ImageDSP/build/linux/build-ImageDSP-Desktop-Debug/ImageDSP --prog-name "Unsharp Masking" --in-img "datasets/train/images/' + in_img_name + '" --out-img "datasets/train/images/a3_' + in_img_name + '" --params "' + str(N) + ';' + str(B) + ';' + str(lambda_coeff) + '"')
