prj = attardmu

tex = $(wildcard *.tex)
pdf = $(patsubst %.tex, %.pdf, $(tex))
html = $(patsubst %.tex, %.html, $(tex))
htmldir = $(patsubst %.tex, %_html, $(tex))

all: $(pdf)

$(pdf) : %.pdf: %.tex
	pdflatex $<
	bibtex $*
	pdflatex $<
	pdflatex $<

# compile to latex .dvi first to figure out references


$(htmldir) : %_html : %.tex
	if [ ! -d "$@" ] ; then mkdir "$@" ; fi
	cd $@; ln -sf ../$<; ln -sf ../../liquid.bib ..; htlatex $<

# html versions by tth are more basic and have problems
$(html) : %.html: %.tex
	tth -i $<

# -i: means to use italic font for equations

IPO=cz1@129.109.88.204
#IPO=cz1@he.host.utmb.edu

Bossman: $(pdf)
	rsync -avzrL *.pdf *.tex $(IPO):/Bossman/cz1/notes/$(prj)

# upload to github
github:
	git push origin master

push: github

clean:
	rm -f *~ *.out *.dvi *.aux *.log *.idv *.lg *.bbl *.blg *Notes.bib
	rm -rf $(htmldir)
	rstrip.py

.PHONY: clean all

