cmd_/home/shrinidhi/SPProject/Read/read.mod := printf '%s\n'   read.o | awk '!x[$$0]++ { print("/home/shrinidhi/SPProject/Read/"$$0) }' > /home/shrinidhi/SPProject/Read/read.mod
