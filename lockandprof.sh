#!/bin/bash

# fixa a frequencia
echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

./profiler.sh

echo "done"

# volta à frequência normal
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
