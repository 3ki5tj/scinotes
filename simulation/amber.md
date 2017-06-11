## Compilation

add `export AMBERHOME=~/lwork/amber16`

To compile
```
./configure gnu
make
```

### Preprocessing the PDB

Notes on http://ambermd.org/doc12/Amber16.pdf

```
pdb4amber -i in.pdb -o out.pdb --reduce --dry
```

`--dry` is used to remove water molecules.
`--reduce` run Reduce first to add hydrogens.


```
$AMBERHOME/bin/xleap -s -f $AMBERHOME/dat/leap/cmd/leaprc.DNA.bsc1

source leaprc.protein.ff14SB
source leaprc.water.tip3p

mol1 = loadpdb "out.pdb"

addions mol1 Na+ 0
addions mol1 Na+ 90 Cl- 110

mol2 = copy mol1
solvatebox mol1 TIP3PBOX { 40 40 40 }

solvateoct mol1 TIP3PBOX 8.0

savepdb mol1 out_wat.pdb
saveamberparm mol1 out_wat.prmtop out_wat.inpcrd
```
