import os
with open("Rmdir/text.txt", "r") as file:
	name=file.read().split('\n')[0]
	try:
		os.rmdir(name)
	except:
		print("No folder exists")
