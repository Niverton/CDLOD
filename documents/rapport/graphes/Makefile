%.svg: %.dot
	dot $^ -Tsvg -o $@

%.png: %.dot
	dot $^ -Tpng -o $@

pipeline.pdf: pipeline.md | architecture_main_pipeline.png scene_init.png
	pandoc $^ -o $@

.PHONY: clean
clean:
	rm -f *.svg *.png
