cmd_/home/shrinidhi/LS/Module.symvers :=  sed 's/ko$$/o/'  /home/shrinidhi/LS/modules.order | scripts/mod/modpost -m -a    -o /home/shrinidhi/LS/Module.symvers -e -i Module.symvers -T - 
