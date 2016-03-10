На моём ноутбуке два ядра с HyperThreading.

Вывод запуска скрипта `run.sh`.

```$ ./run.sh
+ g++ -Wall -std=c++11 -O2 -pthread futex.cpp -o futex
+ g++ -Wall -std=c++11 -O2 -pthread mutex.cpp -o mutex
+ ./futex 4
thread 0: 281907250
thread 1: 277734216
thread 2: 320074970
thread 3: 320283564
1200000000

real    1m2.695s
user    2m8.132s
sys     1m57.048s
+ ./mutex 4
thread 0: 300755533
thread 1: 297933240
thread 2: 301069697
thread 3: 300241530
1200000000

real    2m22.556s
user    2m32.612s
sys     5m54.124s
+ ./futex 2
thread 0: 860590988
thread 1: 339409012
1200000000

real    0m39.494s
user    0m58.012s
sys     0m21.012s
+ ./mutex 2
thread 0: 594238886
thread 1: 605761114
1200000000

real    3m9.206s
user    3m29.824s
sys     2m48.548s
+ ./futex 8
thread 0: 144052197
thread 1: 150024296
thread 2: 146408804
thread 3: 147523419
thread 4: 160227792
thread 5: 151956954
thread 6: 154141498
thread 7: 145665040
1200000000

real    0m40.099s
user    1m1.280s
sys     1m35.844s
+ ./mutex 8
thread 0: 149814594
thread 1: 149767363
thread 2: 149569958
thread 3: 149848898
thread 4: 149359465
thread 5: 151342342
thread 6: 150123786
thread 7: 150173594
1200000000

real    2m35.420s
user    2m19.424s
sys     7m14.672s
```

Можно видеть, futex работает быстрей, чем mutex. Причём mutex исполняется в режиме ядра больше времени, чем futex.

При исполнении на двух ядрах время меньше, чем при исполнении на четырёх, что логично, ибо HT.

Интересно, что версия futex на четырёх ядрах медленней версии на восьми ядрах. Скорее всего это связано с остановкой потока при неудачной попытке занять futex (команда yield) и особенностями планировщика.