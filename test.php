<?php
dl("locktools.so");
sleep(1);

EasySys\LockTools::run('tmp1',function(){
    sleep(2000);
    echo "ok is running\n";
    return [1,2];
},10);
echo "finished";
