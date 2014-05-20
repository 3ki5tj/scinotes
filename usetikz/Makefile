prj = usetikz

tex = $(wildcard *.tex)
dvi = $(patsubst %.tex, %.dvi, $(tex))
pdf = $(patsubst %.tex, %.pdf, $(tex))

binx = 2d_th 2d_mp 2d_mpi

all: $(pdf)

$(pdf) : %.pdf: %.tex %.dvi
	pdflatex $<

$(dvi) : %.dvi: %.tex
	latex $<

Bossman: $(pdf)
	rsync -avzrL *.pdf *.tex cz1@he.host.utmb.edu:/Bossman/cz1/notes/$(prj)

# upload to github
github:
	git push origin master

push: github

clean:
	rm -f *~ *.out *.dat *.dvi *.aux *.log *.toc *.idv *.lg
	rm -rf $(bin) $(binx) $(prj).zip $(prj).pdf
	rstrip.py

.PHONY: clean all

