cmd_/home/shrinidhi/SPProject/Rmdir/rmdir.mod := printf '%s\n'   rmdir.o | awk '!x[$$0]++ { print("/home/shrinidhi/SPProject/Rmdir/"$$0) }' > /home/shrinidhi/SPProject/Rmdir/rmdir.mod
