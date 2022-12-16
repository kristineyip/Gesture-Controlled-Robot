# Gesture-Controlled-Robot
A gesture-controlled robotic system involving machine learning and two Arduino BLEs.

This is my final project for ESE3600 (Machine Learning on Embedded Systems) at the Univ. of Pennsylvania.

This application consists of:
- A central Arduino, which runs classification on input gestures locally and publishes to the service
- A peripheral Arduino, which executes robot movements based on the classification

The machine learning model was trained on a custom dataset of 7 classes (idle, forward, backward, left, right, squiggle) with ~100 samples each.

A demo of the project working for a few classifications:
