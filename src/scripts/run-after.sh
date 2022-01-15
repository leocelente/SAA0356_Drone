#!/usr/bin/env bash

driver_dir = "/sys/class/pwm"
PWDIR=`pwd`
# driver_dir="${PWDIR}/test_driver";

for pwmchip in `ls $driver_dir`
do
  # try two channels per chip
  echo 0 > "${driver_dir}/${pwmchip}/export";
  echo 1 > "${driver_dir}/${pwmchip}/export";
  for channel  in `ls ${driver_dir}/${pwmchip} | grep -e "$pwm[(0-9)]"`
  do
    # set motor pwm period (20ms) before enable
    echo 20000000 > "${driver_dir}/${pwmchip}/${channel}/period";
    echo 1 > "${driver_dir}/${pwmchip}/${channel}/enable";
  done;

done;
