clean:
	rm -rf $(prog) a.out *~ .*.un~ */*~ */.*.un~ */*/*~ */*/.*.un~
	rstrip.py -Rlv

Dropbox: clean
	rsync -avzL * ~/Dropbox/scinotes/
