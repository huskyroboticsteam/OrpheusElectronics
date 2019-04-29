kill -9 `ps -a | grep debug_dump | awk '/ / {print $1;}'`
