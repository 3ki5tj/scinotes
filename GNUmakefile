subdirs = liqprob singer1985mu usefftw usetikz attardmu hochain WHAM vrescale \
	  legendre dielectrics

clean:
	for dir in $(subdirs) ; do $(MAKE) -C $$dir clean ; done
	rm -rf *~ .*~ */*~ */.*~ */*/*~ */*/.*~ \
	  *.log *.aux *.bbl *.blg *.out
	rstrip.py -Rlv

excludes = --exclude=".*.swp"

Dropbox: clean
	rsync -avzL $(excludes) * ~/Dropbox/scinotes/

syncbib:
	rsync -avzL $(excludes) ../vir/doc/iedoc/liquid.bib .
