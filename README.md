# High Tech Christmas 2.0
A wireless E1.31 system for controlling Neopixels (WS2812) with ESP8266 and Vixen Lights

## Background ##
Christmas comes around every year and there are many passionate embedded enthusiasts such as myself who find the desire to animate colorful lights around the house. Neopixels (WS2811 or WS2812) are serially addressable RGB LEDs that can be controlled individually. There are LED controllers out there but I want a **wireless** lights controller that conventionally will work with **Vixen Lights**, which is a free software that many people are familiar with.

A couple years ago, I wrote an Instructable about to animate Chirstmas lights with an 8-channel relay, some outlets, and my custom application called "High Tech Christmas 1.0". The lights were manually programmed to work with music but they were not able to change colors or brightness. 

This year, I decided to upgrade that setup to something that feels more modern while enhancing the show. To do that, I wanted a system that cost less than $100 to implement but perform as a far more sophisticated setup than goes beyond entry-level systems found on Amazon.

## Disclaimer ##
The system we are working with will require that you have basic knowledge working with electronics. The author is not responsible and shall not be held liable for any damages or injuries as a result of attempting this project. You agree to perform this project at your own risk.

## Power Supply ##
You will first need to calculate the power supply that you will require. That depends on how many pixels you will power. According to an [article on Adafruit](https://learn.adafruit.com/adafruit-neopixel-uberguide/powering-neopixels), you would use the following example equation:

60 Neopixels × 20 mA ÷ 1,000 = 1.2 Amps minimum

In my case, I am using a 16.4ft reel of Neopixels with 300 pixels. So 300 Neopixels x 20 mA ÷ 1,000 = 6 Amps minimum. Obviously, I will likely have more than one reel of Neopixels, so it would be best for me to choose a power supply 10 Amps or above. With that in mind, it is also important to note that it is not good to turn on **all** the Neopixels unless we are confident that we have sufficient supply of power. Otherwise, it would pose a hazard.

## Materials ##
The following parts are needed:

- [Wemos D1 Mini](https://www.amazon.com/gp/product/B076F52NQD/ref=ppx_yo_dt_b_search_asin_image?ie=UTF8&psc=1) (ESP8266) - $5 ea.
- [Drok 5v Step-Down Regulator](https://www.amazon.com/gp/product/B0758ZTS61/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) - $3 ea.
- [Logic Level Bi-Directional Converter](https://www.sparkfun.com/products/12009) - $3 ea.
- 1000uF Electrolytic Capacitor - $1 ea.
- [25mm 5V Cooling Fan](https://www.amazon.com/WINSINN-Brushless-Cooling-25x10mm-Notebook/dp/B07KRX9F99/) - $2 ea.
- [Outdoor WS2812, 16.4ft, 300 pixel reel](https://www.amazon.com/gp/product/B07BKBN1DQ/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) - $30 ea. (1-4 qty as desired)
- 5V 10A (or 20A) outdoor power supply - $20 ea.
- 3D Printed enclosure (case and plate) - **Files provided** in this repository. Roughly $3 in PLA filament.

Overall, these parts should cost roughly $100 or less. If you buy a larger power supply or more reels of Neopixels, that may increase the cost.

## Supplies/Tools ##
It is not required but highly recommended that you have these tools. It will make the project much easier to accomplish.

- Scissors
- Wire stripper/cutter
- Electrical tape
- Hot glue or UV glue
- Electrical connectors
- Duct tape
- Windows laptop or tablet (with Vixen 3 Lights installed)

## Quick Assembly Instructions ##
1. Order and prepare all the supplies and materials above.
2. Place Wemos D1 Mini into the enclosure **case**.
3. Place the Drok 5v **regulator** into the enclosure.
4. Hot glue or UV glue the 5v cooling **fan** to the enclosure **plate**.
5. Connect the 5v **fan** to the **output** of the Drok 5v regulator. Connect the ground wire as well.
6. Connect the 1000uF cap between the **input** and **ground** of the Drok 5v regulator. Connect those two terminals to the **output connector**.
7. Connect the **logic level converter** to the Wemos D1 data outputs (D5, D6, D7). Don't forget to connect the Gnd and 5v and 3.3v VCC.
8. **Shut the enclosure** and apply UV or hot glue on the edges.
9. Download Arduino v1.8.8 IDE, set the board to NodeMCU 1.0, select COM port, and **upload the code** in this repo. You may need to first download the libraries for ESP8266, E1.31, and Adafruit Neopixels.
10. Open up Vixen, configure, and patch this controller.