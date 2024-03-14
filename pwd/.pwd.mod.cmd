cmd_/home/shrinidhi/SPProject/pwd/pwd.mod := printf '%s\n'   pwd.o | awk '!x[$$0]++ { print("/home/shrinidhi/SPProject/pwd/"$$0) }' > /home/shrinidhi/SPProject/pwd/pwd.mod
