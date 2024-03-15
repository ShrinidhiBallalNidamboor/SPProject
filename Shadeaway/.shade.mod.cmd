cmd_/home/shrinidhi/SPProject/Shadeaway/shade.mod := printf '%s\n'   shade.o | awk '!x[$$0]++ { print("/home/shrinidhi/SPProject/Shadeaway/"$$0) }' > /home/shrinidhi/SPProject/Shadeaway/shade.mod
