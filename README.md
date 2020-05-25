# PBM



Installation ESP8266 Python3 Error :
	The problem is that the symlink for python3 is incorrect. To correct it:

	$ cd /Users/[your-username]/Library/Arduino15/packages/esp8266/tools/python3/3.7.2-post1/
	$ rm python3
	$ which python3
	$ ln -s [path-returned-by-the-above-command] python3



# HADWARE

## WARNING IF USING SAME SIDE FCC CABLE
The pinout on the connector side are inverted !!!!