# Hardware - Pro Micro

This section covers the required hardware for users who have chosen the Pro Micro board.

This board is significantly harder to use than the Teensys. But is cheap in bulk and is best suited for farms of multiple Switches running PABotBase where they rarely need to be reprogrammed.

There are 3 levels of hardware setups here. How far you get into this tutorial will depend on which level you wish to achieve.

1. **Basic Programs:** No computer control. No feedback. ([Basic Hardware](#basic-hardware) only)
2. **Serial Programs:** Computer control. No feedback. ([Basic Hardware](#basic-hardware) + [Serial Hardware](#serial-hardware))
3. **Full Feedback:** Computer control with video feedback. (everything in this tutorial - all the way to the end)

# Basic Hardware:

The basic Pro Micro hardware setup will look like this:

<img src="images/pro-micro-basic.jpg" height="400">

**Required Hardware:**

1. [Pro Micro Board](https://www.amazon.com/gp/product/B08BJNV1J3)
2. Micro-USB male to USB-A male cable or adapter. ([example](https://www.amazon.com/gp/product/B081HDS3WB))

***Adapters*** for Micro-USB male to USB-A male are notoriously difficult to find in quantity.
Cables are easy to find, but less convenient if you just want to plug them into the standing Switch dock.

The adapter linked above is one Micro-USB and one Mini-USB. The Mini-USB isn't useful for the Pro Micro, but is useful for Teensy if you also have those.

<img src="images/pro-micro.jpg" height="200"> <img src="images/usb-a-to-usb-micro.jpg" height="200">

**Switch Lite users will also need:**

1. A USB hub or portable dock. ([example](https://www.amazon.com/gp/product/B07JK9DFKH))

The Switch Lite does not have a USB-A port. Therefore you need either an adapter or a hub to connect the Teensy. A charging hub or dock is required to simultaneously charge and use the Teensy.

Portable docks will work for the Switch Lite. It will just not be able to output video over the HDMI.

**Optional Hardware:**

If you will be using the [FastCodeEntry](../Programs/FastCodeEntry.md) program or if you are a heavy user in general, then it is strongly recommended to get a USB-A male-to-female cable with a power switch on it. ([example](https://www.amazon.com/gp/product/B07T9BRNHW))

If you intend to change programs very often and will be running the Switch next to a computer, then you will want a USB switch. ([example](https://www.amazon.com/gp/product/B006Z0Q2SI)) These are like USB-only KVM switches. In fact a regular KVM switch will also work. With this, you no longer have to constantly plug/unplug USBs which will eventually wear them down.

# Serial Hardware:

To use any of the serial or feedback programs, you will need additional hardware.

There are many ways to set this up with varying cost and difficulty. Here we will present some simple options that do not require soldering. If you are experienced with electronics, feel free to do your own thing.

## Option 1: UART Cable + Mini-Grabber Cables

This option is the easiest to setup, however the mini grabber cables that are needed are rarely in stock.

<img src="images/serial-pro-micro-mg.jpg" height="400">

**Required Hardware:**
1. Everything from the [previous section](#basic-hardware).
2. A [USB-to-TTL UART cable or board](https://www.adafruit.com/product/954). It is recommended to get one with the CP210x controller. Avoid the ones with PLxxxx controllers since many of them are knock-offs that do not work.
3. [Mini grabber to jumper wires (male).](https://www.amazon.com/gp/product/B08M5GNY47) You want the one with ***male*** jumper wires.

<img src="images/uart-adafruit.jpg" height="200"> <img src="images/mini-grabber.jpg" height="200">

**Hardware Setup:**

Once you have your hardware, you need to make some connections.

Make the following connections:
- UART cable green (TX) to Pro Micro RX1
- UART cable white (RX) to Pro Micro TX0
- UART cable black (GND) to Pro Micro GND (any one is fine)
- UART cable red (VCC) – leave unconnected

Note that the mini grabber clips may not fit through the holes on the Pro Micro. This is fine.

<img src="images/serial-pro-micro-mg-0.jpg" height="200"> <img src="images/serial-pro-micro-mg-1.jpg" height="200">

## Option 2: UART Cable + Solderless Hammer Headers

This option is cleaner, but is more involved.

<img src="images/pro-micro-hammer-0.jpg" height="400">

**Required Hardware:**
1. Everything from the [previous section](#basic-hardware).
2. A [USB-to-TTL UART cable or board](https://www.adafruit.com/product/954). It is recommended to get one with the CP210x controller. Avoid the ones with PLxxxx controllers since many of them are knock-offs that do not work.
3. [Solderless Hammer Headers](https://www.adafruit.com/product/3662)
4. A box cutter or a wire cutter.
5. Pliers. (you will likely need two of them)

**Hardware Setup:**

1. Use your box cutter or wire cutter to cut out 2 pairs of pins from the strip of solderless headers. ***Be very careful not to cut yourself.***
2. Insert a pair of hammer headers into the TX and RX holes on the Pro Micro.
3. Insert a hammer header into the GND hole on the Pro Micro. (Since you can't easily split the pair of pins, you can do GND and the pin adjacent to it.)

<img src="images/pro-micro-hammers-0.jpg" height="200"> <img src="images/pro-micro-hammers-1.jpg" height="200">

You will need a LOT of force to push the hammer headers into the holes. Recommend using pliers to pull the pins out of the plastic holds and inserting the long side into the Pro Micro. Then put the covers back on and use pliers to squeeze it in.

Now that the pins are setup, you can make the connections.
- UART cable green (TX) to Pro Micro RX1
- UART cable white (RX) to Pro Micro TX0
- UART cable black (GND) to Pro Micro GND (any one is fine)
- UART cable red (VCC) – leave unconnected

<img src="images/pro-micro-hammer-1.jpg" height="400">

## Bulk Alternatives to UART Cable

The Adafruit UART cable is reliable and beginner-friendly, but it is also quite expensive. If you are experienced (or confident), here are some cheaper alternatives which also work. These may require a trivial amount of extra wiring.
- https://www.amazon.com/gp/product/B07T1XR9FT (4 for $8)
- https://www.amazon.com/gp/product/B07D6LLX19/ (2 for $8)
- https://www.amazon.com/dp/B072K3Z3TL (1 for $8)

These red CP210x boards seem to be the most popular in our server due to their cost.

<img src="images/uart-red-cp210x.jpg" height="400">

<img src="images/pro-micro-red-uart.jpg" height="400">


# Video Hardware:

Main Section: [Video Hardware](Hardware-Video.md)



