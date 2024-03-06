cmd_/home/shrinidhi/SPProject/Decrypt/decrypt.mod := printf '%s\n'   decrypt.o | awk '!x[$$0]++ { print("/home/shrinidhi/SPProject/Decrypt/"$$0) }' > /home/shrinidhi/SPProject/Decrypt/decrypt.mod
