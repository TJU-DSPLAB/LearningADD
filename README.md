# Acoustic-detection
Machine Learning based Acoustic Defect Detection in Factory Automation: Feature Extraction and Deployment Strategies

## Background
The detection of invisible cracks in empty glass bottles is an important process before the filling of liquor production. Light inspection is used to ensure the integrity of empty bottles before filling. However, in the actual production process, the compulsory light inspection by labor is long, high labor intensity, and large-employees, which increases Labor costs, management difficulties and other issues. Furthermore, with the liquor industry from the traditional manual work, manual tactics to mechanization, automation, information technology, intelligent production to march forward during the process, the detection of invisible cracks in empty bottles poses new challenges, such as fully automatic online detection and online automatic rejection, and therefore use machines instead of manual labor to reduce labor intensity, increase production efficiency and ensure product quality.

## dataset

This paper sets glass bottles as experiment objects. The data set is collected from a prototyping platform. Firstly, we set 2000 percussion signals generated from 1000 defective and 1000 defect-free bottles as experiment data. Then, we divide all data into the training set with 1200 signals and the test set with 800 signals. Among training set and testing set, the defective and defect-free bottles have equal sample number.

It is noted that there are two splitting method for dataset, which is respectively split randomly and by time.

## Prototyping platform of LearningADD system

The prototyping platform of LearningADD system is introduced as following.

Note that, if the pictures and videos in this page are not visible, please visit [http://dingby.site/2020/06/25/Prototyping-platform-of-LearningADD-system/](http://dingby.site/2020/06/25/Prototyping-platform-of-LearningADD-system/).

### 1）System block diagram
**（1）System block diagram**. The system mainly consists of Data Collection, Defect Detection, and Control Action. Here, the classifier is built after feature extraction. The decision output is used to control Defect Indicator and Rejection Equipment for defective bottle.

![System_block_diagram](/images/System_block_diagram.png)


**（2）Prototyping system of LearningADD system**.
Prototyping system of LearningADD system collects acoustic signals and control related equipment. Firstly, Object under Detection(glass bottles) is conveyed to Positioning Equipment by Conveyor Belt. Here, Positioning Equipment ensures the correct distance between the bottle and Knocking Equipment (metal rod). Secondly, the bottle is sent to Object Detector (pair tube photoelectric) for checking its passing. Finally, acoustic signal is collected by an Acoustic Collection Module after knocking a bottle body by Knocking Equipment.

After collecting the acoustic signal, the signal is transmitted to Field Controller including Industrial Personal Computer (IPC) and Digital Signal Processor dsk5416. Then, Defect Indicator will display the decision output. Finally, the defective bottles will be rejected by Rejection Equipment.

![prototyping_platform](/images/prototyping_platform.png)


### 2）Data stream

The picture show that the data stream in device layer.

![data_stream](/images/data_stream.png)

### 3）Experimental workshop

![workshop](/images/workshop.png)


### 4）Experimental subject

![glass_bottle](/images/glass_bottle.png)
![glass_bottles](/images/glass_bottles.png)

### 5）Conveyor belt
![Conveyor_belt](/images/Conveyor_belt.png)


### 6）Positioning equipment

![Positioning_equipment](/images/Positioning_equipment.jpg)

### 7）Acoustic collection module
![Acoustic_collection2](/images/Acoustic_collection2.jpg)

![Acoustic_collection](/images/Acoustic_collection.jpg)

### 8）Field Controller
Field_controller:

![Field_controller](/images/Field_controller.jpg)

dsk5416:
![dsk5416](/images/dsk5416.jpg)

### 9）Waveform display

![waveform](/images/waveform.jpg)

![waveform2](/images/waveform2.jpg)

### 10）Defect Indicator
![Defect_indicator](/images/Defect_indicator.jpg)


### 11）Rejection equipment

![rejection](/images/rejection.jpg)


### 12）vedios

<iframe 
    width="400" 
    height="450" 
    src="/vedios/device1.mp4"
    frameborder="0" 
    allowfullscreen>
</iframe>

<iframe 
    width="400" 
    height="450" 
    src="/vedios/device2.mp4"
    frameborder="0" 
    allowfullscreen>
</iframe>

<iframe 
    width="400" 
    height="450" 
    src="/vedios/waveform_display.mp4"
    frameborder="0" 
    allowfullscreen>
</iframe>
