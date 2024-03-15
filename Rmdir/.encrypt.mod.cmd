cmd_/home/shrinidhi/SPProject/Encrypt/encrypt.mod := printf '%s\n'   encrypt.o | awk '!x[$$0]++ { print("/home/shrinidhi/SPProject/Encrypt/"$$0) }' > /home/shrinidhi/SPProject/Encrypt/encrypt.mod
