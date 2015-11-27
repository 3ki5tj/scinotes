prj=lrestimator

figs=
pdffigs=$(patsubst %,fig/%.pdf, $(figs))
epsfigs=$(patsubst %,fig/%.eps, $(figs))
figgps=$(patsubst %,fig/%.gp,  $(figs))

all: $(prj).pdf

$(prj).pdf: $(prj).tex Makefile $(pdffigs)
	pdflatex $<
	#bibtex $(prj)
	#pdflatex $<
	#pdflatex $<

$(pdffigs): %.pdf: %.gp
	$(MAKE) -C fig

clean:
	$(RM) *.aux *.bbl *.blg *.log *.dvi *.out \
	      *Notes.bib *~
	rstrip.py

$(prj)doc.zip: $(prj).tex $(prj).pdf \
	       $(epsfigs) $(pdffigs) $(figgps) \
	       README Makefile
	zip -r $@ $^

zip: $(prj)doc.zip

Bossman:
	rsync -avL $(prj).tex $(prj).pdf \
	  cz1@129.109.88.204:/Bossman/cz1/notes/$(prj)
