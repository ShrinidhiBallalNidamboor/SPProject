cmd_/home/shrinidhi/SPProject/Decrypt/Module.symvers :=  sed 's/ko$$/o/'  /home/shrinidhi/SPProject/Decrypt/modules.order | scripts/mod/modpost -m -a    -o /home/shrinidhi/SPProject/Decrypt/Module.symvers -e -i Module.symvers -T - 