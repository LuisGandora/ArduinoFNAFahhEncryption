Welcome to my Arduino/AWS/PythonProject

The main goal is to set a link of arduino based actions to AWS buckets to access information from their. This project simulates a video games, with the arduino functioning as a game console and the AWS site functioning as a cloud.
In order to beat the game, the player 'P' has to get to the goal '1' in order to beat the game. The player cant move past 'H' and 'N'. Hint: '0' is a key.
The player can move in all directions via a standard issue arduino remote using vol+, vol-, fast forward and rewind.
Upon touching the 1, the python script will push the scores to the AWS bucket using a combination of Boto3 and enviornment keys.
The person that completes the board with the least amount of moves wins.

Tinkercad: https://www.tinkercad.com/things/cayOyoAh9bY/editel?returnTo=%2Fdashboard&sharecode=JiIgYHxFt7hoaqaEzbTQxm5b_o6mU8z7bm4tx0FIfTk

Materials:
-Arduino Elegoo
-Alot of wires
-The standard Elegoo controller
-More wires
-IR sensor
-Poteniometer
-One resistor
-The LCD1602
-Even More wires
-Computer
-Access to wifi (Not mcdonalds)

Packages:
-Python 3.10+ I think?
-Arduino.ide
-Boto3
-IRremote
-LiquidCrystal

AWS acccount:
-An aws account with at least s3 level access

Setup:
1. Build the board according to tinkercad specs
2. Pull this project
3. Open up the TestwithScreen.ino file using Arduino.ide
4. If not setup already, go into Arduino.ide and in /Tools/Manage Libraries, search and install IRremote and LiquidCrystal
5. Upload to the board, if you get errors you may need to fix the permissions in your board port
6. Open the python script using your code editor of choice, Close Arduino.ide
7. Use these commands to set up AWS to connect to your AWS account of choice:
           .export AWS_ACESSKEY_ID = your_access_key
           .export AWS_SECRET_ACCESS_KEY = your_secret_key
           .export region = region_in_your_account
9. Run the program in your arduino board and in your code editor run the script
10. You should be able to see that in your code editor terminal that upon completion, your high score will be uploaded to your bucket of choice

Specs:
-1 GB at the very least

Perferred Specs:
-999GB worth of space


This project uses the following:
-Arduino
-Tinkercad
-Python
-Mainly VsCode for testing

Shoutout to Gabriel for the help


Project Duration 7/9-7/13 Cause I procastinated
