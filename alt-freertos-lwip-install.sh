#!/bin/bash
read -p "altera path: [/opt/altera/12.0] " ALT_PATH;
M_INST=`pwd`;
if ! ls "${ALT_PATH}" > /dev/null >2 /dev/null; then
    echo "Error: No altera directory found!";
    exit 1;
fi
echo "Launching the Nios II Command Shell, please standby....";
# launce Nios command shell
"${ALT_PATH}/nios2eds/nios2_command_shell.sh" "${M_INST}/alt-freertos-lwip-do-install.sh" "${ALT_PATH}" "${M_INST}"
