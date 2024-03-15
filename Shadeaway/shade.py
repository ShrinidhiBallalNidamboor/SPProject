import os
with open("Shadeaway/text.txt", "r") as file:
	name=file.read().split('\n')
	for i in name[:-1]:
		try:
			os.remove(i)
		except:
			print("",end="")
with open("Shadeaway/text.txt", "w") as file:
	file.write('')
