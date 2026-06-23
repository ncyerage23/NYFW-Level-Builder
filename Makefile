#

BDIR=build
OBJ=build/main.o build/level_module.o build/nymap.o build/tile_palette.o build/tile_loader.o

level-builder: $(OBJ)
	gcc $(OBJ) -lnyfw -o $@

$(BDIR):
	mkdir -p $(BDIR)

$(BDIR)/main.o: src/main.c | $(BDIR)
	gcc -c $< -o $@

$(BDIR)/level_module.o: src/level_module.c | $(BDIR)
	gcc -c $< -o $@

$(BDIR)/nymap.o: src/nymap.c | $(BDIR)
	gcc -c $< -o $@

$(BDIR)/tile_palette.o: src/tile_palette.c | $(BDIR)
	gcc -c $< -o $@

$(BDIR)/tile_loader.o: src/tile_loader.c | $(BDIR)
	gcc -c $< -o $@

clean:
	rm -rf build
	rm -f level-builder



