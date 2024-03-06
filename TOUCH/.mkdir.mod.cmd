cmd_/home/shrinidhi/MKDIR/mkdir.mod := printf '%s\n'   mkdir.o | awk '!x[$$0]++ { print("/home/shrinidhi/MKDIR/"$$0) }' > /home/shrinidhi/MKDIR/mkdir.mod
