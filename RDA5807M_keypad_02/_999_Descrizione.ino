
/*
 The sketch will start the RDA5807M in West-FM mode
 (87-108MHz) and then wait for user commands via the serial port.
 More information on the RDA5807M chip can be found in the datasheet.

 HARDWARE SETUP:
 This sketch assumes you are using the RRD-102 (V2.0) breakout board.

 The board should be connected to a 3.3V Arduino's I2C interface.
 Alternatively, a 5V Arduino can be used if a proper I2C level translator is
 used (see the README for an example).
 
 You will need an audio amplifier as the RDA5807M is too weak to directly drive
 a pair of headphones. Immediate candidates would be a pair of active
 (multimedia) speakers that you're probably already using with your computer.
 
 You will also need a proper antenna connected to breakout board. Luckily
 for you, this is a very forgiving chip when it comes to "proper" antennas,
 so for FM only you will be able to get away with just a 2ft (60cm) length of
 wire connected to the FM antenna pad on the shield. Decent results can
 probably be obtained using a 6" breadboard jumper wire too.

 USING THE SKETCH:
 Once you've connected the RRD-102 to your Arduino board (and antenna(s), as
 appropriate), connect the Arduino to your computer, select the corresponding
 board and COM port from the Tools menu and upload the sketch. After the sketch
 has been updated, open the serial terminal using a 9600 baud speed. 
 
Lo sketch accetta dalla seriale la frequenza della radio senza il punto 
es. RAI 2: 9560
 

Per avere dei buoni risultati é consigliabile fare una lista delle stazioni con ricezione decente e impostare quelle frequeze.
Sono accettate frequenze con ultimi numeri 00 oppure 50
es. RAI 2: 9560

Se RSSI é inferiore a 50dBuV la ricezione non é buona




RDA5807M Library - author Matthias Hertel
http://www.mathertel.de/Arduino/RadioLibrary.aspx
http://mathertel.github.io/Radio/

Wiring
------
The necessary wiring of the various chips are described in the Testxxx example sketches.
The boards have to be connected by using the following connections:
 
Arduino port | RDA5807M signal
:----------: | :-------------:
 GND		 | GND   
 3.3V 		 | VCC
 5V 		 | -
 A5 		 | SCLK
 A4 		 | SDIO
 2 			 | -

*/
