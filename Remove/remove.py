import os
with open("Remove/text.txt", "r") as file:
	name=file.read().split('\n')[0]
	try:
		os.remove(name)
	except:
		print("No file exists")
