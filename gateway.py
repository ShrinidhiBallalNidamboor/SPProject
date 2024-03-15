import os

print("Commands:")
print("1.  Copy file from one to other (copy from=from_path to=to_path)")
print("2.  Encrypt file (encrypt filepath=path encryption_key=key)")
print("3.  Decrypt file (decrypt filepath=path encryption_key=key)")
print("4.  List files in a directory (list directory=path)")
print("5.  Present working directory (pwd)")
print("6.  Read file (read filepath=path)")
print("7.  Create file (touch filename=path)")
print("8.  Remove file (remove filename=path)")
print("9.  Make folder (mkdir directory=path)")
print("10. Remove folder (rmdir directory=path)")
print("11. Edit file (open file_path)")
print("12.  Exit (exit)")

hashing={}
hashing["copy"]=["sudo insmod CP/cp.ko", "sudo rmmod CP/cp.ko"]
hashing["encrypt"]=["sudo insmod Encrypt/encrypt.ko", "sudo rmmod Encrypt/encrypt.ko"]
hashing["decrypt"]=["sudo insmod Decrypt/decrypt.ko", "sudo rmmod Decrypt/decrypt.ko"]
hashing["list"]=["sudo insmod ls/ls.ko", "sudo rmmod ls/ls.ko"]
hashing["pwd"]=["sudo insmod pwd/pwd.ko", "sudo rmmod pwd/pwd.ko"]
hashing["read"]=["sudo insmod Read/read.ko", "sudo rmmod Read/read.ko"]
hashing["touch"]=["sudo insmod TOUCH/touch.ko", "sudo rmmod TOUCH/touch.ko"]
hashing["remove"]=["sudo insmod Remove/remove.ko", "sudo rmmod Remove/remove.ko\npython3 Remove/remove.py"]
hashing["mkdir"]=["sudo insmod Mkdir/mkdir.ko", "sudo rmmod Mkdir/mkdir.ko\npython3 Mkdir/mkdir.py"]
hashing["rmdir"]=["sudo insmod Rmdir/rmdir.ko", "sudo rmmod Rmdir/rmdir.ko\npython3 Rmdir/rmdir.py"]
hashing["open"]=["./editor", ""]

while True:
	cmd=input("Input command: ")
	if cmd=="exit":
		break	
	try:
		result=cmd.split(" ")
		if result[0]=="open":
			with open(result[1], "r") as fd:
				text=fd.read()
				with open("editor.txt", "w") as fd:
					fd.write(text)
		cmd1=hashing[result[0]][0]+" "+" ".join(result[1:])
		cmd2=hashing[result[0]][1]
		os.system(cmd1)
		os.system(cmd2)
		if result[0]=="open":
			cmd1="sudo insmod CP/cp.ko from=editor.txt "+"to="+result[1]
			cmd2="sudo rmmod CP/cp.ko"
			os.system(cmd1)
			os.system(cmd2)
	except:
		print("Incorrect command")
