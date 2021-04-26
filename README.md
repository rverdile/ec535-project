# EC535 Project: Centipede

Centipede is a classic, fixed shooter arcade game. The primary objective is to shoot all the segments of a centipede that navigates through a field of mushrooms towards the player. This project a is version of Centipede coded for the BeagleBone Black and an LCD touchscreen. A USB keyboard is also required. 

To build the project, copy all files from this repository to eng-grid. Be sure to run:

```
source /ad/eng/courses/ec/ec535/bashrc_ec535
```

In the directory containing the Centipede code, run:

```
qmake
make
```

This will make an executable named Centipede. Copy this file to the root folder of your rootfs and rebuild the SD card image. Flash the SD card with the updated image. Before starting up the BeagleBone, make sure you have plugged in USB keyboard. Power on the BeagleBone and log in. To start the game, run:

```
./Centipede
```

This repository also contains a version of the game that can be run using Qt Creater on a computer. To get this version, pull from the computer branch instead of main.
