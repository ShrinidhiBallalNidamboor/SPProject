cmd_/home/shrinidhi/MKDIR/Module.symvers :=  sed 's/ko$$/o/'  /home/shrinidhi/MKDIR/modules.order | scripts/mod/modpost -m -a    -o /home/shrinidhi/MKDIR/Module.symvers -e -i Module.symvers -T - 
