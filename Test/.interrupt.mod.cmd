cmd_/home/shrinidhi/SPProject/Test/interrupt.mod := printf '%s\n'   interrupt.o | awk '!x[$$0]++ { print("/home/shrinidhi/SPProject/Test/"$$0) }' > /home/shrinidhi/SPProject/Test/interrupt.mod
