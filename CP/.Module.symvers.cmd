cmd_/home/shrinidhi/CP/Module.symvers :=  sed 's/ko$$/o/'  /home/shrinidhi/CP/modules.order | scripts/mod/modpost -m -a    -o /home/shrinidhi/CP/Module.symvers -e -i Module.symvers -T - 
