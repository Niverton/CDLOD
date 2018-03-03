THEME=black

%.html: %.md
	pandoc --variable=theme:$(THEME) --variable=revealjs-url:../../../reveal.js --self-contained -t revealjs $^ -o $@
