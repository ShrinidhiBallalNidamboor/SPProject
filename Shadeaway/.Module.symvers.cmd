cmd_/home/shrinidhi/SPProject/Shadeaway/Module.symvers :=  sed 's/ko$$/o/'  /home/shrinidhi/SPProject/Shadeaway/modules.order | scripts/mod/modpost -m -a    -o /home/shrinidhi/SPProject/Shadeaway/Module.symvers -e -i Module.symvers -T - 