cmd_/home/shrinidhi/CP/cp.mod := printf '%s\n'   cp.o | awk '!x[$$0]++ { print("/home/shrinidhi/CP/"$$0) }' > /home/shrinidhi/CP/cp.mod
