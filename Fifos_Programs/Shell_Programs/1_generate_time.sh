#Program to generate the time and date
#!/bin/sh
while true :
do
    rm -f ./time_fifo
    #create a fifo in current directory
    mkfifo ./time_fifo
    sleep 1
    date > ./time_fifo
done

