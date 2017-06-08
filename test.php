<?php
sleep(1);

EasySys\LockTools::run('tmp3',function(){
    sleep(200);
    echo "ok is running\n";
    return [1,2];
},10);
echo "finished";
