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
10. Open up Vixen, configure, and patch this controller. Follow Vixen instructions as needed.

## Vixen Setup ##
Vixen Lights is a fantastic free software that can control Neopixels, DMX lights, and more. In our case, we will have to configure Vixen to recognize our hardware configuration. Although there are tutorial videos out there for Vixen, **your E1.31 configuration may be unique** depending on the number of reels and length of your pixels. This guide will show you how to calculate and set up your configuration.

According to an [article](http://www.vixenlights.com/vixen-3-documentation/setup-configuration/sacn-output/) on Vixen: In DMX, only 512 channels of data could be carried on a DMX cable.  This was a limit based on the balance of data rate, distance requirements, multidrop topology and refresh rate.  With all of those factors considered, 512 channels was defined as the standard number of channels in a universe.  As shows grew, and designers needed more than 512 channels to control a show, it became necessary to implement multiple independent DMX networks.  While not part of the standard, the term “universe” became the standard term to refer to each separate DMX network. In the DMX world, every group of 512 channels was its own physical network and this network was called a universe.

A "universe" by no means is equivalent to a reel/strand of lights. It is not equivalent to any specific decoration either. A universe is just a fragment (aka chunk) of your lights show that comprises of channels that go up to 512. If your lights show is below that number, then you don't have to worry about configuration. If you go over that, you will have to do some calculations.

Despite our wireless approach, each universe is still bound by the 512 channel convention. Each Neopixel consumes 3 "channels", one for red, green, and blue. If you divide 512 by 3, you would understand that we can control a maximum for 170 Neopixels in a universe. Nowadays, a reel of 16.4ft Neopixels contain 300 pixels. In other words, 300 pixels X 3 = 900 outputs. These 900 outputs cannot fix in a single DMX universe since it exceeds 510. You will need to add an extra universe for the overflowed amount.

In our **current setup**, we have 2 reels (each with 300 Neopixels) and 1 strand of 50 Neopixels. So that gives us a total of 650 Neopixels. We want to organize these into universes that would allow us to easily patch them into "elements" for the display.

### Hardware Setup Summary ###

**Reel A (300 pixels):** <br />
170 pixels in universe A (510) <br />
Start 1 <br />
130 pixels in universe B (390) <br />
Start 511

**Reel B (300 pixels):** <br />
170 pixels in universe C (510) <br />
Start 901 <br />
130 pixels in universe D (390) <br />
Start 1411

**Strand C (50 pixels):** <br />
50 pixels in universe E (150) <br />
Start 1801

Each universe must start at channel 1. The channels are **relative** to their own universes.

### Vixen Configuration ###
1. Install Vixen 3.7 or latest version.
2. Click **Setup Display**.
3. On the top-right corner, select **Streaming ACN (E1.32)** from the dropdown list. Click the "Add" button.
4. Give your controller a name. In this case, I have named it *BunnyPixel (E1.31)*. Right-click on it and select **Configure**.
5. Enter the values as shown in the Hardware Setup Summary. If your hardware is different, ensure that the pixels are calculated properly.
6. Select the "Destination" and enter the IP address of your Neopixel controller.
7. On the top-left corner, select **Generic Numbered Group** from the dropdown list. Click the "Add" button. If your reel of lights is for the roof, name it "Roof Lights" with a prefix of "roof". Be creative and meaningful with these names since it will help later.
8. Keep performing step 7 until you have added all your light reels and strands as "Elements".
9. Select the Element you want to assign to the universe. This is known as "patching". In other words, select all the items in "Roof Lights" and then select the items on the right-side Controller that you want to map them to.
10. Click the Patch Elements button.
11. The WS2812 16.4ft 300 pixel reels I have use a "GRB" profile instead of an RGB convention. The WS2811 strand of 50 pixels use the typical RGB convention. You don't really need a dimming profile unless desired.
12. Click "Save" and close the window.
13. Click **Setup Previews** and give a name to your default preview.
14. Click the "Background" button and select an image of your house. Adjust the opacity slider to around 50-60% to emulate a dark environment.
15. Select the "smart shapes" multi-line tool, draw the outline of your lights on your house. Hit "Escape" once you are done. The lights may appear unevenly distributed.
16. Click the **Pointer Select** button on the menu. Click on the line that you want to associate with an Element.
17. You will see the properties box show details. You can change the size of the lights radius as well as changing the distribution of lights per string.
18. Map the distribution of Elements per string. Save and exit.

Now you are ready to sequence some songs!