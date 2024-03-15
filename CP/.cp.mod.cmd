cmd_/home/shrinidhi/SPProject/CP/cp.mod := printf '%s\n'   cp.o | awk '!x[$$0]++ { print("/home/shrinidhi/SPProject/CP/"$$0) }' > /home/shrinidhi/SPProject/CP/cp.mod
