gcc tkiselev_filler.c libft.a \-o tkiselev.filler
mv tkiselev.filler players/
./filler_vm \-f maps/map02 \-p2 players/tkiselev.filler \-p1 players/carli.filler
