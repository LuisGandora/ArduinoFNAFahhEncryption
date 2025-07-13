Welcome to my Arduino/AWS/PythonProject

The main goal is to set a link of arduino based actions to AWS buckets to access information from their. This project simulates a video games, with the arduino functioning as a game console and the AWS site functioning as a cloud.
In order to beat the game, the player 'P' has to get to the goal '1' in order to beat the game. The player cant move past 'H' and 'N'. Hint: '0' is a key.
The player can move in all directions via a standard issue arduino remote using vol+, vol-, fast forward and rewind.
Upon touching the 1, the python script will push the scores to the AWS bucket using a combination of Boto3 and enviornment keys.
The person that completes the board with the least amount of moves wins.


This project uses the followin


Project Duration 7/9-7/13 Cause I procastinated
