# acoustic-detection
Feature Acquisition Algorithm and Edge Computing for Acoustic Defect Detection in smart manufacturing

## Background
The detection of invisible cracks in empty glass bottles is an important process before the filling of liquor production. Light inspection is used to ensure the integrity of empty bottles before filling. However, in the actual production process, the compulsory light inspection by labor is long, high labor intensity, and large-employees, which increases Labor costs, management difficulties and other issues. Furthermore, with the liquor industry from the traditional manual work, manual tactics to mechanization, automation, information technology, intelligent production to march forward during the process, the detection of invisible cracks in empty bottles poses new challenges, such as fully automatic online detection and online automatic rejection, and therefore use machines instead of manual labor to reduce labor intensity, increase production efficiency and ensure product quality.

## dataset

This paper sets glass bottles as experiment objects. The data set is collected from a prototyping platform. Firstly, we set 2000 percussion signals generated from 1000 defective and 1000 defect-free bottles as experiment data. Then, we divide all data into the training set with 1200 signals and the test set with 800 signals. Among training set and testing set, the defective and defect-free bottles have equal sample number.

It is noted that there are two splitting method for dataset, which is respectively split randomly and by time.

## Prototyping platform of LearningADD system



The prototyping platform of LearningADD system is introduced as following.



### 1）System block diagram
**（1）System block diagram**.

![System_block_diagram](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/System_block_diagram.png)

**（2）Prototyping system of LearningADD system**.
![prototyping_platform](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/prototyping_platform.png)


### 2）Data stream

![data_stream](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/data_stream.png)

### 3）Experimental workshop

![workshop](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/workshop.png)


### 4）Experimental subject

![glass_bottle](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/glass_bottle.png)
![glass_bottles](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/glass_bottles.png)

### 5）Conveyor belt
![Conveyor_belt](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/Conveyor_belt.png)


### 6）Positioning equipment

![Positioning_equipment](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/Positioning_equipment.jpg)

### 7）Acoustic collection module
![Acoustic_collection2](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/Acoustic_collection2.jpg)

![Acoustic_collection](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/Acoustic_collection.jpg)

### 8）Field Controller
Field_controller:

![Field_controller](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/Field_controller.jpg)

dsk5416:
![dsk5416](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/dsk5416.jpg)

### 9）Waveform display

![waveform](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/waveform.jpg)

![waveform2](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/waveform2.jpg)

### 10）Defect Indicator
![Defect_indicator](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/Defect_indicator.jpg)


### 11）Rejection equipment

![rejection](https://github.com/TJU-DSPLAB/LearningADD/tree/master/images/rejection.jpg)


### 12）vedios

<video id="video" controls="" preload="none"
    poster="/vedios/waveform_display.MOV">
     <source id="MOV" src="https://github.com/TJU-DSPLAB/LearningADD/tree/master/vedios/waveform_display.MOV" 
         type="video/MOV">
      <p>Your user agent does not support the HTML5 Video element.</p>
</video>

<iframe 
    width="400" 
    height="450" 
    src="https://github.com/TJU-DSPLAB/LearningADD/tree/master/vedios/waveform_display.MOV"
    frameborder="0" 
    allowfullscreen>
</iframe>

<iframe 
    width="400" 
    height="450" 
    src="https://github.com/TJU-DSPLAB/LearningADD/tree/master/vedios/device1.mp4"
    frameborder="0" 
    allowfullscreen>
</iframe>


<iframe 
    width="400" 
    height="450" 
    src="https://github.com/TJU-DSPLAB/LearningADD/tree/master/vedios/device2.mp4"
    frameborder="0" 
    allowfullscreen>
</iframe>

<iframe 
    width="400" 
    height="450" 
    src="https://v.miaopai.com/iframe?scid=SvyHaHOczsp7B6ftW86oqMMz62-h5ai6~Fwp8A__"
    frameborder="0" 
    allowfullscreen>
</iframe>