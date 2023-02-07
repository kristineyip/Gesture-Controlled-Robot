# Gesture-Controlled-Robot
A gesture-controlled robotic system involving machine learning and two Arduino BLEs.

This is my final project for ESE3600 (Machine Learning on Embedded Systems) at the Univ. of Pennsylvania.

This application consists of:
- A central Arduino, which runs classification on input gestures locally and publishes to the service
- A peripheral Arduino, which executes robot movements based on the classification

The machine learning model was trained on a custom dataset of 7 classes (idle, forward, backward, left, right, squiggle) with ~100 samples each.

## Demo Clips

https://user-images.githubusercontent.com/90000011/217140441-9e798125-5cd9-4d87-9052-7a099da77ef1.mov



https://user-images.githubusercontent.com/90000011/217140450-6b71eacc-738e-446b-847a-3efd78135072.mov

