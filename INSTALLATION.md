# Getting setup

##Windows

 1. First, go to the [IEEE UH webpage](http://www.ieeeuh.org/3pi-quick-start-guide/).
 2. Go to the [Pololu AVR Quick Start guide](https://www.pololu.com/docs/0J51). It's for the Orangutang, but the instructions still apply for the 3p1.
 3. [Download the Atmel studio6](http://www.atmel.com/images/AStudio6_2sp2_1563.exe).
 4. [Download the bundle of drivers and other stuff](https://www.pololu.com/file/0J541/pololu-avr-bundle.exe).
 5. Install the Atmel Studio first, then the bundle
	 1. It's going to ask you to install a lot of different things
 6. Once it's done installing, open the Device Manager from the Start Menu and plug in the programmer and wait for the page to refresh
 7. Under the Ports menu, find the COM port number of the `Pololu AVR Programmer PRogramming Port`
	 1. Usually will be COM3
 8.  Start up Atmel Studio, and go to the Tools menu, and `Add Target..`
 9. Start a `New Project..`, and got to the `Pololu` sub-menu from the `C/C++` menu
 10. Pick the 3pi with ATMega328P
 11. Connect the programmer to the 3pi
 12. Build --> Build Solution
 13. Debug --> Start without debugging