cmd_/home/shrinidhi/SPProject/Mkdir/mkdir.mod := printf '%s\n'   mkdir.o | awk '!x[$$0]++ { print("/home/shrinidhi/SPProject/Mkdir/"$$0) }' > /home/shrinidhi/SPProject/Mkdir/mkdir.mod
