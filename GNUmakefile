subdirs = liqprob singer1985mu usefftw usetikz attardmu hochain WHAM vrescale \
	  legendre dielectrics

clean:
	for dir in $(subdirs) ; do $(MAKE) -C $$dir clean ; done
	rm -rf *~ .*~ */*~ */.*~ */*/*~ */*/.*~ \
	  *.log *.aux *.bbl *.blg *.out
	rstrip.py -Rlv

Dropbox: clean
	rsync -avzL * ~/Dropbox/scinotes/

syncbib:
	rsync -avzL ../vir/doc/liquid.bib .
