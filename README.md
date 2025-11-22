## How did I do to make AS5600 work:

1. Soldered all the connections from Blue pill with AS5600.
2. Installed the board in Arduino IDE.
3. Select Fake board and COM9 as port.
4. Installed AS5600 lib by Rob Tilaart from Library manager.
5. Executed the current code
6. Set BOOT0(second one behind the reset button. not the first one) to 1.
7. From ***Tools*** option in the top of IDE, you should select upload method to serial since we’re using FT232. 
8. Hit upload button and check serial monitor option in Tools option at the top. 
9. Once you rotate the magnets, you should see differentiating values.

## How did I actually made it to work in sim racing(F1 25):
1. Once flashed, remove TTL adapter from blue pill. It’s just used for flashing the code.
2. Then connect the blue pill to computer. 
3. In windows, search for `Game controller` and enter the first one which starts with set up game controller.
4. If correctly loaded you should see something named 'Maple' in it and select that and select properties below
5. After clicking properties, window will open up. Use the magnet and check if the rotation is proper. The + symbol should move.
6. 1. Open a game, set the control. When to steer left, rotate the magnet left and to steer right control, rotate to right. And that’s it. 
7. Try the game. It should work!
