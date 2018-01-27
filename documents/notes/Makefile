%.html: %.md
	pandoc -s $^ -o $@

%.pdf: %.md
	pandoc -s $^ -o $@

.PHONY: clean
clean:
	rm -f *.pdf *.html
