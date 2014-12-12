subdirs = kirkwoodg

clean:
	for dir in $(subdirs) ; do $(MAKE) -C $$dir clean ; done
	rm -rf *~ .*~ */*~ */.*~ */*/*~ */*/.*~ \
	  *.log *.aux *.bbl *.blg *.out
	rstrip.py -Rlv

Dropbox: clean
	rsync -avzL * ~/Dropbox/scinotes/dielectrics
