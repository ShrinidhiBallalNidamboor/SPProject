cmd_/home/shrinidhi/SPProject/Read/Module.symvers :=  sed 's/ko$$/o/'  /home/shrinidhi/SPProject/Read/modules.order | scripts/mod/modpost -m -a    -o /home/shrinidhi/SPProject/Read/Module.symvers -e -i Module.symvers -T - 
