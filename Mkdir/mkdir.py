import os
with open("Mkdir/text.txt", "r") as file:
	name=file.read().split('\n')[0]
	os.mkdir(name)
