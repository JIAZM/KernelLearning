cmd_/home/thirty/code/kernellearn/irq/up/modules.order := {   echo /home/thirty/code/kernellearn/irq/up/interrupt.ko; :; } | awk '!x[$$0]++' - > /home/thirty/code/kernellearn/irq/up/modules.order
