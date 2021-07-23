#!/bin/bash


find FreeRTOS -name "*.c" -exec echo "add_sw_property c_source " {} \; > gen.txt
find FreeRTOS -name "*.h" -exec echo "add_sw_property include_source " {} \; >> gen.txt

