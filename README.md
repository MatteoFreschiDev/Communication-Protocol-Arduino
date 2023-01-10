# Arduino nRF24L01 module example code

(Primary source: https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/ )

First of all, it's suggested to verify that the IDE can correctly upload code to the arduino board; the Examples > 01.Basics > Blink is a good choice for doing that, as it needs only the built in LED to function and its functionality can be verified visually.

Verified that, both arduino boards can be connected to the modules according to the diagram you can find in "connection_diagram.png".

The last thing needed to use the code is to install, from the IDE manage libraries util, the RF24 by TMRh20 library.

Explanations as to the functionality of the code used can be found in the comments of the code itself.

## Minimal code

The folders "receiver_minimal" and "transmitter_minimal" contain code, meant to work together to verify the minimal functionality of the boards, by transmitting from one board to the other a short character string.

## Example code

To more closely resemble the code that will be needed for the project, the folders "receiver_example" and "transmitter_example" contain code that uses the boards to transmit and receive multiple (two) integer values.
