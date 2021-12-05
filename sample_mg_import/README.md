Compile sample:

```
        cl65 -Wl -D__HIMEM__=0x6000 -DDYN_DRV=0 -t vic20 -C vic20-tgi.cfg -I.. import.c ../tgi_utils.lib
```
