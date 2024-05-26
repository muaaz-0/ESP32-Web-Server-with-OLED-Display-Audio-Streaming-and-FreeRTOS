
# **ESP32 Web Server with OLED Display, Audio Streaming, and FreeRTOS**

This project demonstrates how to create a web server on an ESP32, display information on an OLED screen, stream audio using the MAX98357 I2S amplifier module, and manage tasks using FreeRTOS. The web server allows controlling multiple GPIO pins and displays their states on a web page.

# **Features**

**Web Server:** Control multiple GPIO pins and monitor their states through a web interface.

**OLED Display:** Display the states of GPIO pins on an OLED screen.

**Audio Streaming:** Stream audio using the MAX98357 module via I2S protocol.

**FreeRTOS:** Manage concurrent tasks for the web server and audio streaming.


## **Libraries Used**
- Arduino

- Adafruit GFX Library

- Adafruit SSD1306 Library

- ESP32 Core

- Audio Library

- FreeRTOS

**Note:** For audio library, use this audio library [ESP32 Audio I2S Library](https://github.com/schreibfaul1/ESP32-audioI2S)
## **Pin Configuration**

**Output pins:** 

The following pins have been configured as Output and will be controlled through the web server using On/OFF buttons

```bash
 
const int output23 = 23;
const int output1  = 1;
const int output3  = 3;
const int output19 = 19;
const int output18 = 18;
const int output5 = 5;
const int output17 = 17;
const int output16 = 16;
const int output4  = 4;
const int output2  = 2;
const int output15  = 15;
```

**Output pins:**
Similarly, the following pins have been configured as input.
```bash
const int input36=36;
const int input39=39;
const int input34=34;
const int input35=35;
const int input32=32;
const int input33=33;
const int input14=14;
const int input12=12;
const int input13=13;
```
## **Web Server**
The web server is created using an HTML script with buttons to control and monitor the GPIO pins. For output pins buttons have been created showing the ON or OFF state. Also, the state of input pins (HIGH or LOW) is displayed on the web page. The web page refreshes every 7 seconds to update the states of the pins using an HTML tag:

```bash
 client.println("<meta http-equiv=\"refresh\" content=\"7\">");

```
## **Audio Streaming**
Audio is streamed using the MAX98357 module, which communicates via the I2S protocol. The I2S pins are configured as follows:
Note: Don't forget to connect the gain to the ground.

```bash
 
#define I2S_DOUT  27
#define I2S_BCLK  26
#define I2S_LRC   25

```
## **OLED Display**
The state of each GPIO pin is also displayed on the OLED screen. Whenever the state of a GPIO pin is changed through the web server, it is updated on the OLED display.
![WhatsApp Image 2024-05-22 at 1 50 59 PM](https://github.com/muaaz-0/ESP32-Web-Server-with-OLED-Display-Audio-Streaming-and-FreeRTOS/assets/74170095/366988ee-75e8-43b2-877c-ce7ff92bc67e)

## **RTOS for Tasks** 
FreeRTOS is used to manage multiple tasks running concurrently. Two tasks with the same priority are created to handle the radio player and the web server simultaneously. Both the tasks run in a round-robin way to give the output.

```bash
 
xTaskCreatePinnedToCore( task_Speaker,
                              "Connect Speaker",
                              2000,
                              NULL,
                              2,
                              &task_Speaker_Handle,
                              app_cpu);
     xTaskCreatePinnedToCore( task_Web,
                                "Control_Web",
                                2000,
                                NULL,
                                2,
                                &task_Web_Handle,
                                app_cpu);
  

```
