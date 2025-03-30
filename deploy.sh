# To get the compliler on linux: sudo apt-get install g++-arm-linux-gnueabihf
# you can get it on windows too, but idk how. get ready to learn WSL buddy

arm-linux-gnueabihf-g++ main.cpp -o SIO.out
scp SIO.out rpirobo@192.168.1.2:~/SIO/SIO.out