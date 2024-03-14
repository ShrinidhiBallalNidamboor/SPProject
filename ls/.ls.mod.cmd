cmd_/home/shrinidhi/SPProject/ls/ls.mod := printf '%s\n'   ls.o | awk '!x[$$0]++ { print("/home/shrinidhi/SPProject/ls/"$$0) }' > /home/shrinidhi/SPProject/ls/ls.mod
