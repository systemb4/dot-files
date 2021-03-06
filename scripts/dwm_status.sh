#!/bin/sh
# dwm status using xset root

printIp() {
    echo "$(ip route get 8.8.8.8 2>/dev/null | grep -Eo 'src [0-9.]+' | grep -Eo '[0-9.]+')"
}

printMemory() {
    echo "(mem)$(($(grep -m1 'MemAvailable:' /proc/meminfo | awk '{print $2}') / 1024))"
}

printDisk() {
    echo "(hd)$(df -h / | awk '{print $3}' | sed -n '1!p')"
}

print_caps() {
    echo "Caps: $(xset -q | grep Caps | awk '{ print $4 }')"
}

printTime() {
    echo "$(date +"%a, %D %I:%M:%S %p")"
}

printBacklight() {
    echo "(bl)$(xbacklight -get | sed 's/\.[0-9]*//' | sed 's/$/%/')"
}

printBattery() {
    bat0=$(cat /sys/class/power_supply/BAT0/status)
    batstat0=$(echo "(i)$(cat /sys/class/power_supply/BAT0/capacity | sed 's/$/%/')")
    
    bat1=$(cat /sys/class/power_supply/BAT1/status)
    batstat1=$(echo "$(cat /sys/class/power_supply/BAT1/capacity | sed 's/$/%/'| sed 's/^/(e)/')")
    
    case $bat0 in
        Full)
            bat0=$(echo "T")
            ;;
        Unknown)
            bat0=$(echo "T")
            ;;
        Discharging)
            bat0=$(echo "D")
            ;;
        Charging)
            bat0=$(echo "C")
            ;;
    esac
                                                                                                                    
    case $bat1 in
        Full)
            bat1=$()
            ;;
        Unknown)
            bat1=$(echo "T")
            ;;
        Discharging)
            bat1=$(echo "D")
            ;;
        Charging)
            bat1=$(echo "C")
            ;;
    esac
                                                                                                                                                                                                                                   
    echo "$batstat0$bat0$batstat1$bat1"
}

printCputmp() {
    test -f /sys/class/thermal/thermal_zone0/temp || return 0
    echo "(cpu)$(head -c 2 /sys/class/thermal/thermal_zone0/temp)C"
    #sensors | awk '/^Package id/ { print $4 }' | sed -e 's/+//' -e 's/C//' -e 's/°//' -e 's/.$//' -e 's/.$//' >> ~/tempsLog.txt
    #echo "(cpu)$(sensors | awk '/^Package id/ { print $4 }')"
}

printVolume() {
    # output script
    output=$(amixer sget Master | grep 'Right:' | awk -F'[][]' '{ print $4 }')
    input=$(amixer sget Capture | grep 'Left:' | awk -F '[][]' '{ print $4 }')
    if [[ $output = "on" ]]; then
        output=$(echo "(vol)$(amixer sget Master | grep 'Right:' | awk -F '[][]' '{ print $2, $4 }')")
        input=$(echo "$(amixer sget Capture | grep 'Left:' | awk -F '[][]' '{ print $4 }')")
    else
        output=$(echo "(vol)$(amixer sget Master | grep 'Right:' | awk -F '[][]' '{ print $4 }')")
        fi
    echo "$output $input"
}

printNetwork() {
    logfile=/dev/shm/netlog
    [ -f "$logfile" ] || echo "0 0" > "$logfile"
    read -r rxprev txprev < "$logfile"
    rxcurrent="$(($(paste -d '+' /sys/class/net/[ew]*/statistics/rx_bytes)))"
    txcurrent="$(($(paste -d '+' /sys/class/net/[ew]*/statistics/tx_bytes)))"
    echo "$(bc <<< "scale=2; ($rxcurrent-$rxprev) / 10^6")" "$(bc <<< "scale=2; ($txcurrent-$txprev) / 10^6")"
    echo "$rxcurrent $txcurrent" > "$logfile"
}

while true
do
    xsetroot -name "$(printVolume)$(printBacklight)$(printBattery)$(printDisk)$(printCputmp) $(printIp) $(printTime)"
    sleep 1
done
