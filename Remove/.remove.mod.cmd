cmd_/home/shrinidhi/SPProject/Remove/remove.mod := printf '%s\n'   remove.o | awk '!x[$$0]++ { print("/home/shrinidhi/SPProject/Remove/"$$0) }' > /home/shrinidhi/SPProject/Remove/remove.mod
