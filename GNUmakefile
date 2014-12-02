subdirs = liqprob singer1985mu usefftw usetikz attardmu hochain WHAM

clean:
	for dir in $(subdirs) ; do $(MAKE) -C $$dir clean ; done
	rm -rf $(prog) a.out *~ .*.un~ */*~ */.*.un~ */*/*~ */*/.*.un~
	rstrip.py -Rlv

Dropbox: clean
	rsync -avzL * ~/Dropbox/scinotes/
