cmd_/home/shrinidhi/SPProject/TOUCH/touch.mod := printf '%s\n'   touch.o | awk '!x[$$0]++ { print("/home/shrinidhi/SPProject/TOUCH/"$$0) }' > /home/shrinidhi/SPProject/TOUCH/touch.mod
