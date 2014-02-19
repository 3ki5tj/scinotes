tex = $(wildcard *.tex)
dvi = $(patsubst %.tex, %.dvi, $(tex))
pdf = $(patsubst %.tex, %.pdf, $(tex))
html = $(patsubst %.tex, %.html, $(tex))
htmldir = $(patsubst %.tex, %_html, $(tex))

c = $(wildcard *.c)

all: $(pdf) $(htmldir)

$(pdf) : %.pdf: %.tex %.dvi
	pdflatex $<

$(dvi) : %.dvi: %.tex
	latex $<

# compile to latex .dvi first to figure out references


$(htmldir) : %_html : %.tex
	if [ ! -d "$@" ] ; then mkdir "$@" ; fi
	cd $@; ln -sf ../$< ../*.c .; htlatex $<

# html versions by tth are more basic and have problems
$(html) : %.html: %.tex
	tth -i $<

# -i: means to use italic font for equations


Bossman: $(pdf) $(htmldir)
	rsync -avzrL *.pdf *.tex *_html *.c cz1@129.109.88.204:/Bossman/cz1/notes/fftw/

# upload to github
github:
	git push origin master

push: github

clean:
	rm -f *~ *.out *.dvi *.aux *.log *.idv *.lg
	rm -rf $(htmldir)
	rstrip.py

.PHONY: clean all

