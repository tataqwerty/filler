gcc tkiselev_filler.c libft.a \-o tkiselev.filler
mv tkiselev.filler players/
./filler_vm \-f maps/map03 \-p1 players/tkiselev.filler \-p2 players/champely.filler
