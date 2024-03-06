cmd_/home/shrinidhi/LS/ls.mod := printf '%s\n'   ls.o | awk '!x[$$0]++ { print("/home/shrinidhi/LS/"$$0) }' > /home/shrinidhi/LS/ls.mod
