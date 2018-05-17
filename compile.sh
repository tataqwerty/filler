gcc tkiselev_filler.c arrays.c piece.c piece2.c preparation.c staff.c libft.a \-o tkiselev.filler
mv tkiselev.filler players/
./filler_vm \-f maps/map00 \-p2 players/tkiselev.filler \-p1 players/champely.filler
