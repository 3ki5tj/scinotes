tex = $(wildcard *.tex)
pdf = $(patsubst %.tex, %.pdf, $(tex))
html = $(patsubst %.tex, %.html, $(tex))
htmldir = $(patsubst %.tex, %_html, $(tex))

all: $(pdf) $(htmldir)

$(pdf) : %.pdf: %.tex
	latex $<
	pdflatex $<

# compile to latex .dvi first to figure out references


$(html) : %.html: %.tex
	tth -i $<

$(htmldir) : %_html : %.tex
	if [ ! -d "$@" ] ; then mkdir "$@" ; fi
	cd $@; ln -sf ../$<; htlatex $<

#	tth -i $<
# -i: means to use italic font for equations

Bossman:
	rsync -avzr *.pdf *.tex *_html cz1@129.109.88.204:/Bossman/cz1/notes/


clean:
	rm -f *~ *.out *.dvi *.aux *.log *.idv *.lg
	rm -rf $(htmldir)
	rstrip.py

.PHONY: clean all debug build

