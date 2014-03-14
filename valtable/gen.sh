#!/bin/bash

FILE=val_table.inc

MIN_VALUE=128
CONVERTER=60000000
DIMENSION=100

MAX_SPEED=$(($CONVERTER / $MIN_VALUE))
SPEED_STEP=$(($MAX_SPEED / $DIMENSION))

echo "static uint16_t val_table[] = {" > $FILE

for i in `seq $SPEED_STEP $SPEED_STEP $MAX_SPEED`;
do
        echo -e "\t" $((60000000 / $i + 16))"," >> $FILE
done

echo "};" >> $FILE

echo $(($MIN_VALUE + 5))
