# EMG-MeArm

Use of EMG sensors in controlling a grabbing motion from the MeArm robot. 

This project was for an open ended final project for my robotics course. I wanted to experiment with control by EMG sensors in order to implement a very simple version of the controls involved in many prosthetic limbs. If I could sufficiently control a grabbing motion based on one muscle, it would be matter of repitition to control more axes with more muscles.

The forward and reverse kinematics are calculated in Matlab and the M files are included. The equations generated from those calculations are then plugged into Arduino.

The EMG signal is taken in through an Olimex EKG-EMG shield. From there it is filtered within the code. Using threshholds allowed decent control of a grab motion, but how much the signal is snoothed is a double edged sword. Too little smoothing causes the thresh hold to be repeatedly crossed by the signal, causing jerky control. Too much caused slow responses as it took too long for the signal to change. I believe the solution is to put greater emphasis on using RMS values and less on direct smoothing.

Materials: Arduino Uno, EMG shield (https://www.amazon.com/gp/product/B00DK298G2/ref=oh_aui_detailpage_o03_s00?ie=UTF8&psc=1), EMG cable (https://www.amazon.com/gp/product/B00K9487UC/ref=oh_aui_detailpage_o05_s01?ie=UTF8&psc=1), electrodes (https://www.amazon.com/gp/product/B001E1UHFM/ref=oh_aui_detailpage_o05_s00?ie=UTF8&psc=1), MeArm robot (https://shop.mime.co.uk/collections/frontpage/products/mearm-pocket-sized-robot-arm)
