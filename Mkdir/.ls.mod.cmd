cmd_/home/shrinidhi/CP/ls.mod := printf '%s\n'   ls.o | awk '!x[$$0]++ { print("/home/shrinidhi/CP/"$$0) }' > /home/shrinidhi/CP/ls.mod
