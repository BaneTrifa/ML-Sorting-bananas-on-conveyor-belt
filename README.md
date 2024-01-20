# Sorting-bananas-on-conveyor-belt
## Description
Selection of bananas based on maturity using a camera on a conveyor belt.

## Data preprocessing:
The basic dataset consisted of about 500 images, and all other images were obtained through augmentation of these basic images. The augmentation was performed manually in the Qt Creator environment using the C++ language, without the assistance of any software.

The complete dataset (with augmentation) consists of 2705 images. The images are divided into 3 sets: 
  1. train - 1945 images 
  2. test - 260 images
  3. val - 500 images

Images are located in the folder dataset/images. Each image is labeled and the labels are located in the dataset/labels folder.

Labling images is done using [Roboflow](https://roboflow.com/).



## Implementation
The model used for training and selection is YOLOv8. The complete system schematic is shown below:

<p align="center">
<img width="648" alt="banan_sorting" src="https://github.com/BaneTrifa/ML-Sorting-bananas-on-conveyor-belt/assets/88882867/52b1af04-3fa0-48fc-a71d-cb3ff360eff5">
</p>


The parts of the system are:

1. **Conveyor belt**
2. **First stepper motor** - Used for constant rotation of the conveyor belt.
3. **PC or RPi** - It serves as a machine that deploys the model it works on. It receives an image in real-time from a camera that records the belt, which it then passes through the model. Based on the determination of whether the banana has passed (ripe or unripe), it sends a signal to the Arduino on how to rotate the bar.
4. **Second stepper motor** - It serves to receive signals from the PC or RPi and turn the second motor with the bar in a certain direction. But it also constantly rotates the first motor.
5. **Second stepper motor** - It serves to rotate the bar depending on whether the banana that arrives is ripe or unripe. If the banana is not ripe, the motor positions the bar so that the banana hits the container with ripe bananas (to the left of the tape); otherwise, the banana falls into the container with ripe bananas.It serves to rotate the bar depending on whether the banana that arrives is ripe or unripe. If the banana is not ripe, the motor positions the bar so that the banana falls into the container with unripe bananas (to the left of the belt); otherwise, the banana falls into the container with ripe bananas.

## Author
- [@BrankoTrifkovic](https://www.linkedin.com/in/branko-trifkovic/)
