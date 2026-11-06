# ESP32_devlopment

I'm using esp32-s3 board for these projects.

## Tools required
- arduino-cli

## Install and Setup
We need to install the specific tools to be able to use arduino-cli to compile binary for esp32.
```bash
arduino-cli config add board_manager.additional_urls https://espressif.github.io/arduino-esp32/package_esp32_index.json
arduino-cli core update-index
arduino-cli core install esp32:esp32
```
To check if your board is detected or not, use the following command after connecting the esp32-s3 board via USB port.
```bash
arduino-cli board list
```
User should be the part of the group "uucp" to be able to interact with the connected board <br>
```bash
sudo usernod -aG uucp $USER
```
> NOTE :
> We'll always use the USB port to flash the board not the COM port. 

---

## Creating project
To create a new project use the following command
```bash
arduino-cli sketch new project0
```
this will create a `project0/project0.ino` file where we will write our code.

---

## Compiling and Flashing
for normal firmware that does not need to act as HID device to communicate with other devices we can use these simple commands to compile and upload the binary to the esp32 board.
```bash
arduino-cli compile --fqbn esp32:esp32:esp32s3 project0
arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 project0
```
and for the projects that does require the use of USB port to act as HID device, we use the following.
```bash
arduino-cli compile --fqbn esp32:esp32:esp32s3:USBMode=default project0
arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:esp32s3:USBMode=default project0
```

---

## Debugging
To debug your code you can set the value of baudrate in the `setup()` function inside the `project0/project0.ino` file.
```c
void setup() {
  Serial.begin(115200);
}
```
after this you can use the `Serial.println();` to debug your program.<br>
To see the output you'll have to interact with the board using the monitor mode.<br>
Use the following command to monitor the output of your esp32 board.
```bash
arduino-cli monitor -p /dev/ttyACM0 -c baudrate=115200
```
Alternatively, we can also use the inbuilt RGB light of the esp32-s3 board to display different state of our program.
```c
void blink() {
  neopixelWrite(RGB_BUILTIN, 25, 25, 25);  // (R, G, B: 0-255)
  delay(50);
  neopixelWrite(RGB_BUILTIN, 0, 0, 0);     // off
}
```
