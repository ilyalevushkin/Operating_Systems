make
echo
sleep 0.8

# Загрузим модули ядра 
echo ">>>>> Loading tasklet.ko..."
insmod tasklet.ko irq=12

# Выведем список загружен модулей ядра, чье название содержит строку «tasklet» 
lsmod | grep tasklet
echo
sleep 1

# Посмотрим последние 15 сообщений, выведенных модулями ядра
echo ">>>>> This is the last 15 lines in the system log: "
dmesg | tail -15
echo
read -n 1 -s -r -p "Press any key to continue..."
echo

# Выгрузим модуль ядра 
echo ">>>>> Remove tasklet.ko..."
rmmod tasklet
echo
sleep 0.8

# Посмотрим последние 5 сообщений, выведенных модулями ядра
dmesg | tail -5