#!/bin/sh

PWDIR=`pwd`
# driver_dir = "/sys/class/pwm"
driver_dir="${PWDIR}/test_driver";

for pwmchip in `ls $driver_dir`
do
  
  echo 1 > "${driver_dir}/${pwmchip}/export";
  echo 2 > "${driver_dir}/${pwmchip}/export";
  for channel  in `ls ${driver_dir}/${pwmchip} | grep pwm`
  do
    echo 1 > "${driver_dir}/${pwmchip}/${channel}/enable";
  done;
  
done;
