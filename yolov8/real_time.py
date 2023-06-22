import cv2
from ultralytics import YOLO
import supervision as sv
import serial
import time

mode = 1 # 0-train, 1-detect
model = YOLO('C:/Users/tbran/Desktop/banana_detection_model/script/runs/detect/train6/weights/best.pt')
class_id = ["OverRipe", "Ripe", "VeryRipe"]
#class_id = ['O', 'R', 'V']

if __name__ == "__main__":
    arduino = serial.Serial(port='COM4', baudrate=9600, bytesize=8)
    time.sleep(3)

    if mode == 0:
        model.train(data='data.yaml', epochs=50, imgsz=640)
    else:
        video = cv2.VideoCapture(0)
        bounding_box_annotator = sv.BoxAnnotator(thickness=2, text_thickness=2, text_scale=1)

        while (True):

            ret, frame = video.read()
            results = model(frame, conf=0.6)[0]
            detections = sv.Detections.from_yolov8(results)

            # Extracting confidence score and class id from above results
            results_list = results.boxes.data.tolist()
            for data in results_list:
                print(data)
                if int(data[5]) != 1:
                    command = '1'
                    arduino.write(command.encode())


            # Drawing bounding boxes on the frame
            frame = bounding_box_annotator.annotate(scene=frame, detections=detections)

            cv2.imshow('yolo', frame)

            # Exit key is ESC
            if cv2.waitKey(30) == 27:
                break

        # Close serial port
        arduino.close()
        # After the loop release the cap object
        video.release()
        # Destroy all the windows
        cv2.destroyAllWindows()